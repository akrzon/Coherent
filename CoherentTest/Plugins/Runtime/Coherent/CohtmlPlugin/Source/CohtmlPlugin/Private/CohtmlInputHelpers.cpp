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
#include "CohtmlInputHelpers.h"

#include "CohtmlInputBindings.h"
#include "CohtmlSystem.h"
#include "CohtmlGestureApplicationPolicy.h"
#include "CohtmlSettings.h"

#if !defined(COHTML_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/AllowWindowsPlatformTypes.h>
#endif

namespace CohtmlInputHelpers
{
	// UE4 and Cohtml have opposing opinions on scrolling directions
	constexpr float INVERT_SCROLL_DIRECTION = -1.0;

	FORCEINLINE bool IsKeyLocationLeft(const FKey& Key)
	{
		return Key == EKeys::LeftShift
			|| Key == EKeys::LeftControl
			|| Key == EKeys::LeftAlt
			|| Key == EKeys::LeftCommand;
	}

	FORCEINLINE bool IsKeyLocationRight(const FKey& Key)
	{
		return Key == EKeys::RightShift
			|| Key == EKeys::RightControl
			|| Key == EKeys::RightAlt
			|| Key == EKeys::RightCommand;
	}

	FORCEINLINE bool IsKeyLocationNumPad(const FKey& Key)
	{
		return Key == EKeys::NumLock
			|| Key == EKeys::NumPadZero
			|| Key == EKeys::NumPadOne
			|| Key == EKeys::NumPadTwo
			|| Key == EKeys::NumPadThree
			|| Key == EKeys::NumPadFour
			|| Key == EKeys::NumPadFive
			|| Key == EKeys::NumPadSix
			|| Key == EKeys::NumPadSeven
			|| Key == EKeys::NumPadEight
			|| Key == EKeys::NumPadNine;
	}

	bool HasMouseChanged(const FPointerEvent& First, const FPointerEvent& Second, cohtml::MouseEventData::EventType EventType)
	{
		return EventType != cohtml::MouseEventData::MouseMove ||
			First.GetEffectingButton() != Second.GetEffectingButton() ||
			First.GetScreenSpacePosition() != Second.GetScreenSpacePosition() ||
			First.IsMouseButtonDown(First.GetEffectingButton()) != Second.IsMouseButtonDown(Second.GetEffectingButton()) ||
			First.GetWheelDelta() != 0.0f ||
			First.IsLeftAltDown() != Second.IsLeftAltDown() ||
			First.IsRightAltDown() != Second.IsRightAltDown() ||
			First.IsLeftControlDown() != Second.IsLeftControlDown() ||
			First.IsRightControlDown() != Second.IsRightControlDown() ||
			First.IsLeftShiftDown() != Second.IsLeftShiftDown() ||
			First.IsRightShiftDown() != Second.IsRightShiftDown() ||
			First.IsLeftCommandDown() != Second.IsLeftCommandDown() ||
			First.IsRightCommandDown() != Second.IsRightCommandDown();
	}

	bool HasTouchChanged(const FPointerEvent& First, const FPointerEvent& Second, cohtml::TouchEventData::EventType EventType)
	{
		return EventType != cohtml::TouchEventData::TouchMove ||
			First.GetEffectingButton() != Second.GetEffectingButton() ||
			First.GetScreenSpacePosition() != Second.GetScreenSpacePosition() ||
			First.IsMouseButtonDown(First.GetEffectingButton()) != Second.IsMouseButtonDown(Second.GetEffectingButton()) ||
			First.GetWheelDelta() != 0.0f ||
			First.IsLeftAltDown() != Second.IsLeftAltDown() ||
			First.IsRightAltDown() != Second.IsRightAltDown() ||
			First.IsLeftControlDown() != Second.IsLeftControlDown() ||
			First.IsRightControlDown() != Second.IsRightControlDown() ||
			First.IsLeftShiftDown() != Second.IsLeftShiftDown() ||
			First.IsRightShiftDown() != Second.IsRightShiftDown() ||
			First.IsLeftCommandDown() != Second.IsLeftCommandDown() ||
			First.IsRightCommandDown() != Second.IsRightCommandDown();
	}

	void ClearViewState(cohtml::View* View, const cohtml::MouseEventData* UnpairedMouseDownEvent)
	{
		// When unfocusing the component, send a mouse move outside the boundaries of the view
		// so that we lose any hover effects
		cohtml::MouseEventData ResetMouseStateEvent;
		ResetMouseStateEvent.Type = cohtml::MouseEventData::MouseMove;

		// If there's a unpaired mouse down, instead send a mouseup outside the boundaries
		// This will remove both hover and active effects
		if (UnpairedMouseDownEvent)
		{
			ResetMouseStateEvent = *UnpairedMouseDownEvent;
			ResetMouseStateEvent.Type = cohtml::MouseEventData::MouseUp;
		}
		else
		{
			// Simulate mousemove and drag or move event will be ignored
			// ToDo: chage that with View->ClearInputFocus(); when available
			ResetMouseStateEvent.MouseModifiers.IsLeftButtonDown = true;
		}
		ResetMouseStateEvent.X = 2 * View->GetWidth();
		ResetMouseStateEvent.Y = 2 * View->GetHeight();
		View->MouseEvent(ResetMouseStateEvent, nullptr, nullptr);
	}

