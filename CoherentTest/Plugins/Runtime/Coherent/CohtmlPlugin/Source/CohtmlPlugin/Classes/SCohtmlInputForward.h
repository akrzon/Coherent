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

#include "cohtml/InputEvents.h"
#include "CohtmlBackwardsCompatibility.h"

#include <Widgets/Docking/SDockTab.h>
#include <Widgets/Input/IVirtualKeyboardEntry.h>
#include <Framework/Application/IPlatformTextField.h>
#include <Framework/Application/SlateApplication.h>
#include <Widgets/Input/SVirtualJoystick.h>
#include <SceneView.h>

#include <Engine/Texture.h>

#include "SCohtmlInputForward.generated.h"

namespace cohtml
{
	class View;
	class ViewRenderer;
}

class UCohtmlBaseComponent;

UENUM(meta=(DisplayName = "Prysm Input Widget Raycast Quality"))
enum ECohtmlInputWidgetRaycastQuality
{
	CohtmlRaycastQuality_Fast UMETA(DisplayName = "Fast"),
	CohtmlRaycastQuality_Balanced UMETA(DisplayName = "Balanced"),
	CohtmlRaycastQuality_Accurate UMETA(DisplayName = "Accurate"),
	CohtmlRaycastQuality_MAX,
};

UENUM(meta=(DisplayName = "Prysm Input Widget Line Trace Mode"))
enum ECohtmlInputWidgetLineTraceMode
{
	CohtmlInputLineTrace_Single UMETA(DisplayName = "Single object trace"),
	CohtmlInputLineTrace_Multi UMETA(DisplayName = "Multiple objects trace"),
	CohtmlInputLineTrace_MAX
};

UENUM(meta=(DisplayName = "Prysm Gamepad Behaviour On Focus Lost"))
enum ECohtmlGamepadBehaviourOnFocusLost
{
	/// Set the current state to zero this is default behaviour.
	CohtmlResetState,
	/// Behaviour will be the same as before losing a focus
	CohtmlUseCurrentState,
	/// Will save the last known state, set the current state to zero and
	/// once focus is regained by UI that saved state will be reapplied
	CohtmlUseStateBeforeReset
};

UENUM(BlueprintType, meta=(DisplayName = "Prysm Input Propagation Behaviour"))
namespace ECohtmlInputPropagationBehaviour
{
enum Type
{
	None = 0x0,
	Keyboard = 0x1,
	Joystick = 0x2,
	KeyboardAndJoystick = 0x3
};
}


DECLARE_MULTICAST_DELEGATE_OneParam(FCohtmlInputWidgetMouseButtonDown, const FKey&);
DECLARE_MULTICAST_DELEGATE_OneParam(FCohtmlInputWidgetMouseButtonUp, const FKey&);
DECLARE_MULTICAST_DELEGATE_OneParam(FCohtmlInputWidgetKeyDown, const FKey&);
DECLARE_MULTICAST_DELEGATE_OneParam(FCohtmlInputWidgetKeyUp, const FKey&);
DECLARE_DELEGATE_RetVal_OneParam(ECohtmlGamepadBehaviourOnFocusLost, FCohtmlGamepadBehaviourOnFocusLostDelegate, uint32);

class SCohtmlInputForward : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCohtmlInputForward) {}
	SLATE_ARGUMENT(TWeakObjectPtr<AActor>, Owner)
	SLATE_END_ARGS()

	COHTMLPLUGIN_API SCohtmlInputForward();
	COHTMLPLUGIN_API virtual ~SCohtmlInputForward();

	COHTMLPLUGIN_API void Construct(const FArguments& InArgs);

	COHTMLPLUGIN_API virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	COHTMLPLUGIN_API virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;
	COHTMLPLUGIN_API virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	COHTMLPLUGIN_API virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	COHTMLPLUGIN_API virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;

	COHTMLPLUGIN_API virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;
	COHTMLPLUGIN_API virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;

	COHTMLPLUGIN_API virtual FReply OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& KeyEvent) override;

	COHTMLPLUGIN_API virtual FReply OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) override;
	COHTMLPLUGIN_API virtual bool SupportsKeyboardFocus() const override;

	COHTMLPLUGIN_API virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InKeyboardFocusEvent) override;
	COHTMLPLUGIN_API virtual void OnFocusLost(const FFocusEvent& InKeyboardFocusEvent) override;
