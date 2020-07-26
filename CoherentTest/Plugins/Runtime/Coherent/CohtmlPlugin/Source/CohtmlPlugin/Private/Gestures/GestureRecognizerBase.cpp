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

#include <Gestures/GestureRecognizerBase.h>

namespace gesture
{

GestureRecognizerBase::GestureRecognizerBase(GestureManager* manager, int priority)
	: m_State(GestureRecognizerState::Possible)
	, m_Enabled(true)
	, m_SentTouchesBegan(false)
	, m_SentTouchesMoved(false)
	, m_SentTouchesEnded(false)
	, m_Priority(priority)
	, m_TrackingTouchesCount(0)
	, m_Manager(manager)
	, m_Listener(nullptr)
{}

GestureRecognizerBase::~GestureRecognizerBase()
{}

void GestureRecognizerBase::SetState(GestureRecognizerState state)
{
	m_State = state;

	if (state == GestureRecognizerState::Recognized || state == GestureRecognizerState::RecognizedAndStillRecognizing)
	{
		OnGestureRecognized();
	}

	if (state == GestureRecognizerState::Recognized || state == GestureRecognizerState::CanceledOrDone)
	{
		Reset();
	}
}

void GestureRecognizerBase::Reset()
{
	m_State = GestureRecognizerState::Possible;
	m_TrackingTouchesCount = 0;
}

bool GestureRecognizerBase::ShouldAttemptToRecognize() const
{
	return m_Enabled &&
		m_State != GestureRecognizerState::CanceledOrDone &&
		m_State != GestureRecognizerState::Recognized;
}

bool GestureRecognizerBase::FilterOnlyTrackedTouchesAndUpdate(const cohtml::TouchEventData* touches, size_t count)
{
	m_TrackedTouchesWithinTouchesToRecognize.clear();

	for (size_t i = 0; i < count; ++i)
	{
		auto& t1 = touches[i];
		for (size_t j = 0; j < m_TrackingTouchesCount; ++j)
		{
			if (t1.Id == m_TrackingTouches[j].Id)
			{
				auto& tracked = m_TrackingTouches[j];
				m_TrackedTouchesWithinTouchesToRecognize.emplace_back();
				auto& trackedWithin = m_TrackedTouchesWithinTouchesToRecognize.back();

				trackedWithin = t1;
				// Update the tracked touch
				tracked.CurrentX = t1.X;
				tracked.CurrentY = t1.Y;
			}
		}
	}

	return m_TrackedTouchesWithinTouchesToRecognize.size() > 0;
}

renoir::float2 GestureRecognizerBase::GetTouchLocation() const
{
	float x = 0;
	float y = 0;
	float k = 0;

	for (size_t i = 0; i < m_TrackingTouchesCount; ++i)
	{
		x += m_TrackingTouches[i].CurrentX;
		y += m_TrackingTouches[i].CurrentY;
		k += 1.0f;
	}

	if (k > 0)
	{
		return renoir::float2(x / k, y / k);
	}
	else
	{
		return renoir::float2(0 ,0);
	}
}

void GestureRecognizerBase::RecognizeTouches(const cohtml::TouchEventData* touches, size_t count)
{
	if (!ShouldAttemptToRecognize())
	{
		return;
	}

	m_SentTouchesBegan = false;
	m_SentTouchesMoved = false;
	m_SentTouchesEnded = false;

	for (size_t i = 0; i < count; ++i)
	{
		auto& touch = touches[i];

		switch (touch.Type)
		{
		case cohtml::TouchEventData::TouchDown:
			if (!m_SentTouchesBegan)
			{
				OnTouchesBegan(touches, count);
				m_SentTouchesBegan = true;
			}
			break;
		case cohtml::TouchEventData::TouchMove:
			if (!m_SentTouchesMoved && FilterOnlyTrackedTouchesAndUpdate(touches, count))
			{
				OnTouchesMoved(m_TrackedTouchesWithinTouchesToRecognize.data(), m_TrackedTouchesWithinTouchesToRecognize.size());
				m_SentTouchesMoved = true;
			}
			break;
		case cohtml::TouchEventData::TouchUp:
			if (!m_SentTouchesEnded && FilterOnlyTrackedTouchesAndUpdate(touches, count))
			{
				OnTouchesEnded(m_TrackedTouchesWithinTouchesToRecognize.data(), m_TrackedTouchesWithinTouchesToRecognize.size());
				m_SentTouchesEnded = true;
			}
			break;
		}
	}
}

}
