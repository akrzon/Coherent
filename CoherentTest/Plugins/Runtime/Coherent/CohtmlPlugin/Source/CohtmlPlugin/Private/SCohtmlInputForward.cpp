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
#include "SCohtmlInputForward.h"

#include <Engine/UserInterfaceSettings.h>
#include "CohtmlInputBindings.h"
#include "CohtmlComponent.h"
#include "CohtmlHUD.h"
#include "CohtmlGameHUD.h"
#include "CohtmlSystemWrapper.h"
#include "CohtmlIMEManager.h"

#include "cohtml/View.h"

#include "Engine/RendererSettings.h"

#include "StaticMeshResources.h"

#include <Widgets/SWeakWidget.h>

#include "CohtmlSystemHolder.h"
#include "CohtmlInputHelpers.h"

#include "Engine/LocalPlayer.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/HUD.h"
#include "GameFramework/GameModeBase.h"

#if PLATFORM_ANDROID
#include <Kismet/GameplayStatics.h>
#include <PhysicsEngine/PhysicsSettings.h>
#endif

using EGamepad = ECohtmlGamepadBehaviourOnFocusLost;

SCohtmlInputForward::SCohtmlInputForward()
{
}

SCohtmlInputForward::~SCohtmlInputForward()
{
}

void SCohtmlInputForward::Construct(const FArguments& InArgs)
{
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill);

	OwnerActor = InArgs._Owner;
	FocusedViewComponent = nullptr;
	bHasKeyboardFocus = false;
	bAlwaysAcceptMouseInputEvents = false;
	InputPropagationBehaviour = ECohtmlInputPropagationBehaviour::None;
	GamepadBehaviourOnFocusLost = EGamepad::CohtmlResetState;
	LineTraceMode = CohtmlInputLineTrace_Single;

	SetRaycastCollisionGroup(ECC_WorldDynamic);
	SetRaycastTextureAddressMode(TA_Wrap);
	SetRaycastQuality(CohtmlRaycastQuality_Accurate);
	SetRaycastUVChannel(0);

	bUnpairedMouseDown = false;
	bAttachedVirtualJoystick = false;

	IMEManager.Reset(new FCohtmlInputForwardIME(StaticCastSharedRef<SCohtmlInputForward>(AsShared())));
}

void SCohtmlInputForward::AttachVirtualJoystick(TSharedRef<SVirtualJoystick> Joystick)
{
	if (bAttachedVirtualJoystick)
	{
		ChildSlot.DetachWidget();
	}
	ChildSlot.AttachWidget(Joystick);
	bAttachedVirtualJoystick = true;
}

void SCohtmlInputForward::DetachVirtualJoystick()
{
	if (bAttachedVirtualJoystick)
	{
		ChildSlot.DetachWidget();
		bAttachedVirtualJoystick = false;
	}
}

FReply SCohtmlInputForward::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if ((!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents) || MouseEvent.GetCursorDelta().IsZero())
	{
		return FReply::Unhandled();
	}

	OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseMove);
	return FReply::Unhandled();
}

FReply SCohtmlInputForward::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	OnCohtmlInputWidgetMouseButtonDown.Broadcast(MouseEvent.GetEffectingButton());
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseDown);
}

FReply SCohtmlInputForward::OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseDown);
}

FReply SCohtmlInputForward::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	OnCohtmlInputWidgetMouseButtonUp.Broadcast(MouseEvent.GetEffectingButton());
	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseUp);
}

FReply SCohtmlInputForward::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	return OnMouseEvent(MyGeometry, MouseEvent, cohtml::MouseEventData::MouseWheel);
}

FReply SCohtmlInputForward::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	if ((!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents) || TouchEvent.GetCursorDelta().IsZero())
	{
		return FReply::Unhandled();
	}

	OnTouchEvent(MyGeometry, TouchEvent, cohtml::TouchEventData::TouchMove);
	return FReply::Unhandled();
}

FReply SCohtmlInputForward::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	return OnTouchEvent(MyGeometry, TouchEvent, cohtml::TouchEventData::TouchDown);
}

FReply SCohtmlInputForward::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	return OnTouchEvent(MyGeometry, TouchEvent, cohtml::TouchEventData::TouchUp);
}

