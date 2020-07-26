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

#include <RenoirBackend/CommonTypes.h>
#include <Gestures/IGestureListener.h>
#include <Gestures/GestureManager.h>

#include "Runtime/Core/Public/Templates/UniquePtr.h"

namespace cohtml
{
class View;
struct TouchEventData;
}

#if !defined(COHERENT_PLATFORM_DURANGO) && !defined(COHERENT_PLATFORM_ORBIS) && !defined(COHERENT_PLATFORM_UWP)
class FCohtmlGesturePolicy
	: public gesture::IGestureListener
{
public:
	void Initialize(cohtml::View* ViewPtr);

	virtual void OnPanRecognized(
		const renoir::float2 GestureBeginPos,
		const renoir::float2 CurrentPos,
		const renoir::float2 Delta) override;
	virtual void OnPanCompleted(const renoir::float2 EndPos) override;
	virtual void OnFlingCompleted(const renoir::float2 EndPos,
		const renoir::float2 FlingStart, float FlingMotionMs) override;
	virtual void OnTapRecognized(const renoir::float2 Position) override;

	void OnTouchesUpdate(const cohtml::TouchEventData* Events, unsigned Count);

private:
	cohtml::View* View = nullptr;
	TUniquePtr<gesture::GestureManager> GestureManager;
};
#else
class FCohtmlGesturePolicy : public gesture::IGestureListener
{
public:
	void Initialize(cohtml::View*) {}
	void OnTouchesUpdate(const cohtml::TouchEventData*, unsigned) {}
};
#endif