	void ClearViewState(cohtml::View* View, const cohtml::TouchEventData* UnpairedTouchDownEvent)
	{
		// When unfocusing the component, send a mouse move outside the boundaries of the view
		// so that we lose any hover effects
		cohtml::TouchEventData ResetTouchStateEvent;
		ResetTouchStateEvent.Type = cohtml::TouchEventData::TouchMove;

		// If there's a unpaired mouse down, instead send a mouseup outside the boundaries
		// This will remove both hover and active effects
		if (UnpairedTouchDownEvent)
		{
			ResetTouchStateEvent = *UnpairedTouchDownEvent;
			ResetTouchStateEvent.Type = cohtml::TouchEventData::TouchUp;
		}
		ResetTouchStateEvent.X = 2 * View->GetWidth();
		ResetTouchStateEvent.Y = 2 * View->GetHeight();
		View->TouchEvent(&ResetTouchStateEvent, 1, nullptr, nullptr);
	}

	cohtml::KeyEventData MakeKeyEvent(const FInputEvent& Event, cohtml::KeyEventData::EventType Type)
	{
		cohtml::KeyEventData Result;
		Result.Type = Type;
		Result.IsAutoRepeat = false;
		Result.Modifiers.IsShiftDown = Event.IsShiftDown();
		Result.Modifiers.IsCtrlDown = Event.IsControlDown();
		Result.Modifiers.IsAltDown = Event.IsAltDown();
		Result.Modifiers.IsMetaDown = Event.IsCommandDown();

		if (Type == cohtml::KeyEventData::KeyDown || Type == cohtml::KeyEventData::KeyUp)
		{
			Result.IsAutoRepeat = Event.IsRepeat();
			const FKey Key = static_cast<const FKeyEvent&>(Event).GetKey();
			if (IsKeyLocationLeft(Key))
			{
				Result.Location = cohtml::KeyEventData::EventLocation::Left;
			}
			else if (IsKeyLocationRight(Key))
			{
				Result.Location = cohtml::KeyEventData::EventLocation::Right;
			}
			else if (IsKeyLocationNumPad(Key))
			{
				Result.Location = cohtml::KeyEventData::EventLocation::Numpad;
			}

#define GET_COHERENT_VK_FROM_FKEY(FKey, CoherentVK) \
		if (Key == EKeys::FKey) Result.KeyCode = CoherentVK; \

			FKEY_MACRO_ITERATOR(GET_COHERENT_VK_FROM_FKEY);
#undef GET_COHERENT_VK_FROM_FKEY
		}
		else if (Type == cohtml::KeyEventData::Char)
		{
			Result.KeyCode = static_cast<const FCharacterEvent&>(Event).GetCharacter();
		}
		else
		{
			check(false);
			Result.KeyCode = 0;
		}

		return Result;
	}

	void GetMouseDataFromFPointerEvent(cohtml::MouseEventData& Data,
		const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::MouseEventData::EventType EventType)
	{
		Data.Type = EventType;
		Data.WheelX = 0;
		Data.WheelY = 0;
		Data.Modifiers.IsShiftDown = MouseEvent.IsShiftDown();
		Data.Modifiers.IsCtrlDown = MouseEvent.IsControlDown();
		Data.Modifiers.IsAltDown = MouseEvent.IsAltDown();
		Data.Modifiers.IsMetaDown = MouseEvent.IsCommandDown();

		if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			Data.MouseModifiers.IsLeftButtonDown = true;
		}
		if (MouseEvent.IsMouseButtonDown(EKeys::MiddleMouseButton))
		{
			Data.MouseModifiers.IsMiddleButtonDown = true;
		}
		if (MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			Data.MouseModifiers.IsRightButtonDown = true;
		}
		if (MouseEvent.IsMouseButtonDown(EKeys::ThumbMouseButton))
		{
			Data.MouseModifiers.IsBackButtonDown = true;
		}
		if (MouseEvent.IsMouseButtonDown(EKeys::ThumbMouseButton2))
		{
			Data.MouseModifiers.IsForwardButtonDown = true;
		}