FReply SCohtmlInputForward::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent)
{
	if (!bHasKeyboardFocus && !bAlwaysAcceptMouseInputEvents)
	{
		return FReply::Unhandled();
	}

	if (PointerEvent.IsTouchEvent())
	{
		OnTouchEvent(MyGeometry, PointerEvent, cohtml::TouchEventData::TouchMove);
	}
	else
	{
		OnMouseEvent(MyGeometry, PointerEvent, cohtml::MouseEventData::MouseMove);
	}

	return FReply::Unhandled();
}

FCursorReply SCohtmlInputForward::OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{
	auto CurrentMouseCursor = LastTouchedViewComponent.IsValid() ? LastTouchedViewComponent->CurrentMouseCursor : EMouseCursor::Default;
	return FCursorReply::Cursor(CurrentMouseCursor);
}

void SCohtmlInputForward::SetAlwaysAcceptMouseInputEvents(bool bAccept)
{
	bAlwaysAcceptMouseInputEvents = bAccept;
}

void SCohtmlInputForward::SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Behaviour)
{
	InputPropagationBehaviour = Behaviour;
}

void SCohtmlInputForward::SetLineTraceMode(ECohtmlInputWidgetLineTraceMode Mode)
{
	LineTraceMode = Mode;
}

void SCohtmlInputForward::RefocusView(UCohtmlBaseComponent* NewFocusedView)
{
	// Clear the state of the last component - this will match the currently focused one 90%
	// of the time but since moving the mouse does not change focus, there are times when
	// the focused one is null and the last touched is not null.
	// Since the clear view state method sends a mouse event outside the view bounds it
	// may break WebCore click logic, which expects a mouse up event to occur on the same
	// element that the mouse down was fired. We only send the event if the last touched view
	// is not the same as the focused one to avoid that.
	if (FocusedViewComponent != LastTouchedViewComponent && LastTouchedViewComponent.IsValid() && LastTouchedViewComponent->GetView() != nullptr)
	{
		auto UnpairedMouseDownEvent = bUnpairedMouseDown ? &LastMouseDownData : nullptr;
		CohtmlInputHelpers::ClearViewState(LastTouchedViewComponent->GetView(), UnpairedMouseDownEvent);
		bUnpairedMouseDown = false;

		auto UnpaireTouchDownEvent = bUnpairedTouchDown ? &LastTouchDownData : nullptr;
		CohtmlInputHelpers::ClearViewState(LastTouchedViewComponent->GetView(), UnpaireTouchDownEvent);
		bUnpairedTouchDown = false;
	}
	FocusedViewComponent = NewFocusedView;
}

FReply SCohtmlInputForward::DiscardViewFocus(cohtml::MouseEventData::EventType EventType)
{
	if (EventType != cohtml::MouseEventData::MouseMove)
	{
		RefocusView(nullptr);
	}

	return FReply::Unhandled();
}

FReply SCohtmlInputForward::DiscardViewFocus(cohtml::TouchEventData::EventType EventType)
{
	if (EventType != cohtml::TouchEventData::TouchMove)
	{
		RefocusView(nullptr);
	}

	return FReply::Unhandled();
}

static bool IntersectRayTriangle(
	const FVector& RayOrigin, const FVector& RayDirection,
	const FVector& V0, const FVector& V1, const FVector& V2,
	float& T, float& U, float& V)
{
	// Moller-Trumbore ray-triangle intersection
	FVector E1 = V1 - V0;
	FVector E2 = V2 - V0;

	FVector Pvec = FVector::CrossProduct(RayDirection, E2);

	float Det = FVector::DotProduct(E1, Pvec);

	static const float DET_EPSILON = 0.001f;

	// With culling
	if (Det < DET_EPSILON)
	{
		return false;
	}

	FVector Tvec = RayOrigin - V0;
	U = FVector::DotProduct(Tvec, Pvec);

	if (U < 0 || U > Det)
	{
		return false;
	}

	FVector Qvec = FVector::CrossProduct(Tvec, E1);

	V = FVector::DotProduct(RayDirection, Qvec);

	if (V < 0 || U + V > Det)
	{
		return false;
	}

	float InvDet = 1.0f / Det;
	T = FVector::DotProduct(E2, Qvec) * InvDet;
	U *= InvDet;
	V *= InvDet;

	return true;
}

