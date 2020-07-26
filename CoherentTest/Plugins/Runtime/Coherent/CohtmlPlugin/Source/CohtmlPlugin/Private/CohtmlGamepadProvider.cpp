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
#include "CohtmlGamepadProvider.h"

#include "Runtime/SlateCore/Public/Input/Events.h"
#include "CohtmlSystemWrapper.h"

// Assume 4 axes, 17 buttons as described by the standard W3C gamepad
FCohtmlGamepadState::FCohtmlGamepadState()
{
	AxisValues = ActualAxisValues;
	ButtonValues = ActualButtonValues;
	FMemory::Memset(AxisValues, 0, sizeof(ActualAxisValues));
	FMemory::Memset(ButtonValues, 0, sizeof(ActualButtonValues));
}

void Swap(FCohtmlGamepadState& first, FCohtmlGamepadState& second)
{
	Swap(first.Id, second.Id);
	FMemory::Memswap(first.AxisValues, second.AxisValues, sizeof(first.ActualAxisValues));
	FMemory::Memswap(first.ButtonValues, second.ButtonValues, sizeof(first.ButtonValues));
}

FCohtmlGamepadState::FCohtmlGamepadState(const FCohtmlGamepadState& Other)
{
	Id = Other.Id;
	// The pointers must always refer to the current instance, don't copy them
	AxisValues = ActualAxisValues;
	ButtonValues = ActualButtonValues;
	FMemory::Memcpy(AxisValues, Other.AxisValues, sizeof(ActualAxisValues));
	FMemory::Memcpy(ButtonValues, Other.ButtonValues, sizeof(ActualButtonValues));
}

FCohtmlGamepadState& FCohtmlGamepadState::operator = (FCohtmlGamepadState Other)
{
	Swap(*this, Other);
	return *this;
}

void FCohtmlGamepadProvider::SetActiveSystem(TWeakPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> SystemPtr)
{
	System = SystemPtr;
	if (!System.IsValid())
	{
		ActiveGamepads.Empty();
	}
}


void FCohtmlGamepadProvider::EnsureGamepadIsRegistered(const FKeyEvent& InputEvent)
{
	if (!System.IsValid())
	{
		return;
	}

	if (!ActiveGamepads.Contains(InputEvent.GetUserIndex()))
	{
		FCohtmlGamepadState state;
		state.Id = InputEvent.GetUserIndex();
		ActiveGamepads.Add(InputEvent.GetUserIndex(), state);

		System.Pin()->GetSystemPtr()->RegisterGamepad(state.Id, "UE4 Standard Gamepad",
			FCohtmlGamepadState::AXES_COUNT, FCohtmlGamepadState::BUTTONS_COUNT);
	}
}

