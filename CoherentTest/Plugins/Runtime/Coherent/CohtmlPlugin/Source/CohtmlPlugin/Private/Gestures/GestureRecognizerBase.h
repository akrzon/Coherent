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
#pragma once

#include <Gestures/GestureRecognizerStates.h>
#include <Gestures/GestureType.h>
#include <cohtml/InputEvents.h>
#include <RenoirBackend/CommonTypes.h>
#include <vector>

namespace gesture
{
class IGestureListener;
class GestureManager;

class GestureRecognizerBase
{
public:
	static const int MAX_TRACKING_TOUCHES = 8;

	GestureRecognizerBase(GestureManager* manager, int priority);
	virtual ~GestureRecognizerBase();
	GestureRecognizerBase(const GestureRecognizerBase&) = delete;
	GestureRecognizerBase& operator=(const GestureRecognizerBase&) = delete;

	GestureRecognizerState GetState() const { return m_State; }

	bool IsEnabled() const { return m_Enabled; }
	void SetEnabled(bool enable) { m_Enabled = enable; }

	int GetPriority() const { return m_Priority; }

	void SetGestureListener(IGestureListener* listener) { m_Listener = listener; }

	struct TouchEventDataWithCurrentPos : public cohtml::TouchEventData
	{
		int CurrentX;
		int CurrentY;

		TouchEventDataWithCurrentPos& operator=(const cohtml::TouchEventData& other)
		{
			cohtml::TouchEventData::operator=(other);
			CurrentX = other.X;
			CurrentY = other.Y;
			return *this;
		}
	};

	virtual bool OnTouchesBegan(const cohtml::TouchEventData* touches, size_t count) { return false; }
	virtual bool OnTouchesMoved(const TouchEventDataWithCurrentPos* touches, size_t count) { return false; }
	virtual bool OnTouchesEnded(const TouchEventDataWithCurrentPos* touches, size_t count) { return false; }

	virtual void OnGestureRecognized() {}

	virtual GestureType GetType() const = 0;

	/// Returns the location of the touches. If there are multiple touches this
	/// will return the centroid of the location.
	renoir::float2 GetTouchLocation() const;

	void RecognizeTouches(const cohtml::TouchEventData* touches, size_t count);

protected:
	void SetState(GestureRecognizerState state);

private:
	void Reset();
	bool ShouldAttemptToRecognize() const;
	bool FilterOnlyTrackedTouchesAndUpdate(const cohtml::TouchEventData* touches, size_t count);

private:
	GestureRecognizerState m_State;
	bool m_Enabled;
	bool m_SentTouchesBegan;
	bool m_SentTouchesMoved;
	bool m_SentTouchesEnded;
	int m_Priority;

protected:
	TouchEventDataWithCurrentPos m_TrackingTouches[MAX_TRACKING_TOUCHES];
	size_t m_TrackingTouchesCount;
	std::vector<TouchEventDataWithCurrentPos> m_TrackedTouchesWithinTouchesToRecognize;
	GestureManager* m_Manager;
	IGestureListener* m_Listener;
};

}