static bool IntersectWithRay(const FVector& RayOriginModelSpace, const FVector& RayDirectionModelSpace,
	const TArray<FCohtmlVertexUV>& UVs,
	const TArray<FVector>& PositionBuffer,
	const FIndexArrayView& IndexBuffer,
	const uint32 UVChannel,
	float& OutDist, float& OutU, float& OutV)
{
	static const int32 NO_HIT = -1;
	int32 HitFaceIndex = NO_HIT; // Actually index of the hit face's first vertex index in the indices array, but never mind
	float MinDist = FLT_MAX;
	float TexU = 0;
	float TexV = 0;

	for (int32 i = 0; i < IndexBuffer.Num(); i += 3)
	{
		float T, U, V;
		const FVector& V0 = PositionBuffer[IndexBuffer[i]];
		const FVector& V1 = PositionBuffer[IndexBuffer[i + 2]];
		const FVector& V2 = PositionBuffer[IndexBuffer[i + 1]];

		if (IntersectRayTriangle(RayOriginModelSpace, RayDirectionModelSpace, V0, V1, V2, T, U, V))
		{
			if (T < MinDist)
			{
				MinDist = T;
				// Temporarily save barycentric coordinates here
				TexU = U;
				TexV = V;

				HitFaceIndex = i;
			}
		}
	}

	if (HitFaceIndex != NO_HIT)
	{
		// Compute texture coordinates from barycentric coordinates
		FVector2D TexCoords =
			(1 - TexU - TexV) * UVs[IndexBuffer[HitFaceIndex]].Channels[UVChannel] +
			TexU * UVs[IndexBuffer[HitFaceIndex + 2]].Channels[UVChannel] +
			TexV * UVs[IndexBuffer[HitFaceIndex + 1]].Channels[UVChannel];

		OutU = TexCoords.X;
		OutV = TexCoords.Y;
		OutDist = MinDist;

		return true;
	}

	return false;
}

static void AdjustUVCoordinates(TextureAddress AddressMode, float& U, float& V)
{
	switch (AddressMode)
	{
	case TA_Wrap:
		// Account for negative values as well
		U = FMath::Fmod(FMath::Fmod(U, 1.0f) + 1.0f, 1.0f);
		V = FMath::Fmod(FMath::Fmod(V, 1.0f) + 1.0f, 1.0f);
		return;
	case TA_Clamp:
		U = FMath::Clamp(U, 0.0f, 1.0f);
		V = FMath::Clamp(V, 0.0f, 1.0f);
		return;
	case TA_Mirror:
		U = FMath::Fmod(FMath::Fmod(U, 2.0f) + 2.0f, 2.0f);
		if (U > 1.0f)
		{
			U = 1.0f - U;
		}
		V = FMath::Fmod(FMath::Fmod(V, 2.0f) + 2.0f, 2.0f);
		if (V > 1.0f)
		{
			V = 1.0f - V;
		}
		return;
	default:
		COHTML_UE_LOG(Warning, TEXT("Unsupported texture addressing mode when adjusting texture coordinates!"));
		return;
	}
}

