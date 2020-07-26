/*
This file is part of Cohtml, modern user interface library for
games. Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

Copyright (c) 2012-2018 Coherent Labs AD and/or its licensors. All
rights reserved in all media.

The coded instructions, statements, computer programs, and/or related
material (collectively the "Data") in these files contain confidential
and unpublished information proprietary Coherent Labs and/or its
licensors, which is protected by United States of America federal
copyright law and by international treaties.

This software or source code is supplied under the terms of a license
agreement and nondisclosure agreement with Coherent Labs Limited and may
not be copied, disclosed, or exploited except in accordance with the
terms of that agreement. The Data may not be disclosed or distributed to
third parties, in whole or in part, without the prior written consent of
Coherent Labs Limited.

COHERENT LABS MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS
SOURCE CODE FOR ANY PURPOSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER, ITS AFFILIATES,
PARENT COMPANIES, LICENSORS, SUPPLIERS, OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OR PERFORMANCE OF THIS SOFTWARE OR SOURCE CODE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "CohtmlPluginPrivatePCH.h"
#include "SCohtmlWidget.h"

#include <Engine/UserInterfaceSettings.h>
#include "CohtmlInputBindings.h"
#include "CohtmlSystem.h"
#include "CohtmlGestureApplicationPolicy.h"
#include "cohtml/View.h"

#include <Engine/RendererSettings.h>
#include <StaticMeshResources.h>
#include <Widgets/SWeakWidget.h>

#include "CohtmlSystemHolder.h"
#include "CohtmlSystemWrapper.h"
#include "CohtmlInputHelpers.h"

#include "SlateMaterialBrush.h"
#include "CohtmlAssetReferencer.h"
#include "Materials/MaterialInstanceDynamic.h"

using EGamepad = ECohtmlGamepadBehaviourOnFocusLost;

namespace
{
	UMaterialInstanceDynamic* FindMaterialInstance()
	{
		auto MaterialClass = Cast<UMaterial>(CohtmlAssetReferences::EditorMaterial().TryLoad());
		auto MaterialInstance = UMaterialInstanceDynamic::Create(MaterialClass, nullptr);
		return MaterialInstance;
	}

	UGameViewportClient* GetGameViewport()
	{
		UGameViewportClient* GameViewport = GWorld ? GWorld->GetGameViewport() : nullptr;
		if (!GameViewport)
		{
			// search for World context with GameViewport
			auto& Worlds = GEngine->GetWorldContexts();
			for (auto WorldCtx : Worlds)
			{
				if (WorldCtx.GameViewport)
				{
					GameViewport = WorldCtx.GameViewport;
					break;
				}
			}
		}
		return GameViewport;
	}
}

#define UI_TEXTURE_NAME TEXT("UITexture")
#define GAMMA_CORRECTION_EXPONENT_NAME TEXT("GammaCorrectionExponent")
class FCoherentSlateElement
{
public:
	FCoherentSlateElement(UTexture* InTexture, bool IsMaterialGammaCorrected)
		: Material(FindMaterialInstance())
		, Texture(InTexture)
	{
		//Prevent GC from destroying this instance
		Material->AddToRoot();
		Material->SetTextureParameterValue(UI_TEXTURE_NAME, InTexture);

		SetIsMaterialGammaCorrected(IsMaterialGammaCorrected);

		Brush = MakeShareable(new FSlateMaterialBrush(*Material,
			FVector2D(Texture->GetSurfaceWidth(), Texture->GetSurfaceHeight())));
	}

	~FCoherentSlateElement()
	{
		//Enable the GC to collect this instance
		Material->RemoveFromRoot();
	}

	void UpdateTexture(UTexture* InTexture)
	{
		Texture = InTexture;
		Material->SetTextureParameterValue(UI_TEXTURE_NAME, InTexture);

		Brush->ImageSize = FVector2D(Texture->GetSurfaceWidth(), Texture->GetSurfaceHeight());
	}

	FSlateBrush* GetBrush()
	{
		return Brush.Get();
	}

	void SetIsMaterialGammaCorrected(bool IsGammaCorrected)
	{
		Material->SetScalarParameterValue(GAMMA_CORRECTION_EXPONENT_NAME, IsGammaCorrected ? 2.2f : 1.0f);
	}

private:
	TSharedPtr<FSlateBrush> Brush;
	UMaterialInstanceDynamic* Material;
	UTexture* Texture;
};

void SCohtmlWidget::GesturePolicyDeleter::operator()(FCohtmlGesturePolicy* Ptr) const
{
	delete Ptr;
};

// Empty but needed constructor as otherwise the compiler generates one
// and forward declarations with TUniquePtr won't work.
SCohtmlWidget::SCohtmlWidget()
	: CurrentMouseCursor(EMouseCursor::Default)
	, DPIScaleBasedOnSize(1.f)
	, GamepadBehaviourOnFocusLost(EGamepad::CohtmlResetState)
	, bUnpairedMouseDown(false)
	, bUnpairedTouchDown(false)
	, bIsRedrawingFrame(false)
#if WITH_EDITOR
	, bIsSlateDrawingViewport(true)
#endif
{
	ComputeDPIScaleBasedOnSize();
}

void SCohtmlWidget::Construct(const FArguments& InArgs)
{
	InputPropagationBehaviour = ECohtmlInputPropagationBehaviour::None;
#if WITH_EDITOR
	if (!ActiveTimerHandle.IsValid())
	{
		ActiveTimerHandle = RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &SCohtmlWidget::ForceUpdateSlate));
	}
#endif
}

void SCohtmlWidget::CreateView(const FString& Url, TSharedPtr<cohtml::IViewListener> Listener, TSharedPtr<cohtml::ITextInputHandler> TextInputHandler, cohtml::IAsyncResourceHandler* Handler)
{
	cohtml::ViewSettings Info;

	CreateView(Info, Url, Listener, TextInputHandler);
}

void SCohtmlWidget::CreateView(const cohtml::ViewSettings& RequestedViewSettings, const FString& Url, TSharedPtr<cohtml::IViewListener> Listener, TSharedPtr<cohtml::ITextInputHandler> TextInputHandler)
{
	DPIScaledSize = FIntPoint(800, 600);
	bNeedsTextureUpdate = true;
	Filter = TextureFilter::TF_Default;

	Texture = nullptr;
	RenderWrapper.Reset(new FCohtmlRenderWrapper(Listener, TextInputHandler, &Texture, &Filter));
	cohtml::ViewSettings Info = RequestedViewSettings;
	Info.Width = DPIScaledSize.X;
	Info.Height = DPIScaledSize.Y;
	RenderWrapper->CreateView(Info, Url);

	bIsMaterialGammaCorrected = true;
	SlateElement = MakeShareable(new FCoherentSlateElement(Texture, bIsMaterialGammaCorrected));
	bReceiveInput = true;
	IMEManager.Reset(new FCohtmlWidgetIME(StaticCastSharedRef<SCohtmlWidget>(AsShared())));

	ViewportResizedHandle = FViewport::ViewportResizedEvent.AddSP(StaticCastSharedRef<SCohtmlWidget>(AsShared()), &SCohtmlWidget::OnViewportResized);

#if WITH_EDITOR
	auto Delegate = FOnActiveTabChanged::FDelegate::CreateRaw(this, &SCohtmlWidget::OnActiveTabChanged);
	ActiveTabChangedHandle = FGlobalTabmanager::Get()->OnActiveTabChanged_Subscribe(Delegate);
#endif
}

void SCohtmlWidget::OnViewportResized(class FViewport*, uint32)
{
	auto View = GetView();
	if (View)
	{
		// Redraw all on viewport resize because ue4 clears our texture
		bIsRedrawingFrame = true;
		View->ContinuousRepaint(true); //continues repaint until next tick
	}

	ComputeDPIScaleBasedOnSize();
}
#if WITH_EDITOR
void SCohtmlWidget::OnActiveTabChanged(TSharedPtr<SDockTab>, TSharedPtr<SDockTab>)
{
	auto View = GetView();
	if (View)
	{
		bIsRedrawingFrame = true;
		View->ContinuousRepaint(true); //continues repaint until next tick
	}
}
#endif

namespace
{
	void DestroyRenderWrapper(FCohtmlRenderWrapper* RenderWrapper)
	{
		RenderWrapper->BeginDestroy();
		RenderWrapper->WaitForFinishDestroy();
		RenderWrapper->FinishDestroy();
	}
}

SCohtmlWidget::~SCohtmlWidget()
{
#if WITH_EDITOR
	FGlobalTabmanager::Get()->OnActiveTabChanged_Unsubscribe(ActiveTabChangedHandle);
#endif
	FViewport::ViewportResizedEvent.Remove(ViewportResizedHandle);
	DestroyRenderWrapper(RenderWrapper.Get());
}

void SCohtmlWidget::RecreateView(const cohtml::ViewSettings& RequestedViewSettings, const FString& Url, TSharedPtr<cohtml::IViewListener> Listener, TSharedPtr<cohtml::ITextInputHandler> TextInputHandler)
{
	cohtml::ViewSettings Info = RequestedViewSettings;
	Info.Width = DPIScaledSize.X;
	Info.Height = DPIScaledSize.Y;
	bNeedsTextureUpdate = true;
	RenderWrapper->RecreateView(Info, Url);
}

cohtml::View* SCohtmlWidget::GetView()
{
	return RenderWrapper->GetView();
}

cohtml::ViewRenderer* SCohtmlWidget::GetViewRenderer()
{
	return RenderWrapper->GetViewRenderer();
}

UTextureRenderTarget2D* SCohtmlWidget::GetRenderTexture() const
{
	return Texture;
}

FVector2D SCohtmlWidget::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(DPIScaledSize) / DPIScaleBasedOnSize;
}

void SCohtmlWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	auto View = GetView();
	bool bIsRenderWrapperValid = View != nullptr;
	if (bIsRedrawingFrame && bIsRenderWrapperValid)
	{
		bIsRedrawingFrame = false;
		View->ContinuousRepaint(false);
	}

#if WITH_EDITOR
	// When in the Editor, track the Slate Throttle Manager and cause a redraw
	// whenever it just ended throttling. This is needed because whenever the
	// viewport is resized (for example), the Cohtml texture will be recreated and
	// it will be registered in FDeferredUpdateResource::AddToDeferredUpdateList
	// by the Render Thread when doing InitRHI(). If in that time the resize bar
	// is not released, the Throttle Manager will disallow expensive tasks and
	// UEditorEngine::UpdateSingleViewportClient will stop redrawing the viewport,
	// while Cohtml drawing tasks will still be executed. When the resize bar is
	// released, UpdateSingleViewportClient will redraw the viewport, which in
	// turn will call FDeferredUpdateResource::UpdateResources and complete the
	// initialization of the resized texture by clearing it with a specified
	// color, effectively erasing everything that Cohtml has redrawn after the resize.
	// To remedy that, force a redraw after the Throttle Manager has done its work.

	bool bIsSlateCurrentlyDrawingViewport = FSlateThrottleManager::Get().IsAllowingExpensiveTasks();
	if (bIsSlateCurrentlyDrawingViewport != bIsSlateDrawingViewport && bIsRenderWrapperValid)
	{
		bIsSlateDrawingViewport = bIsSlateCurrentlyDrawingViewport;
		if (bIsSlateCurrentlyDrawingViewport)
		{
			bIsRedrawingFrame = true;
			View->ContinuousRepaint(true);
		}
	}
#endif //WITH_EDITOR

	const FVector2D& NewSize = AllottedGeometry.GetLocalSize();
	auto NewWidth = FMath::RoundToInt(NewSize.X * DPIScaleBasedOnSize);
	auto NewHeight = FMath::RoundToInt(NewSize.Y * DPIScaleBasedOnSize);

	bool bSizeValid = NewWidth > 0 && NewHeight > 0;
	bool bSizeChanged = NewWidth != DPIScaledSize.X || NewHeight != DPIScaledSize.Y;
	if (bIsRenderWrapperValid && bSizeChanged && bSizeValid)
	{
		DPIScaledSize.X = NewWidth;
		DPIScaledSize.Y = NewHeight;
		RenderWrapper->Resize(DPIScaledSize.X, DPIScaledSize.Y);

		bNeedsTextureUpdate = true;
	}

	if (bNeedsTextureUpdate && bIsRenderWrapperValid)
	{
		SlateElement->UpdateTexture(RenderWrapper->GetTexture());
		bNeedsTextureUpdate = false;
	}

	if (RenderWrapper->Tick(InDeltaTime))
	{
		// Paint the View directly as Tick is called on Slate
		// rendering which is just before presenting. Paint will
		// wait for Layout/RecordRendering to finish
		RenderWrapper->Paint_GameThread();
	}
}

int32 SCohtmlWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (!RenderWrapper->bPainted)
	{
		return LayerId;
	}

	const FSlateBrush* Brush = SlateElement->GetBrush();

#if defined(COHTML_UE4_416_SUPPORT)
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(Brush->ImageSize, FSlateLayoutTransform(1 / DPIScaleBasedOnSize)),
		Brush,
		MyClippingRect);
#else
	OutDrawElements.PushClip(FSlateClippingZone(MyClippingRect));
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(Brush->ImageSize, FSlateLayoutTransform(1 / DPIScaleBasedOnSize)),
		Brush);
	OutDrawElements.PopClip();
#endif
	return LayerId;
}

FReply SCohtmlWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseMove);
}

FReply SCohtmlWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseDown);
}

FReply SCohtmlWidget::OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseDown);
}

FReply SCohtmlWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseUp);
}

FReply SCohtmlWidget::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseWheel);
}

FReply SCohtmlWidget::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	return OnTouchEvent(MyGeometry, TouchEvent, cohtml::TouchEventData::TouchMove);
}

FReply SCohtmlWidget::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	return OnTouchEvent(MyGeometry, TouchEvent, cohtml::TouchEventData::TouchDown);
}

FReply SCohtmlWidget::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	return OnTouchEvent(MyGeometry, TouchEvent, cohtml::TouchEventData::TouchUp);
}

FReply SCohtmlWidget::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent)
{
	return FReply::Unhandled();
}

FCursorReply SCohtmlWidget::OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{
	return FCursorReply::Cursor(CurrentMouseCursor);
}

FReply SCohtmlWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	if (KeyEvent.GetKey().IsGamepadKey())
	{
		FCohtmlSystemHolder::GetGamepadProvider().UpdateState(KeyEvent, true);
	}
	else
	{
		ProcessKeyEvent(KeyEvent, cohtml::KeyEventData::KeyDown);
	}
	return HandleEventIfNeeded(KeyEvent);
}

FReply SCohtmlWidget::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	if (KeyEvent.GetKey().IsGamepadKey())
	{
		FCohtmlSystemHolder::GetGamepadProvider().UpdateState(KeyEvent, false);
	}
	else
	{
		ProcessKeyEvent(KeyEvent, cohtml::KeyEventData::KeyUp);
	}
	return HandleEventIfNeeded(KeyEvent);
}

FReply SCohtmlWidget::OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& KeyEvent)
{
	FCohtmlSystemHolder::GetGamepadProvider().UpdateState(KeyEvent);
	return HandleEventIfNeeded(KeyEvent);
}

FReply SCohtmlWidget::OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent)
{
	ProcessKeyEvent(InCharacterEvent, cohtml::KeyEventData::Char);
	return HandleEventIfNeeded(InCharacterEvent);
}

bool SCohtmlWidget::SupportsKeyboardFocus() const
{
	return true;
}

FReply SCohtmlWidget::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InKeyFocusEvent)
{
	if (GamepadBehaviourOnFocusLost == EGamepad::CohtmlUseStateBeforeReset)
	{
		FCohtmlSystemHolder::GetGamepadProvider().ApplyLastGamepadState(InKeyFocusEvent.GetUser());
	}

	IMEManager->ActivateTextInputMethodSystemContext(true);

	return FReply::Unhandled();
}

void SCohtmlWidget::OnFocusLost(const FFocusEvent& InKeyboardFocusEvent)
{
	if (auto View = GetView())
	{
		auto UnpairedMouseDownEvent = bUnpairedMouseDown ? &LastMouseDownData : nullptr;
		CohtmlInputHelpers::ClearViewState(GetView(), UnpairedMouseDownEvent);
		bUnpairedMouseDown = false;

		auto UnpaireTouchDownEvent = bUnpairedTouchDown ? &LastTouchDownData : nullptr;
		CohtmlInputHelpers::ClearViewState(GetView(), UnpaireTouchDownEvent);
		bUnpairedTouchDown = false;
	}

	const auto CurrentUserId = InKeyboardFocusEvent.GetUser();
	FCohtmlSystemHolder::GetGamepadProvider().SaveGamepadState(CurrentUserId);
	GamepadBehaviourOnFocusLost = GamepadBehaviourOnFocusLostDelegate.IsBound() ? GamepadBehaviourOnFocusLostDelegate.Execute(CurrentUserId) : EGamepad::CohtmlResetState;

	if (GamepadBehaviourOnFocusLost == EGamepad::CohtmlResetState || GamepadBehaviourOnFocusLost == EGamepad::CohtmlUseStateBeforeReset)
	{
		FCohtmlSystemHolder::GetGamepadProvider().ResetGamepadState(CurrentUserId);
	}

	IMEManager->ActivateTextInputMethodSystemContext(false);
}

FReply SCohtmlWidget::OnMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::MouseEventData::EventType EventType)
{
	auto View = GetView();
	if (View && bReceiveInput)
	{
		if (EventType == cohtml::MouseEventData::MouseMove && MouseEvent.GetCursorDelta().IsZero())
		{
			return FReply::Handled();
		}

		FVector2D ScaledViewportPosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()) * DPIScaleBasedOnSize;
		cohtml::MouseEventData CoherentMouseData;
		CohtmlInputHelpers::GetMouseDataFromFPointerEvent(CoherentMouseData, MyGeometry, MouseEvent, EventType);
		CoherentMouseData.X = ScaledViewportPosition.X;
		CoherentMouseData.Y = ScaledViewportPosition.Y;

		if (EventType == cohtml::MouseEventData::MouseDown)
		{
			LastMouseDownData = CoherentMouseData;
			bUnpairedMouseDown = true;
		}
		else if (EventType == cohtml::MouseEventData::MouseUp)
		{
			bUnpairedMouseDown = false;
		}

		auto Reply = CohtmlInputHelpers::SendCohtmlMouseEvent(View, CoherentMouseData);
		if (Reply.IsEventHandled())
		{
			return Reply.DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton()).PreventThrottling();
		}
		return Reply;
	}
	return FReply::Unhandled();
}

FReply SCohtmlWidget::OnTouchEvent(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent, cohtml::TouchEventData::EventType EventType)
{
	auto View = GetView();
	if (View && bReceiveInput)
	{
		if (EventType == cohtml::TouchEventData::TouchMove && TouchEvent.GetCursorDelta().IsZero())
		{
			return FReply::Handled();
		}

		FVector2D ScaledViewportPosition = MyGeometry.AbsoluteToLocal(TouchEvent.GetScreenSpacePosition()) * DPIScaleBasedOnSize;
		cohtml::TouchEventData CoherentTouchData;
		CohtmlInputHelpers::GetTouchDataFromFPointerEvent(CoherentTouchData, MyGeometry, TouchEvent, EventType);
		CoherentTouchData.X = ScaledViewportPosition.X;
		CoherentTouchData.Y = ScaledViewportPosition.Y;

		if (EventType == cohtml::TouchEventData::TouchDown)
		{
			LastTouchDownData = CoherentTouchData;
			bUnpairedTouchDown = true;
		}
		else if (EventType == cohtml::TouchEventData::TouchUp)
		{
			bUnpairedTouchDown = false;
		}

		auto Reply = CohtmlInputHelpers::SendCohtmlTouchEvent(View, CoherentTouchData, GetGesturePolicy());
		if (Reply.IsEventHandled())
		{
			return Reply.DetectDrag(SharedThis(this), TouchEvent.GetEffectingButton()).PreventThrottling();
		}
		return Reply;
	}
	return FReply::Unhandled();
}

void SCohtmlWidget::ComputeDPIScaleBasedOnSize()
{
	auto Viewport = GetGameViewport();
	if (Viewport)
	{
		FVector2D ViewportSize;
		Viewport->GetViewportSize(ViewportSize);
		DPIScaleBasedOnSize = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(ViewportSize.IntPoint());
	}
}

void SCohtmlWidget::SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Behaviour)
{
	InputPropagationBehaviour = Behaviour;
}

FORCEINLINE FReply SCohtmlWidget::HandleEventIfNeeded(const FKeyEvent& KeyEvent)
{
	const auto Key = KeyEvent.GetKey();
	bool bPropagate = ((InputPropagationBehaviour & ECohtmlInputPropagationBehaviour::Joystick) && Key.IsGamepadKey()) ||
		((InputPropagationBehaviour & ECohtmlInputPropagationBehaviour::Keyboard) && !Key.IsGamepadKey());
	return bPropagate ? FReply::Unhandled() : FReply::Handled();
}

FORCEINLINE FReply SCohtmlWidget::HandleEventIfNeeded(const FCharacterEvent& /* CharacterEvent */)
{
	bool bPropagate = (InputPropagationBehaviour & ECohtmlInputPropagationBehaviour::Keyboard);
	return bPropagate ? FReply::Unhandled() : FReply::Handled();
}

