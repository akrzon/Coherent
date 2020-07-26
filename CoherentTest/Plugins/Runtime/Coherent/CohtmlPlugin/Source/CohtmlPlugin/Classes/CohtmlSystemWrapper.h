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

namespace cohtml
{
	class System;
	class SystemRenderer;
	struct ViewSettings;
}

class UCohtmlBaseComponent;
class IRenderingBackend;

class FCohtmlRendererHolder
{
public:
	FCohtmlRendererHolder(cohtml::SystemRenderer* renderer, IRenderingBackend* backend);
	~FCohtmlRendererHolder();

	cohtml::SystemRenderer* GetRenderer() const;
	IRenderingBackend* GetBackend() const;

private:
	cohtml::SystemRenderer* Renderer;
	IRenderingBackend* Backend;
};

typedef TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe> FCohtmlRendererHolderSharedPtr;
typedef TWeakPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe> FCohtmlRendererHolderWeakPtr;

class FCohtmlSystemWrapper
{
public:
#if PLATFORM_SWITCH
	using CohtmlTimepoint = std::chrono::high_resolution_clock::time_point;
#else
	using CohtmlTimepoint = int64;
#endif

	FCohtmlSystemWrapper(cohtml::System* system);
	~FCohtmlSystemWrapper();
	COHTMLPLUGIN_API cohtml::System* GetSystemPtr() const;
	cohtml::View* CreateView(const cohtml::ViewSettings& info);

	void CreateSystemRenderer(TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe>* rendererOut);

	inline float GetCurrentTimepoint() const
	{
#if PLATFORM_SWITCH
		// FDateTime::Now() internally is using DateTime and the implementation on
		// SWITCH does not have miliseconds, making the time too imprecise and that
		// is why we use chrono time points on SWITCH
		using namespace std::chrono;
		const high_resolution_clock::time_point Now = high_resolution_clock::now();
		return static_cast<float>(duration_cast<nanoseconds>(Now - TimepointAtSystemCreation).count() / 1000000.0);
#else

		return static_cast<float>((FDateTime::Now().GetTicks() - TimepointAtSystemCreation) / ETimespan::TicksPerMillisecond);
#endif
	}
private:
	cohtml::System* System;

	// multiple ACohtmlSystem actors must share the same renderer
	FCohtmlRendererHolderWeakPtr Renderer;
	CohtmlTimepoint TimepointAtSystemCreation;
};