FReply SCohtmlInputForward::OnMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::MouseEventData::EventType EventType)
{
	UWorld* World = nullptr;
	if (OwnerActor.IsValid())
	{
		World = OwnerActor->GetWorld();
	}

	if (World == nullptr)
	{
		return DiscardViewFocus(EventType);
	}

	const FVector2D& ScaledViewportPosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());

	UGameViewportClient* GameViewportClient = World->GetGameViewport();

	if (GameViewportClient == nullptr)
	{
		return DiscardViewFocus(EventType);
	}

	FVector2D ViewportSize;
	GameViewportClient->GetViewportSize(ViewportSize);

	float DPIScale = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));

	//Since the mouse event's coordinated are scaled to count for the desired UI dpi, we need to remove the scaling
	FVector2D ViewportPositionVec2D = ScaledViewportPosition * DPIScale;

	APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(World);
	if (!PlayerController || !PlayerController->Player)
	{
		return DiscardViewFocus(EventType);
	}

	ULocalPlayer* Player = Cast<ULocalPlayer>(PlayerController->Player);

	FSceneViewProjectionData ProjectionData;
	const bool bProjectionDataObtained = Player->GetProjectionData(Player->ViewportClient->Viewport, eSSP_FULL, ProjectionData);

	cohtml::MouseEventData CoherentMouseData;
	CohtmlInputHelpers::GetMouseDataFromFPointerEvent(CoherentMouseData, MyGeometry, MouseEvent, EventType);

	// Handle Mouse input on HUD Views
	FReply Reply(FReply::Unhandled());
	TFunction<bool(FVector2D&, UCohtmlBaseComponent*, cohtml::View*)> HandleHUDInputFunction = [&](FVector2D& ConstrainedPos, UCohtmlBaseComponent* Component, cohtml::View* View)
	{
		CoherentMouseData.X = ConstrainedPos.X;
		CoherentMouseData.Y = ConstrainedPos.Y;

		if (EventType == cohtml::MouseEventData::MouseDown)
		{
			RefocusView(Component);
			LastMouseDownData = CoherentMouseData;
			bUnpairedTouchDown = true;
		}
		if (EventType == cohtml::MouseEventData::MouseUp)
		{
			bUnpairedTouchDown = false;
		}

		LastTouchedViewComponent = Component;
		Reply = CohtmlInputHelpers::SendCohtmlMouseEvent(View, CoherentMouseData);
		if (Reply.IsEventHandled())
		{
			Reply = Reply.DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton()).PreventThrottling();
			return true; // should return Reply from function caller
		}

		return false;
	};

	if (HandlePointerEventForHUDViews(World, ViewportPositionVec2D, bProjectionDataObtained, ProjectionData, HandleHUDInputFunction))
	{
		return Reply;
	}

	// Handle Mouse input on In-world UI Views
	Reply = FReply::Unhandled();

	TFunction<void(void)> DiscardViewFocusFunction = [&]()
	{
		Reply = DiscardViewFocus(EventType);
	};

	TFunction<void(void)> HandledInputFunction = [&]()
	{
		Reply = FReply::Handled().DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton()).PreventThrottling();
	};

	TFunction<bool(UCohtmlBaseComponent*, cohtml::View*, float, float)> HandleInWorldInputFunction = [&](UCohtmlBaseComponent* Component, cohtml::View* View, float U, float V)
	{
		CoherentMouseData.X = U * View->GetWidth();
		CoherentMouseData.Y = V * View->GetHeight();

		if (EventType == cohtml::MouseEventData::MouseDown)
		{
			RefocusView(Component);
			LastMouseDownData = CoherentMouseData;
			bUnpairedMouseDown = true;
		}
		if (EventType == cohtml::MouseEventData::MouseUp)
		{
			bUnpairedMouseDown = false;
		}

		LastTouchedViewComponent = Component;
		Reply = CohtmlInputHelpers::SendCohtmlMouseEvent(View, CoherentMouseData);
		if (Reply.IsEventHandled())
		{
			Reply = Reply.DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton()).PreventThrottling();
			return true;
		}

		return false;
	};

	if (HandlePointerEventForInWorldViews(World, Player, ViewportPositionVec2D, bProjectionDataObtained, ProjectionData, DiscardViewFocusFunction, HandledInputFunction, HandleInWorldInputFunction))
	{
		return Reply;
	}

	return DiscardViewFocus(EventType);
}

