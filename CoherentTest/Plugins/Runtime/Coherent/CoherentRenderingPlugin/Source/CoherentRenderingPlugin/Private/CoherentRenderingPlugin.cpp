/*
This file is part of Renoir, a modern graphics library.
Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

Copyright (c) 2012-2019 Coherent Labs AD and/or its licensors. All
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

#include "CoherentRenderingPluginPrivatePCH.h"
#include "CoherentRenderingPlugin.h"

#include "Containers/Array.h"
#include "Interfaces/IPluginManager.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif
#include <RenoirCore/Logging/ILogHandler.h>
#include <RenoirCore/CoherentRenderingLibrary.h>

#include "CoherentRenderingFileManipulator.h"
#include "CohRenoirBackend.h"
#include "CoherentRenderingSettings.h"


#if !PLATFORM_WINDOWS && !PLATFORM_XBOXONE
#include <sys/stat.h>
#include <sys/mman.h>
#endif

DEFINE_LOG_CATEGORY(LogCoherentRendering);

DEFINE_STAT(STAT_CoherentRenderingCPUMemory);

IMPLEMENT_MODULE( FCoherentRenderingPlugin, CoherentRenderingPlugin )

#define RENDERING_PLUGIN_NAME "Coherent Rendering"

FCoherentRenderingPlugin* FCoherentRenderingPlugin::Instance = nullptr;

class FRenderingLogger : public renoir::Logging::ILogHandler
{
public:
	virtual void WriteLog(renoir::Logging::Severity Severity, const char* Message, size_t)
	{
		switch (Severity)
		{
		case renoir::Logging::Trace:
			UE_LOG(LogCoherentRendering, Verbose, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case renoir::Logging::Debug:
			UE_LOG(LogCoherentRendering, Log, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case renoir::Logging::Info:
			UE_LOG(LogCoherentRendering, Display, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case renoir::Logging::Warning:
			UE_LOG(LogCoherentRendering, Warning, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case renoir::Logging::AssertFailure:
		case renoir::Logging::Error:
			UE_LOG(LogCoherentRendering, Error, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		}

		// On-screen
//#if WITH_EDITOR
//		if (GEngine && GetDefault<UCohtmlSettings>()->ShowWarningsOnScreen)
//		{
//			switch (Severity)
//			{
//			case renoir::Logging::Warning:
//				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, Message);
//				break;
//			case renoir::Logging::AssertFailure:
//			case renoir::Logging::Error:
//				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, Message);
//				break;
//			}
//		}
//#endif
	}

	virtual void Assert(const char* Message)
	{
		UE_LOG(LogCoherentRendering, Error, TEXT("%s"), UTF8_TO_TCHAR(Message));
	}
};

class FRenderingMemoryAllocator : public renoir::IAllocator
{
public:
	virtual ~FRenderingMemoryAllocator()
	{}

	virtual void* Allocate(unsigned Size) override
	{
#if !UE_BUILD_SHIPPING && STATS
		INC_MEMORY_STAT_BY(STAT_CoherentRenderingCPUMemory, Size);
#endif
		return FMemory::Malloc(Size, DEFAULT_ALIGNMENT);
	}

	virtual void Deallocate(void* Ptr) override
	{
#if !UE_BUILD_SHIPPING && STATS
		DEC_MEMORY_STAT_BY(STAT_CoherentRenderingCPUMemory, FMemory::GetAllocSize(Ptr));
#endif
		FMemory::Free(Ptr);
	}

	virtual void* Reallocate(void* Ptr, unsigned NewSize) override
	{
#if !UE_BUILD_SHIPPING && STATS
		DEC_DWORD_STAT_BY(STAT_CoherentRenderingCPUMemory, FMemory::GetAllocSize(Ptr));
		INC_DWORD_STAT_BY(STAT_CoherentRenderingCPUMemory, NewSize);
#endif
		return FMemory::Realloc(Ptr, NewSize, DEFAULT_ALIGNMENT);
	}
	virtual void* AlignedAllocate(unsigned Size, unsigned Alignment) override
	{
#if !UE_BUILD_SHIPPING && STATS
		INC_MEMORY_STAT_BY(STAT_CoherentRenderingCPUMemory, Size);
#endif
		return FMemory::Malloc(Size, Alignment);
	}
	virtual void AlignedDeallocate(void* Ptr) override
	{
#if !UE_BUILD_SHIPPING && STATS
		DEC_MEMORY_STAT_BY(STAT_CoherentRenderingCPUMemory, FMemory::GetAllocSize(Ptr));
#endif
		return FMemory::Free(Ptr);
	}
};


FORCEINLINE renoir::Logging::Severity RenoirSeverityFromPluginSettingsSeverity(
	ECoherentRenderingSettingsSeverity severity)
{
	return renoir::Logging::Severity(severity);
}

#if WITH_EDITOR
void FCoherentRenderingPlugin::RegisterSettings()
{
	if (bSettingsRegistered)
	{
		return;
	}
#define LOCTEXT_NAMESPACE "RenoirEditorSettings"
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		auto DefaultValues = GetMutableDefault<UCoherentRenderingSettings>();
		SettingsModule->RegisterSettings("Project", "Plugins", RENDERING_PLUGIN_NAME,
			LOCTEXT("RuntimeSettingsName", RENDERING_PLUGIN_NAME),
			LOCTEXT("RuntimeSettingsDescription", "Configure the " RENDERING_PLUGIN_NAME " plugin"),
			DefaultValues
		);
		bSettingsRegistered = true;
	}
#undef LOCTEXT_NAMESPACE
}

void FCoherentRenderingPlugin::UnregisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", RENDERING_PLUGIN_NAME);
	}
}
#endif

#if PLATFORM_WINDOWS || (defined(PLATFORM_UWP) && PLATFORM_UWP)
namespace
{
FString GetEngineBinariesPath(const FString& LibPath)
{
	const FString Path = FPaths::EngineDir() / LibPath;

#if PLATFORM_WINDOWS
	return FPaths::ConvertRelativePathToFull(Path);
#else //PLATFORM_UWP
	//GetDllHandle for UWP is working with relative paths, thus ConvertRelativePathToFull call is missing here
	return Path;
#endif
}

FString GetGamePluginBinariesPath(const FString& LibPath)
{
	const FString Path = CoherentRenderingGetProjectPluginDir() / LibPath;

#if PLATFORM_WINDOWS
	return FPaths::ConvertRelativePathToFull(Path);
#else //PLATFORM_UWP
	//GetDllHandle for UWP is working with relative paths, thus ConvertRelativePathToFull call is missing here
	return Path;
#endif
}
}
#endif

void FCoherentRenderingPlugin::StartupModule()
{
#if !defined(COHERENT_RENDERING_UE4_420_SUPPORT)
	// betwneen UE4.17 and UE4.20 shader source directory mapping is done by Unreal so we don't have to do it
	// and before UE4.17 Shaders have to reside in the Engine/Shaders directory
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("CoherentRenderingPlugin"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/CoherentRenderingPlugin"), PluginShaderDir);
#endif

	FCoherentRenderingPlugin::Instance = this;
	int result = 1;
#if WITH_EDITOR
	bSettingsRegistered = false;
#endif
#if PLATFORM_WINDOWS || (defined(PLATFORM_UWP) && PLATFORM_UWP)
	FString PlatformName;

#if PLATFORM_WINDOWS
#if PLATFORM_64BITS
	PlatformName = TEXT("Win64");
#else	//32-bit platform
	PlatformName = TEXT("Win32");
#endif
#else // PLATFORM_UWP
#if PLATFORM_64BITS
	PlatformName = TEXT("UWP64");
#else	//32-bit platform
	PlatformName = TEXT("UWP32");
#endif
#endif

	FString RenoirGamePluginBinariesPath = GetGamePluginBinariesPath(TEXT("Runtime/Coherent/CoherentRenderingPlugin/Binaries/Renoir") / PlatformName);
	FString RenoirEngineBinariesPath = GetEngineBinariesPath(TEXT("Binaries/ThirdParty/Renoir") / PlatformName);

	auto TryGetDllHandleIfDllExists = [](FString FileName) -> HMODULE
	{
		return FPaths::FileExists(FileName) ? (HMODULE)FPlatformProcess::GetDllHandle(*FileName) : 0;
	};

#if PLATFORM_WINDOWS
	FPlatformProcess::PushDllDirectory(*RenoirGamePluginBinariesPath);
	FPlatformProcess::PushDllDirectory(*RenoirEngineBinariesPath);

	CoherentRenderingModule = TryGetDllHandleIfDllExists(RenoirGamePluginBinariesPath / TEXT("RenoirCore.WindowsDesktop.dll"));
	if (!CoherentRenderingModule)
	{
		CoherentRenderingModule = TryGetDllHandleIfDllExists(RenoirEngineBinariesPath / TEXT("RenoirCore.WindowsDesktop.dll"));
	}

	FPlatformProcess::PopDllDirectory(*RenoirEngineBinariesPath);
	FPlatformProcess::PopDllDirectory(*RenoirGamePluginBinariesPath);
#else // PLATFORM_UWP
	CoherentRenderingModule = TryGetDllHandleIfFileExists(RenoirGamePluginBinariesPath / TEXT("RenoirCore.UWP.dll"));
	if (!CoherentRenderingModule)
	{
		CoherentRenderingModule = TryGetDllHandleIfFileExists(RenoirEngineBinariesPath / TEXT("RenoirCore.UWP.dll"));
	}
#endif

	if (!CoherentRenderingModule)
	{
		result = 0;
		UE_LOG(LogCoherentRendering, Error, TEXT("Unable to load the Renoir library, searched in paths: %s and %s"),
			*RenoirGamePluginBinariesPath, *RenoirEngineBinariesPath);
	}

#elif PLATFORM_PS4 || PLATFORM_DPX || PLATFORM_XBOXONE
	CoherentRenderingLoadModule(CoherentRenderingHandle, result);

	if (result < 0)
	{
		UE_LOG(LogCoherentRendering, Log, TEXT("Plugin load failed, error: "), result);
		result = 0;
	}
	else
	{
		result = 1;
	}
#endif

	if (!!result)
	{
		UE_LOG(LogCoherentRendering, Log, TEXT("Rendering Plugin initialized!"));
	}
	else
	{
		UE_LOG(LogCoherentRendering, Warning, TEXT("Rendering Plugin initialization failed!"));
	}
}

void FCoherentRenderingPlugin::InitializeLibrary()
{
	Allocator.Reset(new FRenderingMemoryAllocator());
	Logger.Reset(new FRenderingLogger());
	FileSystemReader.Reset(new FRenderingFileManipulator());

	auto Settings = GetDefault<UCoherentRenderingSettings>();
	renoir::RenderingLibraryParams Params;
	Params.LogHandler = Logger.Get();
	Params.LoggingSeverity = RenoirSeverityFromPluginSettingsSeverity(Settings->RenderingLogSeverity);
	Params.FileManipulator = FileSystemReader.Get();
	Params.Allocator = Allocator.Get();
	Params.AllowMultipleRenderingThreads = true;

#if defined(COHERENT_RENDERING_UE4_412_SUPPORT)
	if (RenderingLibrary != nullptr)
	{
		RenderingLibrary->Uninitialize();
	}
	RenderingLibrary = renoir::IRenderingLibrary::Initialize(Params);
#else
	RenderingLibrary.Reset(renoir::IRenderingLibrary::Initialize(Params));
#endif
}

void FCoherentRenderingPlugin::InitializeBackend_RenderThread()
{
	Backend.Reset(new FCohRenoirBackend);
	RenderingLibrary->InitializeOnRenderThread(Backend.Get());
}

void FCoherentRenderingPlugin::ShutdownModule()
{
#if WITH_EDITOR
	UnregisterSettings();
#endif
	if(RenderingLibrary)
	{
#if defined(COHERENT_RENDERING_UE4_412_SUPPORT)
		if (RenderingLibrary != nullptr)
		{
			RenderingLibrary->Uninitialize();
			RenderingLibrary = nullptr;
		}
#else
		RenderingLibrary.Reset(); //Reset will call Library->Uninitialize();
#endif
	}
	Allocator.Reset();
	Logger.Reset();
	FileSystemReader.Reset();

#if PLATFORM_WINDOWS || (defined(PLATFORM_UWP) && PLATFORM_UWP)
	if (CoherentRenderingModule)
	{
		FPlatformProcess::FreeDllHandle(CoherentRenderingModule);
	}
#elif PLATFORM_PS4 || PLATFORM_DPX || PLATFORM_XBOXONE
	int result = 0;
	CoherentRenderingUnloadModule(CoherentRenderingHandle, result);
#endif
	UE_LOG(LogCoherentRendering, Log, TEXT("Coherent rendering plugin shut-down!"));
}