void SCohtmlWidget::ProcessKeyEvent(const FInputEvent& Event, cohtml::KeyEventData::EventType Type)
{
	cohtml::KeyEventData KeyData = CohtmlInputHelpers::MakeKeyEvent(Event, Type);
	auto View = GetView();
	if (View && bReceiveInput)
	{
		View->KeyEvent(KeyData, nullptr, nullptr);
	}
}

bool SCohtmlWidget::HasRequestedView() const
{
	return RenderWrapper->HasRequestedView();
}

TextureFilter SCohtmlWidget::GetFilter() const
{
	return Filter;
}

void SCohtmlWidget::SetFilter(TextureFilter InFilter)
{
	Filter = InFilter;
}

void SCohtmlWidget::SetReceiveInput(bool bInReceiveInput)
{
	bReceiveInput = bInReceiveInput;
}

void SCohtmlWidget::SetIsMaterialGammaCorrected(bool bIsGammaCorrected)
{
	if (bIsMaterialGammaCorrected != bIsGammaCorrected)
	{
		bIsMaterialGammaCorrected = bIsGammaCorrected;
		SlateElement->SetIsMaterialGammaCorrected(bIsMaterialGammaCorrected);
	}
}

FCohtmlGesturePolicy* SCohtmlWidget::GetGesturePolicy()
{
	if (!GesturePolicy)
	{
		GesturePolicy.Reset(new FCohtmlGesturePolicy());
		GesturePolicy->Initialize(GetView());
	}
	return GesturePolicy.Get();
}

#if WITH_EDITOR
EActiveTimerReturnType SCohtmlWidget::ForceUpdateSlate(double InCurrentTime, float InDeltaTime)
{
	return EActiveTimerReturnType::Continue;
}
#endif