FReply SCohtmlInputForward::OnTouchEvent(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent, cohtml::TouchEventData::EventType EventType)
{
	UWorld* World = nullptr;
	if (OwnerActor.IsValid())
	{
		World = OwnerActor->GetWorld();
	}

	if (World == nullptr)
	{
		return DiscardViewFocus(EventType);
	}

	APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(World);
	if (!PlayerController || !PlayerController->Player)
	{
		return DiscardViewFocus(EventType);
	}

	UGameViewportClient* GameViewportClient = World->GetGameViewport();

	if (GameViewportClient == nullptr)
	{
		return DiscardViewFocus(EventType);
	}

	const FVector2D& ScaledViewportPosition = MyGeometry.AbsoluteToLocal(TouchEvent.GetScreenSpacePosition());

	FVector2D ViewportSize;
	GameViewportClient->GetViewportSize(ViewportSize);

	float DPIScale = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));

	//Since the mouse event's coordinated are scaled to count for the desired UI dpi, we need to remove the scaling
	FVector2D ViewportPositionVec2D = ScaledViewportPosition * DPIScale;

	ULocalPlayer* Player = Cast<ULocalPlayer>(PlayerController->Player);

	FSceneViewProjectionData ProjectionData;
	const bool bProjectionDataObtained = Player->GetProjectionData(Player->ViewportClient->Viewport, eSSP_FULL, ProjectionData);

	cohtml::TouchEventData CoherentTouchData;
	CohtmlInputHelpers::GetTouchDataFromFPointerEvent(CoherentTouchData, MyGeometry, TouchEvent, EventType);

	// Handle Touch input on HUD Views
	FReply Reply(FReply::Unhandled());
	TFunction<bool(FVector2D&, UCohtmlBaseComponent*, cohtml::View*)> HandleHUDInputFunction = [&](FVector2D& ConstrainedPos, UCohtmlBaseComponent* Component, cohtml::View* View)
	{
		CoherentTouchData.X = ConstrainedPos.X;
		CoherentTouchData.Y = ConstrainedPos.Y;

		if (EventType == cohtml::TouchEventData::TouchDown)
		{
			RefocusView(Component);
			LastTouchDownData = CoherentTouchData;
			bUnpairedTouchDown = true;
		}
		if (EventType == cohtml::TouchEventData::TouchUp)
		{
			bUnpairedTouchDown = false;
		}

		LastTouchedViewComponent = Component;
		Reply = CohtmlInputHelpers::SendCohtmlTouchEvent(View, CoherentTouchData, Component->GetGesturePolicy());
		if (Reply.IsEventHandled())
		{
			Reply = Reply.DetectDrag(SharedThis(this), TouchEvent.GetEffectingButton()).PreventThrottling();
			return true; // should return Reply from function caller
		}

		return false;
	};

	if (HandlePointerEventForHUDViews(World, ViewportPositionVec2D, bProjectionDataObtained, ProjectionData, HandleHUDInputFunction))
	{
		return Reply;
	}

	// Handle Touch input on In-world UI Views
	Reply = FReply::Unhandled();

	TFunction<void(void)> DiscardViewFocusFunction = [&]()
	{
		Reply = DiscardViewFocus(EventType);
	};

	TFunction<void(void)> HandledInputFunction = [&]()
	{
		Reply = FReply::Handled().DetectDrag(SharedThis(this), TouchEvent.GetEffectingButton()).PreventThrottling();
	};

	TFunction<bool(UCohtmlBaseComponent*, cohtml::View*, float, float)> HandleInWorldInputFunction = [&](UCohtmlBaseComponent* Component, cohtml::View* View, float U, float V)
	{
		CoherentTouchData.X = U * View->GetWidth();
		CoherentTouchData.Y = V * View->GetHeight();

		if (EventType == cohtml::TouchEventData::TouchDown)
		{
			RefocusView(Component);
			LastTouchDownData = CoherentTouchData;
			bUnpairedTouchDown = true;
		}
		if (EventType == cohtml::TouchEventData::TouchUp)
		{
			bUnpairedTouchDown = false;
		}

		LastTouchedViewComponent = Component;
		Reply = CohtmlInputHelpers::SendCohtmlTouchEvent(View, CoherentTouchData, Component->GetGesturePolicy());
		if (Reply.IsEventHandled())
		{
			Reply = Reply.DetectDrag(SharedThis(this), TouchEvent.GetEffectingButton()).PreventThrottling();
			return true;
		}

		return false;
	};

	if (HandlePointerEventForInWorldViews(World, Player, ViewportPositionVec2D, bProjectionDataObtained, ProjectionData, DiscardViewFocusFunction, HandledInputFunction, HandleInWorldInputFunction))
	{
		return Reply;
	}

	return DiscardViewFocus(EventType);
}

