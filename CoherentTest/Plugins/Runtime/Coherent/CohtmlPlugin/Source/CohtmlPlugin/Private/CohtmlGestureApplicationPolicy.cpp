/*
This file is part of Cohtml, a modern user interface library.

Copyright (c) 2012-2018 Coherent Labs AD and/or its licensors. All
rights reserved in all media.

The coded instructions, statements, computer programs, and/or related
material (collectively the "Data") in these files contain confidential
and unpublished information proprietary Coherent Labs and/or its
licensors, which is protected by United States of America federal
copyright law and by international treaties.

This software or source code is supplied under the terms of a license
agreement and nondisclosure agreement with Coherent Labs AD and may
not be copied, disclosed, or exploited except in accordance with the
terms of that agreement. The Data may not be disclosed or distributed to
third parties, in whole or in part, without the prior written consent of
Coherent Labs AD.

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

#include <CohtmlGestureApplicationPolicy.h>

#include <assert.h>

#include <cohtml/InputEvents.h>

#include <memory>

#include <Gestures/PanRecognizer.h>
#include <Gestures/FlingRecognizer.h>
#include <Gestures/GestureTapRecognizer.h>


#if !defined(COHERENT_PLATFORM_DURANGO) && !defined(COHERENT_PLATFORM_ORBIS) && !defined(COHERENT_PLATFORM_UWP)
void FCohtmlGesturePolicy::Initialize(cohtml::View* ViewPtr)
{
	GestureManager.Reset(new gesture::GestureManager);
	std::unique_ptr<gesture::GestureRecognizerBase> PanRecognizer(new gesture::PanRecognizer(GestureManager.Get(), 2));
	PanRecognizer->SetGestureListener(this);
	std::unique_ptr<gesture::GestureRecognizerBase> FlingRecognizer(new gesture::FlingRecognizer(GestureManager.Get(), 1));
	FlingRecognizer->SetGestureListener(this);
	std::unique_ptr<gesture::GestureRecognizerBase> TapRecognizer(new gesture::TapRecognizer(GestureManager.Get(), 0));
	TapRecognizer->SetGestureListener(this);

	GestureManager->AddRecognizer(std::move(PanRecognizer));
	GestureManager->AddRecognizer(std::move(FlingRecognizer));
	GestureManager->AddRecognizer(std::move(TapRecognizer));

	View = ViewPtr;
}

void FCohtmlGesturePolicy::OnPanRecognized(
	const renoir::float2 GestureBeginPos,
	const renoir::float2 CurrentPos,
	const renoir::float2 Delta)
{
	check(View);

	cohtml::GestureEventData EventData;
	EventData.CurrentLocationX = CurrentPos.x;
	EventData.CurrentLocationY = CurrentPos.y;
	EventData.StartLocationX = GestureBeginPos.x;
	EventData.StartLocationY = GestureBeginPos.y;
	EventData.Details.PanDetails.DeltaX = Delta.x;
	EventData.Details.PanDetails.DeltaY = Delta.y;
	EventData.Type = cohtml::GestureEventData::PanStart;
	View->GestureEvent(EventData, nullptr, nullptr);
}

void FCohtmlGesturePolicy::OnPanCompleted(const renoir::float2 EndPos)
{
	check(View);

	cohtml::GestureEventData EventData;
	EventData.CurrentLocationX = EndPos.x;
	EventData.CurrentLocationY = EndPos.y;
	EventData.Type = cohtml::GestureEventData::PanEnd;
	View->GestureEvent(EventData, nullptr, nullptr);
}

void FCohtmlGesturePolicy::OnFlingCompleted(const renoir::float2 EndPos,
	const renoir::float2 FlingStart, float FlingMotionMs)
{
	check(View);

	cohtml::GestureEventData EventData;
	EventData.CurrentLocationX = EndPos.x;
	EventData.CurrentLocationY = EndPos.y;
	EventData.StartLocationX = FlingStart.x;
	EventData.StartLocationY = FlingStart.y;
	EventData.Details.FlingDetails.Duration = FlingMotionMs;
	EventData.Type = cohtml::GestureEventData::Fling;
	View->GestureEvent(EventData, nullptr, nullptr);
}

void FCohtmlGesturePolicy::OnTapRecognized(const renoir::float2 Position)
{
	check(View);

	cohtml::GestureEventData EventData;
	EventData.CurrentLocationX = Position.x;
	EventData.CurrentLocationY = Position.y;
	EventData.Type = cohtml::GestureEventData::Tap;
	View->GestureEvent(EventData, nullptr, nullptr);
}


void FCohtmlGesturePolicy::OnTouchesUpdate(const cohtml::TouchEventData* Events, unsigned Count)
{
	GestureManager->UpdateTouches(Events, Count);
}
#endif