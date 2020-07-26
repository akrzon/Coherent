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

#include <Gestures/PanRecognizer.h>
#include <Gestures/IGestureListener.h>
#include <float.h>
#include <algorithm>

// TODO: more generic DPI-aware function
namespace
{
float ScreenPixelsPerCm()
{
	const float INCHES_TO_CM = 2.54f;
	return 160.0f / INCHES_TO_CM;
}
}

namespace gesture
{

PanRecognizer::PanRecognizer(GestureManager* manager, int priority)
	: GestureRecognizerBase(manager, priority)
	, MinimumNumberOfTouches(1)
	, MaximumNumberOfTouches(2)
	, m_TotalDeltaMovementInCm(0.0f)
	, m_PreviousLocation(FLT_MAX, FLT_MAX)
	, m_MinDistanceToPanCm(0.5f)
	, m_StartPoint(FLT_MAX, FLT_MAX)
	, m_EndPoint(FLT_MAX, FLT_MAX)
	, m_DeltaTranslation(0, 0)
{}

PanRecognizer::~PanRecognizer()
{}

bool PanRecognizer::OnTouchesBegan(const cohtml::TouchEventData* touches, size_t count)
{
	// Cancel gesture if extra touches are present
	auto downCount = std::count_if(touches, touches + count, [](const cohtml::TouchEventData& t) {
		return t.Type == cohtml::TouchEventData::TouchDown; });
	if (m_TrackingTouchesCount + downCount > MaximumNumberOfTouches)
	{
		SetState(GestureRecognizerState::CanceledOrDone);
		return false;
	}

	auto state = GetState();

	// add new or additional touches to gesture (allows for two or more touches to be added or removed without ending the pan gesture)
	if (state == GestureRecognizerState::Possible ||
		((state == GestureRecognizerState::Began || state == GestureRecognizerState::RecognizedAndStillRecognizing) &&
			m_TrackingTouchesCount < MaximumNumberOfTouches))
	{
		for (size_t i = 0; i < count; ++i)
		{
			// only add touches in the Began phase
			if (touches[i].Type == cohtml::TouchEventData::TouchDown)
			{
				// Update or Add tracking touch
				size_t j = 0;
				auto newTouchId = touches[i].Id;
				for (; j < m_TrackingTouchesCount; ++j)
				{
					if (m_TrackingTouches[j].Id == newTouchId)
					{
						break;
					}
				}
				m_TrackingTouches[j] = touches[i];
				if (j == m_TrackingTouchesCount)
				{
					++m_TrackingTouchesCount; // Increment count if this is a new touch
				}

				m_StartPoint = renoir::float2(float(touches[0].X), float(touches[0].Y));

				if (m_TrackingTouchesCount == MaximumNumberOfTouches)
				{
					break;
				}
			}
		}

		if (m_TrackingTouchesCount >= MinimumNumberOfTouches && m_TrackingTouchesCount <= MaximumNumberOfTouches)
		{
			m_PreviousLocation = GetTouchLocation();
			if (state != GestureRecognizerState::RecognizedAndStillRecognizing)
			{
				m_TotalDeltaMovementInCm = 0;
				SetState(GestureRecognizerState::Began);
			}
		}
	}

	return false;
}

bool PanRecognizer::OnTouchesMoved(const TouchEventDataWithCurrentPos* touches, size_t count)
{
	//do not engage with touch events if the number of touches is outside our desired constraints
	if (m_TrackingTouchesCount >= MinimumNumberOfTouches && m_TrackingTouchesCount <= MaximumNumberOfTouches)
	{
		auto currentLocation = GetTouchLocation();
		m_DeltaTranslation = m_PreviousLocation - currentLocation;
		float deltaTranslationCm = m_DeltaTranslation.length() / ScreenPixelsPerCm();
		m_PreviousLocation = currentLocation;

		auto state = GetState();
		if (state == GestureRecognizerState::Began)
		{
			m_TotalDeltaMovementInCm += deltaTranslationCm;

			if (std::abs(m_TotalDeltaMovementInCm) >= m_MinDistanceToPanCm)
			{
				SetState(GestureRecognizerState::RecognizedAndStillRecognizing);
			}
		}
		else
		{
			SetState(GestureRecognizerState::RecognizedAndStillRecognizing);
		}
	}

	return false;
}

bool PanRecognizer::OnTouchesEnded(const TouchEventDataWithCurrentPos* touches, size_t count)
{
	m_EndPoint = GetTouchLocation();

	// remove any completed touches
	for (size_t i = 0; i < count; ++i)
	{
		if (touches[i].Type == cohtml::TouchEventData::TouchUp)
		{
			auto id = touches[i].Id;

			// Remove the touch with the specified ID
			int index = -1;
			for (int j = 0, last = int(m_TrackingTouchesCount); j < last; ++j)
			{
				if (m_TrackingTouches[j].Id == id)
				{
					index = j;
					break;
				}
			}
			if (index >= 0)
			{
				for (int j = index, last = int(m_TrackingTouchesCount) - j; j < last; ++j)
				{
					m_TrackingTouches[j] = m_TrackingTouches[j + 1];
				}
				--m_TrackingTouchesCount;
			}
		}
	}

	auto state = GetState();
	// if we still have a touch left continue. no touches means its time to reset
	if (m_TrackingTouchesCount >= MinimumNumberOfTouches)
	{
		m_PreviousLocation = GetTouchLocation();
		SetState(GestureRecognizerState::RecognizedAndStillRecognizing);
	}
	else
	{
		// if we had previously been recognizing fire our complete event
		if (state == GestureRecognizerState::RecognizedAndStillRecognizing)
		{
			// OnGestureCompleted
			if (m_Listener)
			{
				m_Listener->OnPanCompleted(m_EndPoint);
			}
		}

		SetState(GestureRecognizerState::CanceledOrDone);
	}

	return false;
}

void PanRecognizer::OnGestureRecognized()
{
	if (m_Listener)
	{
		m_Listener->OnPanRecognized(m_StartPoint, m_PreviousLocation, m_DeltaTranslation);
	}
}

}