bool SCohtmlInputForward::HandlePointerEventForHUDViews(
	UWorld* World, FVector2D& ViewportPositionVec2D, bool bProjectionDataObtained, FSceneViewProjectionData& ProjectionData,
	const TFunctionRef<bool(FVector2D&, UCohtmlBaseComponent*, cohtml::View*)> HandleHUDInputFunction)
{
	// Check HUD Views
	for (auto It = UCohtmlBaseComponent::GetUCohtmlBaseComponentIterator(World); It; ++It)
	{
		if ((*It).IsValid() && (*It)->GetWorld() == World)
		{
			UCohtmlBaseComponent* Component = (*It).Get();
			UClass* ComponentClass = Component->GetClass();
			auto Owner = Component->GetOwner();
			if (UCohtmlHUD::StaticClass() == ComponentClass || (Owner && Cast<AHUD>(Owner) != nullptr))
			{
				cohtml::View* View = Component->GetView();
				if (Component->bReceiveInput && View)
				{
					ACohtmlGameHUD* CohtmlGameHud = Cast<ACohtmlGameHUD>(Owner);

					FIntPoint InputPad = CohtmlGameHud->GetInputPadding();
					ViewportPositionVec2D.X -= InputPad.X;
					ViewportPositionVec2D.Y -= InputPad.Y;

					if (ViewportPositionVec2D.X < 0 || ViewportPositionVec2D.Y < 0)
					{
						continue;
					}

					FVector2D ConstraintOffset(0, 0);
					if (bProjectionDataObtained)
					{
						const FIntRect& ConstrainedViewRect = ProjectionData.GetConstrainedViewRect();
						ConstraintOffset = FVector2D(float(ConstrainedViewRect.Min.X), float(ConstrainedViewRect.Min.Y));
					}
					FVector2D ConstrainedPos = ViewportPositionVec2D - ConstraintOffset;

					if (HandleHUDInputFunction(ConstrainedPos, Component, View))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool SCohtmlInputForward::HandlePointerEventForInWorldViews(
	UWorld* World, ULocalPlayer* Player, FVector2D& ViewportPositionVec2D, bool bProjectionDataObtained, FSceneViewProjectionData& ProjectionData,
	const TFunctionRef<void(void)> DiscardViewFocusFunction,
	const TFunctionRef<void(void)> HandledInputFunction,
	const TFunctionRef<bool(UCohtmlBaseComponent*, cohtml::View*, float, float)> HandleInWorldInputFunction)
{
#if PLATFORM_ANDROID
	if (!UPhysicsSettings::Get()->bSupportUVFromHitResults)
	{
		COHTML_UE_LOG(Warning, TEXT("Input for in-world views in UE4 on Android requires")
			TEXT(" enabling \"Support UV From Hit Results\" in Physics Settings. Note that this")
			TEXT(" will increase the size of your apk as UE4 will start storing the UV coordinates")
			TEXT(" for each mesh."));
		return false;
	}
#endif

	// Raycast and find 3D Cohtml Views from the WorldDynamic collision type
	FVector Start;
	FVector Direction;
	FVector End;
	if (bProjectionDataObtained)
	{
		// Create a view family for the game viewport
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			Player->ViewportClient->Viewport,
			World->Scene,
			Player->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));


		// Calculate a view where the player is to update the streaming from the players start location
		FVector ViewLocation;
		FRotator ViewRotation;

		FSceneView* SceneView = Player->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, Player->ViewportClient->Viewport);

		if (!SceneView)
		{
			DiscardViewFocusFunction();
			return true;
		}

#if defined(COHTML_UE4_413_SUPPORT)
		const FMatrix InvProjectionMatrix = SceneView->ViewMatrices.GetInvProjMatrix();
#else
		const FMatrix& InvProjectionMatrix = SceneView->ViewMatrices.GetInvProjectionMatrix();
#endif
		FSceneView::DeprojectScreenToWorld(ViewportPositionVec2D, ProjectionData.GetConstrainedViewRect(), SceneView->ViewMatrices.GetInvViewMatrix(), InvProjectionMatrix, Start, Direction);
	}

	End = Start + WORLD_MAX * Direction;
	TArray<FHitResult> HitResults;
	bool bHitSuccessful = false;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.TraceTag = NAME_None;
	CollisionQueryParams.bTraceComplex = true;
#if PLATFORM_ANDROID
	CollisionQueryParams.bReturnFaceIndex = true;
#endif

	switch (LineTraceMode.GetValue())
	{
	case CohtmlInputLineTrace_Single:
		HitResults.Add(FHitResult());
		bHitSuccessful = World->LineTraceSingleByObjectType(HitResults[0], Start, End,
			FCollisionObjectQueryParams(RaycastCollisionChannel), CollisionQueryParams);
		break;
	case CohtmlInputLineTrace_Multi:
		bHitSuccessful = World->LineTraceMultiByObjectType(HitResults, Start, End,
			FCollisionObjectQueryParams(RaycastCollisionChannel), CollisionQueryParams);
		break;
	}

	for (int32_t i = 0; bHitSuccessful && i < HitResults.Num(); ++i)
	{
		FHitResult Hit = HitResults[i];

		if (Hit.Actor == nullptr)
		{
			DiscardViewFocusFunction();
			return true;
		}

		UCohtmlComponent* Component = Hit.Actor->FindComponentByClass<UCohtmlComponent>();

		if (Component == nullptr)
		{
			// An object without UCohtmlComponent component is blocking the input ray
			DiscardViewFocusFunction();
			return true;
		}

		if (!Component->bReceiveInput ||
#if !PLATFORM_ANDROID
			!Component->EnsureMeshData() ||
#endif
			!Component->GetView())
		{
			// This UCohtmlComponent doesn't receive input;
			// Continue along the FHitResult array and try finding one that does.
			continue;
		}

#if PLATFORM_ANDROID
		FVector2D HitUVCoordinates;
		UGameplayStatics::FindCollisionUV(Hit, 0, HitUVCoordinates);
		AdjustUVCoordinates(RaycastTextureAddressMode, HitUVCoordinates.X, HitUVCoordinates.Y);

		cohtml::View* View = Component->GetView();

		if (HandleInWorldInputFunction(Component, View, HitUVCoordinates.X, HitUVCoordinates.Y))
		{
			return true;
		}
#else
		auto NumMeshes = Component->MeshData.Num();
		if (!NumMeshes)
		{
			COHTML_UE_LOG(Warning, TEXT("The Input widget currently supports input on Static meshes only."));
			HandledInputFunction();
			return true;
		}

		for (auto Index = 0u; Index != NumMeshes; ++Index)
		{
			auto& MeshData = Component->MeshData[Index];
			auto MeshComponent = MeshData.Mesh;
			if (!MeshComponent.IsValid())
			{
				continue;
			}
			int32 LODLevelToRaycast = 0;
#if defined(COHTML_UE4_413_SUPPORT)
			UStaticMesh* StaticMesh = MeshComponent->StaticMesh;
#else
			UStaticMesh* StaticMesh = MeshComponent->GetStaticMesh();
#endif
			switch (RaycastQuality)
			{
			case CohtmlRaycastQuality_Fast:
				LODLevelToRaycast = StaticMesh->RenderData->LODResources.Num() - 1;
				break;
			case CohtmlRaycastQuality_Balanced:
				LODLevelToRaycast = StaticMesh->RenderData->LODResources.Num() / 2;
				break;
			case CohtmlRaycastQuality_Accurate:
				LODLevelToRaycast = 0;
				break;
			}

			auto& Indices = MeshData.LODs[LODLevelToRaycast].Indices;
			auto& UVs = MeshData.LODs[LODLevelToRaycast].UVs;
			auto& Positions = MeshData.LODs[LODLevelToRaycast].Positions;
			FIndexArrayView IndexBuffer(Indices.GetData(), Indices.Num(), true);
			if (!UVs.Num() || !IndexBuffer.Num() || !Positions.Num())
			{
				continue;
			}

			FStaticMeshLODResources& LODRes = StaticMesh->RenderData->LODResources[LODLevelToRaycast];
			check(LODRes.GetNumTriangles() == IndexBuffer.Num() / 3);

			FTransform ComponentTransform = MeshComponent->GetComponentTransform();

			FVector StartModelSpace = ComponentTransform.InverseTransformPosition(Start);
			FVector DirectionModelSpace = ComponentTransform.InverseTransformVector(Direction);
			float U, V, Dist;
			if (!IntersectWithRay(StartModelSpace, DirectionModelSpace, UVs, Positions, IndexBuffer, UVChannel, Dist, U, V))
			{
				continue;
			}
			AdjustUVCoordinates(RaycastTextureAddressMode, U, V);

			cohtml::View* View = Component->GetView();

			if (HandleInWorldInputFunction(Component, View, U, V))
			{
				return true;
			}
		}
#endif
	}

	return false;
}

inline FReply SCohtmlInputForward::HandleEventIfNeeded(const FKeyEvent& KeyEvent)
{
	const auto Key = KeyEvent.GetKey();
	bool bPropagate = ((InputPropagationBehaviour & ECohtmlInputPropagationBehaviour::Joystick) && Key.IsGamepadKey()) ||
		((InputPropagationBehaviour & ECohtmlInputPropagationBehaviour::Keyboard) && !Key.IsGamepadKey());
	return bPropagate ? FReply::Unhandled() : FReply::Handled();
}

inline FReply SCohtmlInputForward::HandleEventIfNeeded(const FCharacterEvent& /* CharacterEvent */)
{
	bool bPropagate = (InputPropagationBehaviour & ECohtmlInputPropagationBehaviour::Keyboard);
	return bPropagate ? FReply::Unhandled() : FReply::Handled();
}

FReply SCohtmlInputForward::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	const auto Key = KeyEvent.GetKey();
	if (Key.IsGamepadKey())
	{
		FCohtmlSystemHolder::GetGamepadProvider().UpdateState(KeyEvent, true);
	}
	else
	{
		OnCohtmlInputWidgetKeyDown.Broadcast(Key);
		ProcessKeyEvent(KeyEvent, cohtml::KeyEventData::KeyDown);
	}
	return HandleEventIfNeeded(KeyEvent);
}

FReply SCohtmlInputForward::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	const auto Key = KeyEvent.GetKey();
	if (Key.IsGamepadKey())
	{
		FCohtmlSystemHolder::GetGamepadProvider().UpdateState(KeyEvent, false);
	}
	else
	{
		OnCohtmlInputWidgetKeyUp.Broadcast(Key);
		ProcessKeyEvent(KeyEvent, cohtml::KeyEventData::KeyUp);
	}
	return HandleEventIfNeeded(KeyEvent);
}

