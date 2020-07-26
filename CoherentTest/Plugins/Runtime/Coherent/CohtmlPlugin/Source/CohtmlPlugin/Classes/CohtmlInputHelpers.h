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
#if defined(COHTML_UE4_417_SUPPORT)
#include <Runtime/Core/Public/GenericPlatform/ICursor.h>
#else
#include <Runtime/ApplicationCore/Public/GenericPlatform/ICursor.h>
#endif

#include <cohtml/InputEvents.h>
#include <cohtml/View.h>
#include <cohtml/NodeProxy.h>

namespace CohtmlInputHelpers
{
	bool IsCapsLockOn();

	bool IsNumLockOn();

	bool HasMouseChanged(const FPointerEvent& First, const FPointerEvent& Second, cohtml::MouseEventData::EventType EventType);
	bool HasTouchChanged(const FPointerEvent& First, const FPointerEvent& Second, cohtml::TouchEventData::EventType EventType);

	// When the view loses focus, it should drop hover and active effects
	// otherwise its state may leak (elements will keep being pressed / hovered)
	void ClearViewState(cohtml::View* View, const cohtml::MouseEventData* UnpairedMouseDownEvent);
	void ClearViewState(cohtml::View* View, const cohtml::TouchEventData* UnpairedTouchDownEvent);

	COHTMLPLUGIN_API cohtml::KeyEventData MakeKeyEvent(const FInputEvent& Event, cohtml::KeyEventData::EventType Type);

	COHTMLPLUGIN_API void GetMouseDataFromFPointerEvent(cohtml::MouseEventData& Data,
		const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::MouseEventData::EventType EventType);

	COHTMLPLUGIN_API void GetTouchDataFromFPointerEvent(cohtml::TouchEventData& Data,
		const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, cohtml::TouchEventData::EventType EventType);

	COHTMLPLUGIN_API EMouseCursor::Type TranslateCurrentCohtmlMouseCursor(cohtml::CursorTypes::Cursors Cursor);

	FReply SendCohtmlMouseEvent(cohtml::View* View, const cohtml::MouseEventData& CoherentMouseData);
	FReply SendCohtmlTouchEvent(cohtml::View* View, const cohtml::TouchEventData& CoherentTouchData, class FCohtmlGesturePolicy* GesturePolicy);

}