#if defined (COHTML_UE4_412_SUPPORT)
	COHTMLPLUGIN_API virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath) override;
#else
	COHTMLPLUGIN_API virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;
#endif

	COHTMLPLUGIN_API void SetRaycastCollisionGroup(ECollisionChannel CollisionChannel);
	COHTMLPLUGIN_API void SetRaycastTextureAddressMode(TextureAddress TextureAddressMode);
	COHTMLPLUGIN_API void SetRaycastQuality(ECohtmlInputWidgetRaycastQuality RaycastQuality);
	COHTMLPLUGIN_API void SetRaycastUVChannel(uint32 UVChannel);

	COHTMLPLUGIN_API void SetAlwaysAcceptMouseInputEvents(bool bAccept);
	COHTMLPLUGIN_API void SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Behaviour);
	COHTMLPLUGIN_API void SetLineTraceMode(ECohtmlInputWidgetLineTraceMode Mode);

	COHTMLPLUGIN_API void RefocusView(UCohtmlBaseComponent* NewFocusedView);

	void AttachVirtualJoystick(TSharedRef<SVirtualJoystick> Joystick);
	void DetachVirtualJoystick();

	FCohtmlInputWidgetMouseButtonDown OnCohtmlInputWidgetMouseButtonDown;
	FCohtmlInputWidgetMouseButtonUp OnCohtmlInputWidgetMouseButtonUp;
	FCohtmlInputWidgetKeyDown OnCohtmlInputWidgetKeyDown;
	FCohtmlInputWidgetKeyUp OnCohtmlInputWidgetKeyUp;

	FCohtmlGamepadBehaviourOnFocusLostDelegate GamepadBehaviourOnFocusLostDelegate;

private:
	void ProcessKeyEvent(const FInputEvent& Event, cohtml::KeyEventData::EventType Type);

	FReply OnMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::MouseEventData::EventType EventType);
	FReply OnTouchEvent(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent, cohtml::TouchEventData::EventType EventType);

	bool HandlePointerEventForHUDViews(
		UWorld* World, FVector2D& ViewportPositionVec2D, bool bProjectionDataObtained, FSceneViewProjectionData& ProjectionData,
		const TFunctionRef<bool(FVector2D&, UCohtmlBaseComponent*, cohtml::View*)> Function);
	bool HandlePointerEventForInWorldViews(
		UWorld* World, ULocalPlayer* Player, FVector2D& ViewportPositionVec2D, bool bProjectionDataObtained, FSceneViewProjectionData& ProjectionData,
		const TFunctionRef<void(void)> DiscardViewFocusFunction,
		const TFunctionRef<void(void)> HandledInputFunction,
		const TFunctionRef<bool(UCohtmlBaseComponent*, cohtml::View*, float, float)> HandleInWorldInputFunction);

	FReply DiscardViewFocus(cohtml::MouseEventData::EventType EventType);
	FReply DiscardViewFocus(cohtml::TouchEventData::EventType EventType);
	inline FReply HandleEventIfNeeded(const FKeyEvent& KeyEvent);
	inline FReply HandleEventIfNeeded(const FCharacterEvent& KeyEvent);

	friend class FCohtmlInputForwardIME;
	TUniquePtr<class FCohtmlInputForwardIME> IMEManager;

	ECohtmlGamepadBehaviourOnFocusLost GamepadBehaviourOnFocusLost;
	ECollisionChannel RaycastCollisionChannel;
	TextureAddress RaycastTextureAddressMode;
	ECohtmlInputWidgetRaycastQuality RaycastQuality;
	uint32 UVChannel;
	bool bHasKeyboardFocus;
	bool bAlwaysAcceptMouseInputEvents;
	TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> InputPropagationBehaviour;
	TEnumAsByte<ECohtmlInputWidgetLineTraceMode> LineTraceMode;

	TWeakObjectPtr<AActor> OwnerActor;
	TWeakObjectPtr<UCohtmlBaseComponent> FocusedViewComponent;
	// The last component to have received any mouse event
	TWeakObjectPtr<UCohtmlBaseComponent> LastTouchedViewComponent;
	bool bAttachedVirtualJoystick;

	// Track mouse downs - we must send a mouse up event when the view
	// loses focus if a given mouse down did not receive the corresponding mouse up
	cohtml::MouseEventData LastMouseDownData;
	cohtml::TouchEventData LastTouchDownData;
	bool bUnpairedMouseDown;
	bool bUnpairedTouchDown;
};