FReply SCohtmlInputForward::OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& KeyEvent)
{
	FCohtmlSystemHolder::GetGamepadProvider().UpdateState(KeyEvent);
	return HandleEventIfNeeded(KeyEvent);
}

FReply SCohtmlInputForward::OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent)
{
	ProcessKeyEvent(InCharacterEvent, cohtml::KeyEventData::Char);
	return HandleEventIfNeeded(InCharacterEvent);
}

bool SCohtmlInputForward::SupportsKeyboardFocus() const
{
	return true;
}

FReply SCohtmlInputForward::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InKeyFocusEvent)
{
	if (GamepadBehaviourOnFocusLost == EGamepad::CohtmlUseStateBeforeReset)
	{
		FCohtmlSystemHolder::GetGamepadProvider().ApplyLastGamepadState(InKeyFocusEvent.GetUser());
	}

	bHasKeyboardFocus = true;
	IMEManager->ActivateTextInputMethodSystemContext(true);

	return FReply::Unhandled();
}

void SCohtmlInputForward::OnFocusLost(const FFocusEvent& InKeyboardFocusEvent)
{
	bHasKeyboardFocus = false;

	const auto CurrentUserId = InKeyboardFocusEvent.GetUser();
	FCohtmlSystemHolder::GetGamepadProvider().SaveGamepadState(CurrentUserId);
	GamepadBehaviourOnFocusLost = GamepadBehaviourOnFocusLostDelegate.IsBound() ? GamepadBehaviourOnFocusLostDelegate.Execute(CurrentUserId) : EGamepad::CohtmlResetState;

	if (GamepadBehaviourOnFocusLost == EGamepad::CohtmlResetState || GamepadBehaviourOnFocusLost == EGamepad::CohtmlUseStateBeforeReset)
	{
		FCohtmlSystemHolder::GetGamepadProvider().ResetGamepadState(CurrentUserId);
	}

	IMEManager->ActivateTextInputMethodSystemContext(false);
}

