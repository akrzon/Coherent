/*
This file is part of Renoir, a modern graphics library.
Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

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
#include "ICoherentRenderingPlugin.h"
#include <RenoirCore/CoherentRenderingLibrary.h>

#include "CohRenoirBackend.h"

#if !defined(COHERENT_RENDERING_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/AllowWindowsPlatformTypes.h>
#endif

#if PLATFORM_PS4
#include "CoherentRenderingModulePS4.h"
#elif PLATFORM_DPX
#include "CoherentRenderingModulePS5.h"
#elif PLATFORM_XBOXONE
#include "CoherentRenderingModuleXboxOne.h"
#endif

class FCoherentRenderingPlugin : public ICoherentRenderingPlugin
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void InitializeLibrary();
	void InitializeBackend_RenderThread();

#if WITH_EDITOR
	virtual void RegisterSettings() override;
	void UnregisterSettings();
#endif

	static inline FCoherentRenderingPlugin& Get()
	{
		return *Instance;
	}

	virtual renoir::IRenderingLibrary* GetLibrary() override
	{
		RenoirLibraryReferences++;
		if (!RenderingLibrary)
		{
			InitializeLibrary();
		}
#if defined(COHERENT_RENDERING_UE4_412_SUPPORT)
		return RenderingLibrary;
#else
		return RenderingLibrary.Get();
#endif
	}

	virtual IRenderingBackend* GetBackend_RenderThread() override
	{
		if (!Backend)
		{
			InitializeBackend_RenderThread();
		}

		return Backend.Get();
	}

	virtual void ReleaseRenderingLibrary() override
	{
		if (--RenoirLibraryReferences == 0)
		{
			ENQUEUE_COHERENT_RENDERING_COMMAND(
				DestroyPluginRenderingResources,
				{
					Get().DestroyRenderingResources();
					Get().Backend.Reset();
				});
		}
	}

	void DestroyRenderingResources()
	{
		RenderingLibrary->DestroyRenderingResources();
	}

	renoir::IAllocator* GetAllocator()
	{
		return Allocator.Get();
	}
	renoir::Logging::ILogHandler* GetLogger()
	{
		return Logger.Get();
	}
private:
	struct LibraryDeleter
	{
		void operator()(renoir::IRenderingLibrary* Library)
		{
			if (Library != nullptr)
			{
				Library->Uninitialize();
			}
		};
	};
#if WITH_EDITOR
	bool bSettingsRegistered;
#endif
	static FCoherentRenderingPlugin* Instance;
	// The console commands are registered inside the constructor
	// of this object

	TUniquePtr<renoir::IAllocator> Allocator;
	TUniquePtr<renoir::Logging::ILogHandler> Logger;
	int RenoirLibraryReferences;

#if defined(COHERENT_RENDERING_UE4_412_SUPPORT)
	// TUniquePtr does not support custom deleter for UE4 prior to 4.12
	renoir::IRenderingLibrary* RenderingLibrary;
#else
	TUniquePtr<renoir::IRenderingLibrary, LibraryDeleter> RenderingLibrary;
#endif
	TUniquePtr<renoir::IFileManipulator> FileSystemReader;
	TUniquePtr<FCohRenoirBackend> Backend;

#if PLATFORM_WINDOWS|| (defined(PLATFORM_UWP) && PLATFORM_UWP)
	HMODULE CoherentRenderingModule;
#elif PLATFORM_PS4
	CohPS4Handle CoherentRenderingHandle;
#elif PLATFORM_DPX
	CohPS5Handle CoherentRenderingHandle;
#elif PLATFORM_XBOXONE
	CoherentRendeirngXboxOneHandle CoherentRenderingHandle;
#endif
};

#if !defined(COHERENT_RENDERING_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/HideWindowsPlatformTypes.h>
#endif
