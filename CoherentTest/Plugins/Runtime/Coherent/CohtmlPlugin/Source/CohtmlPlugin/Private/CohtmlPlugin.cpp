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
#include "CohtmlPluginPrivatePCH.h"
#include "CohtmlPlugin.h"
#include "Containers/Array.h"

#include <cohtml/Logging/ILogHandler.h>
#include <cohtml/Library.h>
#include <cohtml/CohtmlLicense.h>

#include "Async/TaskGraphInterfaces.h"
#include "Async/Async.h"

#if !PLATFORM_WINDOWS && !PLATFORM_XBOXONE
#include <sys/stat.h>
#include <sys/mman.h>

#if PLATFORM_DPX
// No support for MAP_NORESERVE flag on DPX
#define MAP_NORESERVE 0
#endif

#endif

#if PLATFORM_ANDROID
#include <jni.h>
extern JavaVM* GJavaVM;
#endif

#if COHTML_IS_GAMEFACE
	DEFINE_LOG_CATEGORY(LogPrysm);
#else
	DEFINE_LOG_CATEGORY(LogPrysm);
#endif

DEFINE_STAT(STAT_CohtmlTotalCPU);
DEFINE_STAT(STAT_CohtmlViewAdvance);
DEFINE_STAT(STAT_CohtmlPaint);

DEFINE_STAT(STAT_CohtmlCPUMemoryTotal);
DEFINE_STAT(STAT_CohtmlCPUMemoryUnknown);
DEFINE_STAT(STAT_CohtmlCPUMemoryUntagged);
DEFINE_STAT(STAT_CohtmlCPUMemorySystem);
DEFINE_STAT(STAT_CohtmlCPUMemoryLogging);
DEFINE_STAT(STAT_CohtmlCPUMemoryLoader);
DEFINE_STAT(STAT_CohtmlCPUMemoryDOM);
DEFINE_STAT(STAT_CohtmlCPUMemoryDOMStatic);
DEFINE_STAT(STAT_CohtmlCPUMemoryLayout);
DEFINE_STAT(STAT_CohtmlCPUMemoryCSS);
DEFINE_STAT(STAT_CohtmlCPUMemoryCSSStatic);
DEFINE_STAT(STAT_CohtmlCPUMemoryTaskSystemMemory);
DEFINE_STAT(STAT_CohtmlCPUMemoryDisplay);
DEFINE_STAT(STAT_CohtmlCPUMemoryProfiling);
DEFINE_STAT(STAT_CohtmlCPUMemoryHTMLParser);
DEFINE_STAT(STAT_CohtmlCPUMemoryTempAllocator);
DEFINE_STAT(STAT_CohtmlCPUMemoryPoolAllocator);
DEFINE_STAT(STAT_CohtmlCPUMemoryDump);
DEFINE_STAT(STAT_CohtmlCPUMemoryScript);
DEFINE_STAT(STAT_CohtmlCPUMemoryXML);
DEFINE_STAT(STAT_CohtmlCPUMemoryServer);
DEFINE_STAT(STAT_CohtmlCPUMemoryInspector);
DEFINE_STAT(STAT_CohtmlCPUMemorySVG);
DEFINE_STAT(STAT_CohtmlCPUMemoryUriParser);
DEFINE_STAT(STAT_CohtmlCPUMemoryMedia);

IMPLEMENT_MODULE( FCohtmlPlugin, CohtmlPlugin )

FCohtmlPlugin* FCohtmlPlugin::Instance = nullptr;
ICohtmlPlugin::FOnGetLocalizationManager ICohtmlPlugin::OnGetLocalizationManager;
ICohtmlPlugin::FOnGetTextTransformationManager ICohtmlPlugin::OnGetTextTransformationManager;
ICohtmlPlugin::FOnShowVirtualKeyboard ICohtmlPlugin::OnShowVirtualKeyboard;
ICohtmlPlugin::FOnGetFallbackFormats ICohtmlPlugin::OnGetFallbackFormats;
ICohtmlPlugin::FOnURLRequest ICohtmlPlugin::OnURLRequest;