#if defined (COHTML_UE4_412_SUPPORT)
void SCohtmlInputForward::OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath)
#else
void SCohtmlInputForward::OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
#endif
{
}

void SCohtmlInputForward::ProcessKeyEvent(const FInputEvent& Event, cohtml::KeyEventData::EventType Type)
{
	cohtml::KeyEventData KeyData = CohtmlInputHelpers::MakeKeyEvent(Event, Type);

	if (FocusedViewComponent != nullptr && FocusedViewComponent->GetView() != nullptr)
	{
		FocusedViewComponent->GetView()->KeyEvent(KeyData, nullptr, nullptr);
	}
}

void SCohtmlInputForward::SetRaycastCollisionGroup(ECollisionChannel CollisionChannel)
{
	RaycastCollisionChannel = CollisionChannel;
}

void SCohtmlInputForward::SetRaycastTextureAddressMode(TextureAddress TextureAddressMode)
{
	RaycastTextureAddressMode = TextureAddressMode;
}

void SCohtmlInputForward::SetRaycastQuality(ECohtmlInputWidgetRaycastQuality raycastQuality)
{
	this->RaycastQuality = raycastQuality;
}

void SCohtmlInputForward::SetRaycastUVChannel(uint32 uvChannel)
{
	this->UVChannel = uvChannel;
}
