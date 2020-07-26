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

#include <Gestures/GestureTapRecognizer.h>
#include <Gestures/IGestureListener.h>
#include <algorithm>

namespace gesture
{

TapRecognizer::TapRecognizer(GestureManager* manager, int priority)
	: GestureRecognizerBase(manager, priority)
{
}

TapRecognizer::~TapRecognizer()
{
}

bool TapRecognizer::OnTouchesBegan(const cohtml::TouchEventData* touches, size_t count)
{
	// Cancel gesture if extra touches are present
	auto downCount = std::count_if(touches, touches + count, [](const cohtml::TouchEventData& t) {
		return t.Type == cohtml::TouchEventData::TouchDown; });
	if (m_TrackingTouchesCount + downCount > MaximumNumberOfTouches)
	{
		SetState(GestureRecognizerState::CanceledOrDone);
		return false;
	}

	if (touches[0].Type == cohtml::TouchEventData::TouchDown)
	{
		++m_TrackingTouchesCount;
		m_TrackingTouches[0] = touches[0];
		m_StartPoint = renoir::float2(float(touches[0].X), float(touches[0].Y));
		m_LastTouchTimestamp = high_resolution_clock::now();
	}

	return false;
}

bool TapRecognizer::OnTouchesEnded(const TouchEventDataWithCurrentPos* touches, size_t count)
{
	if (!count)
	{
		return false;
	}
	--m_TrackingTouchesCount;
	renoir::float2 end(float(touches[0].X), float(touches[0].Y));
	if (std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - m_LastTouchTimestamp).count() < TimeMsTolerance &&
		(end - m_StartPoint).length() < TapPxDistanceTolerance)
	{
		SetState(GestureRecognizerState::Recognized);
	}
	else
	{
		SetState(GestureRecognizerState::CanceledOrDone);
	}
	return false;
}

void TapRecognizer::OnGestureRecognized()
{
	if (m_Listener)
	{
		m_Listener->OnTapRecognized(m_StartPoint);
	}
}

}