void UpdateCPUMemory(int64 Size, cohtml::MemTags::MemTagsType MemType)
{
	INC_MEMORY_STAT_BY(STAT_CohtmlCPUMemoryTotal, Size);

#define UPDATE_SUBSYSTEM_CPU_MEMORY(Subsystem) \
	case cohtml::MemTags::MemTagsType::Subsystem: \
		INC_MEMORY_STAT_BY_FName(GET_STATFNAME(STAT_CohtmlCPUMemory##Subsystem), Size); \
	break;

	switch (MemType) {
		UPDATE_SUBSYSTEM_CPU_MEMORY(Unknown)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Untagged)
		UPDATE_SUBSYSTEM_CPU_MEMORY(System)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Logging)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Loader)
		UPDATE_SUBSYSTEM_CPU_MEMORY(DOM)
		UPDATE_SUBSYSTEM_CPU_MEMORY(DOMStatic)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Layout)
		UPDATE_SUBSYSTEM_CPU_MEMORY(CSS)
		UPDATE_SUBSYSTEM_CPU_MEMORY(CSSStatic)
		UPDATE_SUBSYSTEM_CPU_MEMORY(TaskSystemMemory)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Display)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Profiling)
		UPDATE_SUBSYSTEM_CPU_MEMORY(HTMLParser)
		UPDATE_SUBSYSTEM_CPU_MEMORY(TempAllocator)
		UPDATE_SUBSYSTEM_CPU_MEMORY(PoolAllocator)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Dump)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Script)
		UPDATE_SUBSYSTEM_CPU_MEMORY(XML)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Server)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Inspector)
		UPDATE_SUBSYSTEM_CPU_MEMORY(SVG)
		UPDATE_SUBSYSTEM_CPU_MEMORY(UriParser)
		UPDATE_SUBSYSTEM_CPU_MEMORY(Media)
	default:
		check(false && TEXT("Trying to track non-existing memory type!"));
	}
}

void DisplayScreenLog(const FColor& Color, const FString& Message)
{
	if (IsInGameThread())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, Color, Message);
	}
	else
	{
		AsyncTask(ENamedThreads::GameThread, [Color, Message]() {
			GEngine->AddOnScreenDebugMessage(-1, 5, Color, Message);
		});
	}
}

