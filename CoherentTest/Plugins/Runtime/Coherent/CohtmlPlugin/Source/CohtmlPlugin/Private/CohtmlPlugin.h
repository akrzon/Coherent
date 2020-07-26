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

#include "ICohtmlPlugin.h"
#include "CohtmlConsoleCommands.h"
#include "CohtmlSettings.h"
#include <cohtml/Library.h>

#if !defined(COHTML_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/AllowWindowsPlatformTypes.h>
#endif

#include <ICoherentRenderingPlugin.h>

#if PLATFORM_PS4
#include "CohtmlModulePS4.h"
#elif PLATFORM_DPX
#include "CohtmlModulePS5.h"
#elif PLATFORM_XBOXONE
#include "CohtmlModuleXboxOne.h"
#endif

namespace cohtml
{
class Library;
class IAllocator;
namespace Logging
{
class ILogHandler;
}
}

class FCohtmlPlugin : public ICohtmlPlugin
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void InitializeLibrary();
	inline FCohtmlConsoleCommands& GetConsoleCommands()
	{
		return ConsoleCommands;
	}
	static inline FCohtmlPlugin& Get()
	{
		return *Instance;
	}

	void InitializeRendering()
	{
		RenderingLibrary = ICoherentRenderingPlugin::Load().GetLibrary();
	}

	cohtml::IAllocator* GetAllocator()
	{
		return Allocator.Get();
	}
	cohtml::Logging::ILogHandler* GetLogger()
	{
		return Logger.Get();
	}
	cohtml::Library* GetLibrary()
	{
		if (!CohtmlLibrary)
		{
			InitializeLibrary();
		}
#if defined(COHTML_UE4_412_SUPPORT)
		return CohtmlLibrary;
#else
		return CohtmlLibrary.Get();
#endif
	}
private:
	struct LibraryDeleter
	{
		void operator()(cohtml::Library* Library)
		{
			if (Library != nullptr)
			{
				Library->Uninitialize();
			}
		};
	};

	static FCohtmlPlugin* Instance;
	// The console commands are registered inside the constructor
	// of this object

	FCohtmlConsoleCommands ConsoleCommands;
	TUniquePtr<cohtml::IAllocator> Allocator;
	TUniquePtr<cohtml::Logging::ILogHandler> Logger;
	renoir::IRenderingLibrary* RenderingLibrary;

#if defined(COHTML_UE4_412_SUPPORT)
	// TUniquePtr does not support custom deleter for UE4 prior to 4.12
	cohtml::Library* CohtmlLibrary;
#else
	TUniquePtr<cohtml::Library, LibraryDeleter> CohtmlLibrary;
#endif
	TUniquePtr<cohtml::IFileSystemReader> FileSystemReader;

#if PLATFORM_WINDOWS || (defined(PLATFORM_UWP) && PLATFORM_UWP)
	HMODULE CohtmlModule;

	struct LibraryInfo
	{
		LibraryInfo(const wchar_t* fn)
			: Filename(fn)
			, Module(nullptr)
		{}
		FString Filename;
		HMODULE Module;
	};
	TArray<LibraryInfo> LoadedLibraries;

#elif PLATFORM_PS4
	CohPS4Handle CohtmlHandle;
#elif PLATFORM_DPX
	CohPS5Handle CohtmlHandle;
#elif PLATFORM_XBOXONE
	CohXboxOneHandle CohtmlHandle;
#endif
};

#if !defined(COHTML_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/HideWindowsPlatformTypes.h>
#endif


class FCohtmlLayoutTask
{
	cohtml::Library* CohtmlLibrary;
	cohtml::TaskFamilyId Family;
public:
	FCohtmlLayoutTask(cohtml::Library* InCohtmlLibrary, cohtml::TaskFamilyId InFamily = COHTML_ANY_TASK_FAMILY_ID)
		: CohtmlLibrary(InCohtmlLibrary)
		, Family(InFamily)
	{}

	static const TCHAR* GetTaskName()
	{
		return TEXT("FCohtmlLayoutTask");
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCohtmlLayoutTask, STATGROUP_TaskGraphTasks);
	}
	static ENamedThreads::Type GetDesiredThread()
	{
#if defined(COHTML_UE4_412_SUPPORT)
		return ENamedThreads::AnyThread;
#else
		return ENamedThreads::AnyHiPriThreadHiPriTask;
#endif
	}
	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::FireAndForget;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& CompletionGraphEvent)
	{
		cohtml::Library::HintThreadUsage(cohtml::WT_Layout);
		CohtmlLibrary->ExecuteWork(cohtml::WT_Layout, cohtml::WEM_UntilQueueEmpty, Family);
	}
};

class FCohtmlResourceTask
{
	cohtml::Library* CohtmlLibrary;
public:
	FCohtmlResourceTask(cohtml::Library* Library)
		: CohtmlLibrary(Library)
	{}

	static const TCHAR* GetTaskName()
	{
		return TEXT("FCohtmlResourceTask");
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCohtmlResourceTask, STATGROUP_TaskGraphTasks);
	}
	static ENamedThreads::Type GetDesiredThread()
	{
#if defined(COHTML_UE4_412_SUPPORT)
		return ENamedThreads::AnyThread;
#else
		return ENamedThreads::AnyBackgroundThreadNormalTask;
#endif
	}
	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::FireAndForget;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& CompletionGraphEvent)
	{
		cohtml::Library::HintThreadUsage(cohtml::WT_Resources);
		CohtmlLibrary->ExecuteWork(cohtml::WT_Resources, cohtml::WEM_UntilQueueEmpty);
	}
};