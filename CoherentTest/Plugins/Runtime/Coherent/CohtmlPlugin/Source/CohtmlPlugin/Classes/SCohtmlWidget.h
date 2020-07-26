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
#pragma once

#include <cohtml/InputEvents.h>
#include "CohtmlBackwardsCompatibility.h"

#include <Widgets/Docking/SDockTab.h>
#include <Framework/SlateDelegates.h>
#include <Widgets/Input/IVirtualKeyboardEntry.h>
#include <Framework/Application/IPlatformTextField.h>
#include <Framework/Application/SlateApplication.h>
#include "SCohtmlInputForward.h"
#include "CohtmlRenderWrapper.h"
#include "CohtmlEventHelpers.h"
#include "CohtmlIMEManager.h"

#include <Widgets/SLeafWidget.h>

namespace cohtml
{
	class View;
	class ViewRenderer;
	class IViewListener;
	struct ViewSettings;
}

class FCohtmlGesturePolicy;

class SCohtmlWidget : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SCohtmlWidget)
	{}
	SLATE_END_ARGS()

	COHTMLPLUGIN_API SCohtmlWidget();
	COHTMLPLUGIN_API virtual ~SCohtmlWidget();
	COHTMLPLUGIN_API void Construct(const FArguments& InArgs);
	COHTMLPLUGIN_API void Construct(const FArguments& InArgs, const FString& Url, TSharedPtr<cohtml::IViewListener> Listener);
	COHTMLPLUGIN_API void Construct(const FArguments& InArgs, const cohtml::ViewSettings& Info, const FString& Url, TSharedPtr<cohtml::IViewListener> Listener);

	COHTMLPLUGIN_API virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;

	COHTMLPLUGIN_API virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	COHTMLPLUGIN_API virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	COHTMLPLUGIN_API virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	COHTMLPLUGIN_API virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent) override;
	COHTMLPLUGIN_API virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent) override;
	COHTMLPLUGIN_API virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent) override;

	COHTMLPLUGIN_API virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent) override;
	COHTMLPLUGIN_API virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;
	COHTMLPLUGIN_API virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;
	COHTMLPLUGIN_API virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;

	COHTMLPLUGIN_API virtual FReply OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& KeyEvent) override;
	COHTMLPLUGIN_API virtual FReply OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) override;
	COHTMLPLUGIN_API virtual bool SupportsKeyboardFocus() const override;

	COHTMLPLUGIN_API virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InKeyboardFocusEvent) override;
	COHTMLPLUGIN_API virtual void OnFocusLost(const FFocusEvent& InKeyboardFocusEvent) override;

	COHTMLPLUGIN_API void CreateView(const FString& Url, TSharedPtr<cohtml::IViewListener> Listener, TSharedPtr<cohtml::ITextInputHandler> TextInputHandler, cohtml::IAsyncResourceHandler* Handler);
	COHTMLPLUGIN_API void CreateView(const cohtml::ViewSettings& Info, const FString& Url, TSharedPtr<cohtml::IViewListener> Listener, TSharedPtr<cohtml::ITextInputHandler> TextInputHandler);

	COHTMLPLUGIN_API void RecreateView(const cohtml::ViewSettings& Info, const FString& Url, TSharedPtr<cohtml::IViewListener> Listener, TSharedPtr<cohtml::ITextInputHandler> TextInputHandler);

	COHTMLPLUGIN_API cohtml::View* GetView();
	COHTMLPLUGIN_API cohtml::ViewRenderer* GetViewRenderer();
	COHTMLPLUGIN_API UTextureRenderTarget2D* GetRenderTexture() const;

	FCohtmlGamepadBehaviourOnFocusLostDelegate GamepadBehaviourOnFocusLostDelegate;

	bool HasRequestedView() const;
	enum TextureFilter GetFilter() const;
	void SetFilter(enum TextureFilter InFilter);
	COHTMLPLUGIN_API void SetReceiveInput(bool bInReceiveInput);
	COHTMLPLUGIN_API void SetReceiveInputWhenTransparent(bool bInReceiveInputWhenTransparent);
	COHTMLPLUGIN_API void SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Behaviour);
	void SetIsMaterialGammaCorrected(bool bIsGammaCorrected);
	FCohtmlGesturePolicy* GetGesturePolicy();

	FCohtmlCaretRect CaretRect;
	EMouseCursor::Type CurrentMouseCursor;

private:
	TSharedPtr<class FCoherentSlateElement, ESPMode::ThreadSafe> SlateElement;
	TUniquePtr<FCohtmlRenderWrapper> RenderWrapper;

	// Custom deleter function is used so we can use a forward declaration of GesturePolicy
	struct GesturePolicyDeleter
	{
		void operator()(FCohtmlGesturePolicy* Ptr) const;
	};
	TUniquePtr<FCohtmlGesturePolicy, GesturePolicyDeleter> GesturePolicy;

	FORCEINLINE FReply HandleEventIfNeeded(const FKeyEvent& KeyEvent);
	FORCEINLINE FReply HandleEventIfNeeded(const FCharacterEvent& KeyEvent);

	TUniquePtr<class FCohtmlWidgetIME> IMEManager;
	FIntPoint DPIScaledSize;
	UTextureRenderTarget2D* Texture;
	TEnumAsByte<enum TextureFilter> Filter;
	float DPIScaleBasedOnSize;
	ECohtmlGamepadBehaviourOnFocusLost GamepadBehaviourOnFocusLost;
	bool bReceiveInput;
	bool bNeedsTextureUpdate;
	bool bIsMaterialGammaCorrected;

	cohtml::MouseEventData LastMouseDownData;
	cohtml::TouchEventData LastTouchDownData;
	bool bUnpairedMouseDown;
	bool bUnpairedTouchDown;

	FDelegateHandle ViewportResizedHandle;

	void ProcessKeyEvent(const FInputEvent& Event, cohtml::KeyEventData::EventType Type);
	FReply OnMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::MouseEventData::EventType EventType);
	FReply OnTouchEvent(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent, cohtml::TouchEventData::EventType EventType);
	void OnViewportResized(class FViewport*, uint32);
	void ComputeDPIScaleBasedOnSize();

	bool bIsRedrawingFrame;
	TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> InputPropagationBehaviour;

#if WITH_EDITOR
	bool bIsSlateDrawingViewport;
	FDelegateHandle ActiveTabChangedHandle;
	void OnActiveTabChanged(TSharedPtr<SDockTab>, TSharedPtr<SDockTab>);
	/** The handle to the active timer */
	TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;

	// This is an active timer function that will
	// prevent Slate to enter in sleep mode
	EActiveTimerReturnType ForceUpdateSlate(double InCurrentTime, float InDeltaTime);
#endif
};