class FCohtmlLogger : public cohtml::Logging::ILogHandler
{
public:
	virtual void WriteLog(cohtml::Logging::Severity Severity, const char* Message, size_t)
	{
		switch (Severity)
		{
		case cohtml::Logging::Trace:
			COHTML_UE_LOG(Verbose, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case cohtml::Logging::Debug:
			COHTML_UE_LOG(Log, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case cohtml::Logging::Info:
			COHTML_UE_LOG(Display, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case cohtml::Logging::Warning:
			COHTML_UE_LOG(Warning, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		case cohtml::Logging::AssertFailure:
		case cohtml::Logging::Error:
			COHTML_UE_LOG(Error, TEXT("%s"), UTF8_TO_TCHAR(Message));
			break;
		}

		// On-screen
#if WITH_EDITOR
		if (GEngine && GetDefault<UCohtmlSettings>()->ShowWarningsOnScreen)
		{
			switch (Severity)
			{
			case cohtml::Logging::Warning:
				DisplayScreenLog(FColor::Yellow, Message);
				break;
			case cohtml::Logging::AssertFailure:
			case cohtml::Logging::Error:
				DisplayScreenLog(FColor::Red, Message);
				break;
			}
		}
#endif
	}

	virtual void Assert(const char* Message)
	{
		COHTML_UE_LOG(Error, TEXT("%s"), UTF8_TO_TCHAR(Message));
	}
};

namespace
{
	void OnWorkAvailable(void* /*UserData*/, cohtml::WorkType WorkType, cohtml::TaskFamilyId TaskFamily)
	{
		auto Library = FCohtmlPlugin::Get().GetLibrary();

		switch (WorkType)
		{
		case cohtml::WT_Resources:
			TGraphTask<FCohtmlResourceTask>::CreateTask(nullptr).ConstructAndDispatchWhenReady(Library);
			break;
		case cohtml::WT_Layout:
			TGraphTask<FCohtmlLayoutTask>::CreateTask(nullptr).ConstructAndDispatchWhenReady(Library, TaskFamily);
			break;
		default:
			verify(false && "Unknown work type!");
			break;
		}
	}
} // namespace
class FCohtmlMemoryAllocator : public cohtml::IAllocator
{

public:
	virtual ~FCohtmlMemoryAllocator()
	{}

	virtual void* Allocate(unsigned size, cohtml::MemTags::MemTagsType tag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(static_cast<int64>(size), tag);
#endif
		return FMemory::Malloc(size, DEFAULT_ALIGNMENT);
	}

	virtual void Deallocate(void* ptr, cohtml::MemTags::MemTagsType tag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(-static_cast<int64>(FMemory::GetAllocSize(ptr)), tag);
#endif
		FMemory::Free(ptr);
	}

	virtual void* Reallocate(void* ptr, unsigned newSize, cohtml::MemTags::MemTagsType memtag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(-static_cast<int64>(FMemory::GetAllocSize(ptr)), memtag);
		UpdateCPUMemory(static_cast<int64>(newSize), memtag);
#endif
		return FMemory::Realloc(ptr, newSize, DEFAULT_ALIGNMENT);
	}
	virtual void* AlignedAllocate(unsigned size, unsigned alignment, cohtml::MemTags::MemTagsType memtag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(static_cast<int64>(size), memtag);
#endif
		return FMemory::Malloc(size, alignment);
	}
	virtual void AlignedDeallocate(void* ptr, cohtml::MemTags::MemTagsType memtag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(-static_cast<int64>(FMemory::GetAllocSize(ptr)), memtag);
#endif
		return FMemory::Free(ptr);
	}
	virtual void* VirtualAllocate(void* hint, unsigned size, int protection, int flags, cohtml::MemTags::MemTagsType memtag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(static_cast<int64>(size), memtag);
#endif

#if PLATFORM_WINDOWS || PLATFORM_XBOXONE
		::uint32 winFlags = (((flags & cohtml::VMemFlags::Reserve) != 0) * MEM_RESERVE) |
			(((flags & cohtml::VMemFlags::Commit) != 0) * MEM_COMMIT);

		::uint32 winProt = 0;
		switch (protection)
		{
		case cohtml::VMemProtection::None:
			winProt = PAGE_NOACCESS;
			break;
		case cohtml::VMemProtection::Execute | cohtml::VMemProtection::Read | cohtml::VMemProtection::Write:
			winProt = PAGE_EXECUTE_READWRITE;
			break;
		case cohtml::VMemProtection::Execute | cohtml::VMemProtection::Read:
			winProt = PAGE_EXECUTE_READ;
			break;
		case cohtml::VMemProtection::Read | cohtml::VMemProtection::Write:
			winProt = PAGE_READWRITE;
			break;
		case cohtml::VMemProtection::Read:
			winProt = PAGE_READONLY;
			break;
		}

		if (flags == cohtml::VMemFlags::ProtectionChange)
		{
			assert(flags & cohtml::VMemFlags::Commit);
			assert(hint);
			winFlags = MEM_COMMIT;
		}

		return ::VirtualAlloc(hint, size, winFlags, winProt);
#elif PLATFORM_SWITCH
		void* result = FMemory::Malloc(size);
		FMemory::Memzero(result, size);
		return result;
#else
		int posixProt = PROT_NONE |
			(((protection & cohtml::VMemProtection::Read) != 0) * PROT_READ) |
			(((protection & cohtml::VMemProtection::Write) != 0) * PROT_WRITE) |
			(((protection & cohtml::VMemProtection::Execute) != 0) * PROT_EXEC);

		void* result = nullptr;
		if (flags == cohtml::VMemFlags::ProtectionChange)
		{
			result = mmap(hint, size, posixProt, MAP_FIXED | MAP_PRIVATE | MAP_ANON, -1, 0);
			if (result == MAP_FAILED)
			{
				COHTML_UE_LOG(Error, TEXT("Failed protection change VirtualAlloc: hint: %p size: %d prot: %d flags: %d tag: %d"), hint, size, protection, flags, memtag);
				return nullptr;
			}
		}
		else
		{
			if (flags == cohtml::VMemFlags::Reserve)
			{
				result = mmap(0, size, posixProt, MAP_NORESERVE | MAP_PRIVATE | MAP_ANON, -1, 0);
				if (result == MAP_FAILED)
				{
					COHTML_UE_LOG(Error, TEXT("Failed reserve in VirtualAlloc: hint: %p size: %d prot: %d flags: %d tag: %d"), hint, size, protection, flags, memtag);
					return nullptr;
				}
				madvise(result, size, MADV_DONTNEED);
			}
			else if (flags & cohtml::VMemFlags::Reserve && flags & cohtml::VMemFlags::Commit)
			{
				result = mmap(hint, size, posixProt, MAP_PRIVATE | MAP_ANON, -1, 0);
				if (result == MAP_FAILED)
				{
					COHTML_UE_LOG(Error, TEXT("Failed reserve & commit in VirtualAlloc: hint: %p size: %d prot: %d flags: %d tag: %d"), hint, size, protection, flags, memtag);
					return nullptr;
				}
			}
			else if (flags == cohtml::VMemFlags::Commit)
			{
				if (mprotect(hint, size, posixProt))
				{
					COHTML_UE_LOG(Error, TEXT("Failed commit in VirtualAlloc: hint: %p size: %d prot: %d flags: %d tag: %d"), hint, size, protection, flags, memtag);
					return nullptr;
				}
				result = hint;
				madvise(result, size, MADV_WILLNEED);
				FMemory::Memzero(result, size);
			}
		}
		return result;
#endif
	}
	virtual bool VirtualFree(void* ptr, unsigned size, int flags, cohtml::MemTags::MemTagsType memtag) override
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateCPUMemory(-static_cast<int64>(size), memtag);
#endif

#if PLATFORM_WINDOWS || PLATFORM_XBOXONE
		::uint32 winFlags = 0;
		if (flags == cohtml::VMemFlags::Decommit)
		{
			winFlags = MEM_DECOMMIT;
		}
		else if (flags == cohtml::VMemFlags::Release)
		{
			assert(ptr != nullptr);
			winFlags = MEM_RELEASE;
			size = 0;
		}
		return ::VirtualFree(ptr, size, winFlags) != 0;
#elif PLATFORM_SWITCH
		FMemory::Free(ptr);
		return true;
#else
		bool result = false;
		if (flags == cohtml::VMemFlags::Decommit)
		{
			madvise(ptr, size, MADV_DONTNEED);
			if (mprotect(ptr, size, PROT_NONE))
			{
				//nonzero from mprotect means error
				COHTML_UE_LOG(Error, TEXT("Failed decommit in VirtualFree: ptr: %p size: %d flags: %d tag: %d -> %d"), ptr, size, flags, memtag, result);
				return false;
			}
			result = true;
		}
		else if (flags & cohtml::VMemFlags::Release)
		{
			if (munmap(ptr, size) == (long)MAP_FAILED)
			{
				COHTML_UE_LOG(Error, TEXT("Failed release in VirtualFree: ptr: %p size: %d flags: %d tag: %d -> %d"), ptr, size, flags, memtag, result);
				return false;
			}
			result = true;
		}
		return result;
#endif
	}
};


inline static cohtml::Logging::Severity CohtmlSeverityFromECohtmlSettingsSeverity(
	ECohtmlSettingsSeverity severity)
{
	return cohtml::Logging::Severity(severity);
}

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
	const FString Path = CohtmlGetProjectPluginDir() / LibPath;

#if PLATFORM_WINDOWS
	return FPaths::ConvertRelativePathToFull(Path);
#else //PLATFORM_UWP
	//GetDllHandle for UWP is working with relative paths, thus ConvertRelativePathToFull call is missing here
	return Path;
#endif
}
}
#endif

void FCohtmlPlugin::StartupModule()
{
	FCohtmlPlugin::Instance = this;

	int result = 1;
#if PLATFORM_WINDOWS || (defined(PLATFORM_UWP) && PLATFORM_UWP)
	FString PlatformName;

#if PLATFORM_WINDOWS
	#if PLATFORM_64BITS
	PlatformName = TEXT("Win64");
	#else	//32-bit platform
	PlatformName = TEXT("Win32");
	#endif
#else	//PLATFORM_UWP
	#if PLATFORM_64BITS
	PlatformName = TEXT("UWP64");
	#else	//32-bit platform
	PlatformName = TEXT("UWP32");
	#endif
#endif

	FString CohtmlGamePluginBinariesPath = GetGamePluginBinariesPath(TEXT("Runtime/Coherent/CohtmlPlugin/Binaries/Cohtml") / PlatformName);
	FString CohtmlEngineBinariesPath = GetEngineBinariesPath(TEXT("Binaries/ThirdParty/Cohtml") / PlatformName);
	FString RenoirGamePluginBinariesPath = GetGamePluginBinariesPath(TEXT("Runtime/Coherent/CoherentRenderingPlugin/Binaries/Renoir") / PlatformName);
	FString RenoirEngineBinariesPath = GetEngineBinariesPath(TEXT("Binaries/ThirdParty/Renoir") / PlatformName);

	auto TryGetDllHandleIfDllExists = [](FString FileName) -> HMODULE
	{
		return FPaths::FileExists(FileName) ? (HMODULE)FPlatformProcess::GetDllHandle(*FileName) : 0;
	};

	// CoherentRenderingPlugin may load after this plugin, so try loading RenoirCore before the other dlls
	auto RenoirCoreHandle = TryGetDllHandleIfDllExists(RenoirGamePluginBinariesPath / TEXT("RenoirCore.WindowsDesktop.dll"));
	if (!RenoirCoreHandle)
	{
		RenoirCoreHandle = TryGetDllHandleIfDllExists(RenoirEngineBinariesPath / TEXT("RenoirCore.WindowsDesktop.dll"));
		if (!RenoirCoreHandle)
		{
			COHTML_UE_LOG(Error, TEXT("Unable to load the Renoir library, searched in paths: %s and %s"),
				*RenoirGamePluginBinariesPath, *RenoirEngineBinariesPath);
		}
	}

	if (!LoadedLibraries.Num())
	{
		LoadedLibraries.Push(LibraryInfo(TEXT("HttpServer.WindowsDesktop.dll")));
		LoadedLibraries.Push(LibraryInfo(TEXT("MediaDecoders.WindowsDesktop.dll")));
		LoadedLibraries.Push(LibraryInfo(TEXT("v8_libbase.dll")));
		LoadedLibraries.Push(LibraryInfo(TEXT("v8.dll")));
	}

	#if PLATFORM_WINDOWS
	FPlatformProcess::PushDllDirectory(*CohtmlGamePluginBinariesPath);
	FPlatformProcess::PushDllDirectory(*CohtmlEngineBinariesPath);
	FPlatformProcess::PushDllDirectory(*RenoirGamePluginBinariesPath);
	FPlatformProcess::PushDllDirectory(*RenoirEngineBinariesPath);
	#endif

	for (auto lib = 0; lib < LoadedLibraries.Num(); ++lib)
	{
		auto& library = LoadedLibraries[lib];
		if (library.Module)
			continue;

		library.Module = TryGetDllHandleIfDllExists(CohtmlGamePluginBinariesPath / library.Filename);
		if (!library.Module)
		{
			library.Module = TryGetDllHandleIfDllExists(CohtmlEngineBinariesPath / library.Filename);
			if (!library.Module)
			{
				COHTML_UE_LOG(Warning, TEXT("Unable to load the module %s"), *library.Filename);
			}
		}
	}

	CohtmlModule = TryGetDllHandleIfDllExists(CohtmlGamePluginBinariesPath / TEXT("cohtml.WindowsDesktop.dll"));
	if (!CohtmlModule)
	{
		CohtmlModule = TryGetDllHandleIfDllExists(CohtmlEngineBinariesPath / TEXT("cohtml.WindowsDesktop.dll"));
		if (!CohtmlModule)
		{
			result = 0;
			COHTML_UE_LOG(Error, TEXT("Unable to load the Cohtml library, searched in paths: %s and %s"),
				*CohtmlGamePluginBinariesPath, *CohtmlEngineBinariesPath);
		}
	}

	#if PLATFORM_WINDOWS
	FPlatformProcess::PopDllDirectory(*RenoirEngineBinariesPath);
	FPlatformProcess::PopDllDirectory(*RenoirGamePluginBinariesPath);
	FPlatformProcess::PopDllDirectory(*CohtmlEngineBinariesPath);
	FPlatformProcess::PopDllDirectory(*CohtmlGamePluginBinariesPath);
	#endif

#elif PLATFORM_PS4 || PLATFORM_DPX || PLATFORM_XBOXONE
	CohtmlLoadModule(CohtmlHandle, result);

	if (result < 0)
	{
		COHTML_UE_LOG(Log, TEXT("Plugin load failed, error: "), result);
		result = 0;
	}
	else
	{
		result = 1;
	}
#endif

	if (!!result)
	{
		COHTML_UE_LOG(Log, TEXT("Plugin initialized!"));
	}
	else
	{
		COHTML_UE_LOG(Warning, TEXT("Plugin initialization failed!"));
	}
}

void FCohtmlPlugin::InitializeLibrary()
{
	Allocator.Reset(new FCohtmlMemoryAllocator());
	Logger.Reset(new FCohtmlLogger());

	auto Settings = GetDefault<UCohtmlSettings>();
	cohtml::LibraryParamsWithExternalRenderingLibrary Params;
	Params.LogHandler = Logger.Get();
	Params.LoggingSeverity = CohtmlSeverityFromECohtmlSettingsSeverity(Settings->LogSeverity);
	Params.Allocator = Allocator.Get();
	Params.OnWorkAvailable = &OnWorkAvailable;
	Params.OnWorkAvailableUserData = nullptr;
	Params.ResourceThreadsCountHint = FTaskGraphInterface::Get().GetNumWorkerThreads();
#if PLATFORM_PS4 || PLATFORM_DPX
	Params.SharedLibraryLocation = "/app0/prx/";
#elif PLATFORM_ANDROID
	Params.WritableDirectory = "/sdcard/";
	Params.PlatformParams.JavaVM = GJavaVM;
#endif
#if defined(COHTML_UE4_412_SUPPORT)
	if (CohtmlLibrary != nullptr)
	{
		CohtmlLibrary->Uninitialize();
}
	CohtmlLibrary = cohtml::Library::Initialize(COHTML_LICENSE_KEY, Params);
#else
	CohtmlLibrary.Reset(cohtml::Library::InitializeWithRenderingLibrary(COHTML_LICENSE_KEY, Params, RenderingLibrary));
#endif
}

void FCohtmlPlugin::ShutdownModule()
{
	if(CohtmlLibrary)
	{
		CohtmlLibrary->StopWorkers();
#if defined(COHTML_UE4_412_SUPPORT)
		if (CohtmlLibrary != nullptr)
		{
			CohtmlLibrary->Uninitialize();
			CohtmlLibrary = nullptr;
		}
#else
		CohtmlLibrary.Reset(); //Reset will call Library->Uninitialize();
#endif
	}
	Allocator.Reset();
	Logger.Reset();
	FileSystemReader.Reset();

#if PLATFORM_WINDOWS || (defined(PLATFORM_UWP) && PLATFORM_UWP)
	for (auto lib = 0; lib < LoadedLibraries.Num(); ++lib)
	{
		auto& library = LoadedLibraries[lib];
		if (library.Module)
		{
			FPlatformProcess::FreeDllHandle(library.Module);
			library.Module = nullptr;
		}
	}
	if (CohtmlModule)
	{
		FPlatformProcess::FreeDllHandle(CohtmlModule);
	}
#elif PLATFORM_PS4 || PLATFORM_DPX || PLATFORM_XBOXONE
	int result = 0;
	CohtmlUnloadModule(CohtmlHandle, result);
#endif
	COHTML_UE_LOG(Log, TEXT("Cohtml plugin shut-down!"));
}