namespace
{
int MapGamepadButton(const FKeyEvent& InputEvent)
{
	// Mapping UE4's keys to standard gamepad as defined here
	// http://www.w3.org/TR/gamepad/#remapping
	auto Key = InputEvent.GetKey();

#define CoherentMapGamepadButton(Button, Value) \
	if (Key == EKeys::Button) return Value
	CoherentMapGamepadButton(Gamepad_FaceButton_Bottom, 0);
	CoherentMapGamepadButton(Gamepad_FaceButton_Right, 1);
	CoherentMapGamepadButton(Gamepad_FaceButton_Left, 2);
	CoherentMapGamepadButton(Gamepad_FaceButton_Top, 3);
	CoherentMapGamepadButton(Gamepad_LeftShoulder, 4);
	CoherentMapGamepadButton(Gamepad_RightShoulder, 5);
	CoherentMapGamepadButton(Gamepad_LeftTrigger, 6);
	CoherentMapGamepadButton(Gamepad_RightTrigger, 7);
	CoherentMapGamepadButton(Gamepad_Special_Left, 8);
	CoherentMapGamepadButton(Gamepad_Special_Right, 9);
	CoherentMapGamepadButton(Gamepad_LeftThumbstick, 10);
	CoherentMapGamepadButton(Gamepad_RightThumbstick, 11);
	CoherentMapGamepadButton(Gamepad_DPad_Up, 12);
	CoherentMapGamepadButton(Gamepad_DPad_Down, 13);
	CoherentMapGamepadButton(Gamepad_DPad_Left, 14);
	CoherentMapGamepadButton(Gamepad_DPad_Right, 15);
#undef CoherentMapGamepadButton
	return -1;
}

struct FAxisMapping
{
	int AxisIndex;
	bool NeedsSwap;
};

// Returns the correct HTML axis index and whether it should be swapped
// (the Y axes in UE4 are inverted compared to the HTML standard)
FAxisMapping MapGamepadAxis(const FKeyEvent& InputEvent)
{
	// Mapping UE4's axes to standard gamepad as defined here
	// http://www.w3.org/TR/gamepad/#remapping
	auto Key = InputEvent.GetKey();

#if PLATFORM_XBOXONE
	FAxisMapping Res;
	Res.AxisIndex = -1;
	Res.NeedsSwap = false;

	if (Key == EKeys::Gamepad_LeftX) { Res.AxisIndex = 0; Res.NeedsSwap = false; return Res; }
	if (Key == EKeys::Gamepad_LeftY) { Res.AxisIndex = 1; Res.NeedsSwap = true; return Res; }
	if (Key == EKeys::Gamepad_RightX) { Res.AxisIndex = 2; Res.NeedsSwap = false; return Res; }
	if (Key == EKeys::Gamepad_RightY) { Res.AxisIndex = 3; Res.NeedsSwap = true; return Res; }

	return Res;
#else
#define CoherentMapGamepadAxis(Button, Value, NeedsSwap) \
	if (Key == EKeys::Button) return { Value, NeedsSwap }
	CoherentMapGamepadAxis(Gamepad_LeftX, 0, false);
	CoherentMapGamepadAxis(Gamepad_LeftY, 1, true);
	CoherentMapGamepadAxis(Gamepad_RightX, 2, false);
	CoherentMapGamepadAxis(Gamepad_RightY, 3, true);
#undef CoherentMapGamepadAxis
	return{ -1, false };
#endif
}
}

void FCohtmlGamepadProvider::UpdateState(const FAnalogInputEvent& InputEvent)
{
	EnsureGamepadIsRegistered(InputEvent);
	auto& Gamepad = ActiveGamepads[InputEvent.GetUserIndex()];
	if (InputEvent.GetKey().IsFloatAxis())
	{
		auto Mapping = MapGamepadAxis(InputEvent);
		if (Mapping.AxisIndex >= 0)
		{
			auto AxisValue = Mapping.NeedsSwap ? -InputEvent.GetAnalogValue() : InputEvent.GetAnalogValue();
			// Although the UE4's docs say that their values are in the range [0; 1], that's not really
			// true for axes so need for mapping the value
			Gamepad.ActualAxisValues[Mapping.AxisIndex] = AxisValue;
		}
		System.Pin()->GetSystemPtr()->UpdateGamepadState(Gamepad);
	}
}

void FCohtmlGamepadProvider::UpdateState(const FKeyEvent& InputEvent, bool bIsDown)
{
	EnsureGamepadIsRegistered(InputEvent);
	auto& Gamepad = ActiveGamepads[InputEvent.GetUserIndex()];
	if (InputEvent.GetKey().IsGamepadKey())
	{
		auto ButtonIndex = MapGamepadButton(InputEvent);
		if (ButtonIndex >= 0)
		{
			Gamepad.ActualButtonValues[ButtonIndex] = 1 * bIsDown;
		}
		System.Pin()->GetSystemPtr()->UpdateGamepadState(Gamepad);
	}
}

void FCohtmlGamepadProvider::ResetGamepadState(uint32 UserId)
{
	if (auto CurrentGamepad = ActiveGamepads.Find(UserId))
	{
		const auto Id = CurrentGamepad->Id;
		*CurrentGamepad = FCohtmlGamepadState();
		CurrentGamepad->Id = Id;
		System.Pin()->GetSystemPtr()->UpdateGamepadState(*CurrentGamepad);
	}
}

void FCohtmlGamepadProvider::SaveGamepadState(uint32 UserId)
{
	if (auto ActiveState = ActiveGamepads.Find(UserId))
	{
		GamepadsBeforeLoseFocus.FindOrAdd(UserId) = *ActiveState;
	}
}

void FCohtmlGamepadProvider::ApplyLastGamepadState(uint32 UserId)
{
	auto OldState = GamepadsBeforeLoseFocus.Find(UserId);
	auto CurrentState = ActiveGamepads.Find(UserId);

	if (OldState && CurrentState)
	{
		*CurrentState = *OldState;
		System.Pin()->GetSystemPtr()->UpdateGamepadState(*CurrentState);
	}
}
