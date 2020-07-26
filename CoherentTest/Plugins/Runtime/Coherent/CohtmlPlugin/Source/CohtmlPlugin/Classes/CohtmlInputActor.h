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

#include "SCohtmlInputForward.h"
#include "CohtmlBackwardsCompatibility.h"

#include <Widgets/SWeakWidget.h>

UENUM(BlueprintType, meta=(DisplayName = "Prysm Keys"))
namespace ECohtmlKeys
{
enum Type
{
	// Using macro's in UENUMs doesn't seem to work so we need to duplicate the key declaration.
	// These are copied from the EKeys structure in InputCoreTypes.h
	LeftMouseButton,
	RightMouseButton,
	MiddleMouseButton,
	ThumbMouseButton,
	ThumbMouseButton2,

	BackSpace,
	Tab,
	Enter,
	Pause,

	CapsLock,
	Escape,
	SpaceBar,
	PageUp,
	PageDown,
	End,
	Home,

	Left,
	Up,
	Right,
	Down,

	Insert,
	Delete,

	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,

	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	NumPadZero,
	NumPadOne,
	NumPadTwo,
	NumPadThree,
	NumPadFour,
	NumPadFive,
	NumPadSix,
	NumPadSeven,
	NumPadEight,
	NumPadNine,

	Multiply,
	Add,
	Subtract,
	Decimal,
	Divide,

	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	NumLock,

	ScrollLock,

	LeftShift,
	RightShift,
	LeftControl,
	RightControl,
	LeftAlt,
	RightAlt,
	LeftCommand,
	RightCommand,

	Semicolon,
	Equals,
	Comma,
	Underscore,
	Period,
	Slash,
	Tilde,
	LeftBracket,
	Backslash,
	RightBracket,
	Quote,

	Unknown UMETA(DisplayName="Unknown"),
};
}

#include "CohtmlInputActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCohtmlInputActorMouseButtonDown, ECohtmlKeys::Type, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCohtmlInputActorMouseButtonUp, ECohtmlKeys::Type, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCohtmlInputActorKeyDown, ECohtmlKeys::Type, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCohtmlInputActorKeyUp, ECohtmlKeys::Type, Key);

UCLASS(BlueprintType, meta=(DisplayName = "Prysm Input Actor"))
class COHTMLPLUGIN_API ACohtmlInputActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Prysm")
	void Initialize(ECollisionChannel CollisionChannel = ECC_WorldDynamic, TextureAddress AddressMode = TA_Wrap, ECohtmlInputWidgetRaycastQuality RaycastQuality = CohtmlRaycastQuality_Accurate, int32 UVChannel = 0);

	UFUNCTION(BlueprintCallable, Category = "Prysm", meta=(DisplayName = "SetInputFocus"))
	void SetCohtmlInputFocus(bool FocusUI);

	UFUNCTION(BlueprintCallable, Category = "Prysm", meta=(DisplayName = "IsFocused"))
	bool IsCohtmlFocused() const;

	UFUNCTION(BlueprintCallable, Category = "Prysm", meta=(DisplayName = "ToggleInputFocus"))
	void ToggleCohtmlInputFocus();

	UFUNCTION(BlueprintCallable, Category = "Prysm", meta=(DisplayName = "SetViewFocus"))
	void SetCohtmlViewFocus(UCohtmlBaseComponent* NewFocusedView);

	UFUNCTION(BlueprintCallable, Category = "Prysm")
	void AlwaysAcceptMouseInput(bool bAccept);

	UFUNCTION(BlueprintCallable, Category = "Prysm")
	void SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Propagation);

	UFUNCTION(BlueprintCallable, Category = "Prysm")
	ECohtmlInputPropagationBehaviour::Type GetInputPropagationBehaviour() const;

	UFUNCTION(BlueprintCallable, Category = "Prysm")
	void SetLineTraceMode(ECohtmlInputWidgetLineTraceMode Mode);

	UPROPERTY(BlueprintAssignable, Category = "Prysm", meta=(DisplayName = "OnInputActorMouseButtonDown"))
	FCohtmlInputActorMouseButtonDown OnCohtmlInputActorMouseButtonDown;

	UPROPERTY(BlueprintAssignable, Category = "Prysm", meta=(DisplayName = "OnInputActorMouseButtonUp"))
	FCohtmlInputActorMouseButtonUp OnCohtmlInputActorMouseButtonUp;

	UPROPERTY(BlueprintAssignable, Category = "Prysm", meta=(DisplayName = "OnInputActorKeyDown"))
	FCohtmlInputActorKeyDown OnCohtmlInputActorKeyDown;

	UPROPERTY(BlueprintAssignable, Category = "Prysm", meta=(DisplayName = "OnInputActorKeyUp"))
	FCohtmlInputActorKeyUp OnCohtmlInputActorKeyUp;

	TSharedPtr<class SCohtmlInputForward> GetWidget();

	FCohtmlGamepadBehaviourOnFocusLostDelegate& GetGamepadBehaviourDelegate();

	void AttachVirtualJoystick(TSharedRef<class SVirtualJoystick> Joystick);
	void DetachVirtualJoystick();

private:
	void OnCohtmlInputWidgetMouseButtonDown(const FKey& Button);
	void OnCohtmlInputWidgetMouseButtonUp(const FKey& Button);
	void OnCohtmlInputWidgetKeyDown(const FKey& Key);
	void OnCohtmlInputWidgetKeyUp(const FKey& Key);

private:
	TSharedPtr<class SCohtmlInputForward> CohtmlInputForwardWidget;
	ECohtmlInputPropagationBehaviour::Type InputPropagationBehaviour;
};