		if (EventType == cohtml::MouseEventData::MouseWheel)
		{
			const auto Settings = GetDefault<UCohtmlSettings>();
			if (MouseEvent.IsShiftDown())
			{
				Data.WheelX = int32(MouseEvent.GetWheelDelta()
					* INVERT_SCROLL_DIRECTION * Settings->ScrollDelta);
			}
			else
			{
				Data.WheelY = int32(MouseEvent.GetWheelDelta()
					* INVERT_SCROLL_DIRECTION * Settings->ScrollDelta);
			}
		}
		else if (EventType == cohtml::MouseEventData::MouseDown ||
				 EventType == cohtml::MouseEventData::MouseUp)
		{
			FKey Btn = MouseEvent.GetEffectingButton();
			if (Btn == EKeys::LeftMouseButton)
			{
				Data.Button = cohtml::MouseEventData::ButtonLeft;
			}
			else if (Btn == EKeys::RightMouseButton)
			{
				Data.Button = cohtml::MouseEventData::ButtonRight;
			}
			else if (Btn == EKeys::MiddleMouseButton)
			{
				Data.Button = cohtml::MouseEventData::ButtonMiddle;
			}
			else if (Btn == EKeys::ThumbMouseButton)
			{
				Data.Button = cohtml::MouseEventData::ButtonBack;
			}
			else if (Btn == EKeys::ThumbMouseButton2)
			{
				Data.Button = cohtml::MouseEventData::ButtonForward;
			}
		}
	}

	void GetTouchDataFromFPointerEvent(cohtml::TouchEventData& Data,
		const FGeometry& MyGeometry, const FPointerEvent& TouchEvent, cohtml::TouchEventData::EventType EventType)
	{
		Data.Type = EventType;
		Data.Modifiers.IsShiftDown = TouchEvent.IsShiftDown();
		Data.Modifiers.IsCtrlDown = TouchEvent.IsControlDown();
		Data.Modifiers.IsAltDown = TouchEvent.IsAltDown();
		Data.Modifiers.IsMetaDown = TouchEvent.IsCommandDown();
		Data.Id = TouchEvent.GetPointerIndex();
	}

	bool HandleTouch(cohtml::View* View, FCohtmlGesturePolicy* GesturePolicy, const cohtml::TouchEventData& CoherentTouchData)
	{
		check(GesturePolicy);

		bool bHandlingTouch;
		View->TouchEvent(&CoherentTouchData, 1, nullptr, &bHandlingTouch);

		if (bHandlingTouch || CoherentTouchData.Type == cohtml::TouchEventData::TouchMove)
		{
			GesturePolicy->OnTouchesUpdate(&CoherentTouchData, 1);
		}

		return bHandlingTouch;
	}

	EMouseCursor::Type TranslateCurrentCohtmlMouseCursor(cohtml::CursorTypes::Cursors Cursor)
	{
		using namespace cohtml;
		// This maps our cursors to all cursors available by default in UE4 except the eyedropper
		// which we don't have an equivalent for.
		switch (Cursor)
		{
		case CursorTypes::None:
			return EMouseCursor::None;
		case CursorTypes::Text:
			return EMouseCursor::TextEditBeam;
		case CursorTypes::EWResize:
		case CursorTypes::EResize:
		case CursorTypes::WResize:
			return EMouseCursor::ResizeLeftRight;
		case CursorTypes::NSResize:
		case CursorTypes::NResize:
		case CursorTypes::SResize:
			return EMouseCursor::ResizeUpDown;
		case CursorTypes::NWSEResize:
		case CursorTypes::NWResize:
		case CursorTypes::SEResize:
			return EMouseCursor::ResizeSouthEast;
		case CursorTypes::NESWResize:
		case CursorTypes::NEResize:
		case CursorTypes::SWResize:
			return EMouseCursor::ResizeSouthWest;
		case CursorTypes::Move:
			return EMouseCursor::CardinalCross;
		case CursorTypes::Crosshair:
			return EMouseCursor::Crosshairs;
		case CursorTypes::Pointer:
			return EMouseCursor::Hand;
		case CursorTypes::Grab:
			return EMouseCursor::GrabHand;
		case CursorTypes::Grabbing:
			return EMouseCursor::GrabHandClosed;
		case CursorTypes::NotAllowed:
			return EMouseCursor::SlashedCircle;
		default:
			return EMouseCursor::Default;
		}
	}

	FReply SendCohtmlMouseEvent(cohtml::View* View, const cohtml::MouseEventData& CoherentMouseData)
	{
		bool bHandlingMouse = false;

		View->MouseEvent(CoherentMouseData, nullptr, &bHandlingMouse);

		if (!bHandlingMouse)
		{
			return FReply::Unhandled();
		}

		return FReply::Handled();
	}

	FReply SendCohtmlTouchEvent(cohtml::View* View, const cohtml::TouchEventData& CoherentTouchData, FCohtmlGesturePolicy* GesturePolicy)
	{
		bool HandlingsTouch = HandleTouch(View, GesturePolicy, CoherentTouchData);

		if (!HandlingsTouch)
		{
			return FReply::Unhandled();
		}

		return FReply::Handled();
	}
}

#if !defined(COHTML_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/HideWindowsPlatformTypes.h>
#endif