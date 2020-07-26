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
#include "CohtmlSystemHolder.h"

#include <cohtml/Library.h>
#include <cohtml/System.h>

#include "CohtmlPlugin.h"
#include "CohtmlSystemWrapper.h"
#include "CohtmlSettings.h"
#include "CohtmlGameHUD.h"
#include "CohtmlFileHandler.h"
#include "ICoherentRenderingPlugin.h"
#include "CohtmlLocalizationManager.h"
#include "CohtmlTextTransformationManager.h"

#include "Misc/FeedbackContext.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/PlatformFile.h"
#include "Misc/OutputDeviceError.h"
#include "Containers/StringConv.h"


extern FString CohtmlSharedLibPath;

TWeakPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> FCohtmlSystemHolder::s_System;
TUniquePtr<cohtml::ILocalizationManager> FCohtmlSystemHolder::s_LocalizationManager;
TUniquePtr<cohtml::ITextTransformationManager> FCohtmlSystemHolder::s_TextTransformationManager;
FCohtmlGamepadProvider FCohtmlSystemHolder::s_GamepadProvider;
FCohtmlLiveViews FCohtmlSystemHolder::s_LiveViews;

static FCohtmlFileHandler* s_ResourceHandler = nullptr;

namespace
{
FString CohtmlImageTypeToString(ECohtmlImageFormat type)
{
	switch (type)
	{
	case ECohtmlImageFormat::DDS:
		return "dds";
	case ECohtmlImageFormat::TGA:
		return "tga";
	case ECohtmlImageFormat::JPEG:
		return "jpeg";
	case ECohtmlImageFormat::PSD:
		return "psd";
	case ECohtmlImageFormat::BMP:
		return "bmp";
	case ECohtmlImageFormat::PNG:
		return "png";
	case ECohtmlImageFormat::ASTC:
		return "astc";
	case ECohtmlImageFormat::PKM:
		return "pkm";
	case ECohtmlImageFormat::KTX:
		return "ktx";
	case ECohtmlImageFormat::SVG:
		return "svg";
	default:
		COHTML_UE_LOG(Error, TEXT("Unknown image fallback format detected"));
		return "";
	}
};

TArray<char> GetFStringAsANSI(const FString& InString)
{
	auto Conv = StringCast<ANSICHAR>(*InString);
	TArray<char> Buffer(Conv.Get(), Conv.Length());
	Buffer.Add('\0');
	return Buffer;
}


cohtml::SystemSettings::FallBackFormats::FallBackFormat GetCohtmlFallbackFormat(const FCohtmlConvertedFallbackFormat& InFormat)
{
	cohtml::SystemSettings::FallBackFormats::FallBackFormat result;
	result.BaseFormat = InFormat.BaseFormat.GetData();
	result.Extensions = InFormat.GetAsCharArrays();
	result.ExtensionsSize = InFormat.FallbackFormats.Num();

	return result;
}

TArray<FOverridableFallbackFormat> GetOverridableFormats(const TArray<FSingleFormatFallbacks>& PluginFallbackSettings)
{
	TArray<FOverridableFallbackFormat> UserFallbackFormats;
	for (const FSingleFormatFallbacks& FormatFallback : PluginFallbackSettings)
	{
		FOverridableFallbackFormat UserFallback;
		UserFallback.BaseFormat = CohtmlImageTypeToString(FormatFallback.BaseFormat);
		for (auto PossibleFallback : FormatFallback.PossibleFallbacks)
		{
			UserFallback.FallbackFormats.Add(CohtmlImageTypeToString(PossibleFallback));
		}
		UserFallbackFormats.Add(UserFallback);
	}
	return UserFallbackFormats;
}

// Converts the fallback types from FString to C-style ANSI strings
TArray<FCohtmlConvertedFallbackFormat> GetANSIConvertedFallbackFormats(const TArray<FOverridableFallbackFormat>& InFallbacks)
{
	// The Fallback image formats use ANSI encoding. Initially we keep
	// them in FString(TCHAR), so that they're easy to override for clients.
	// We need to convert them to C-style ANSI strings and keep them alive
	// until the creation of the system, in order to pass them to Cohtml.
	TArray<FCohtmlConvertedFallbackFormat> ConvertedFallbackFormats;
	for (const FOverridableFallbackFormat& InUserFallbackStruct : InFallbacks)
	{
		FCohtmlConvertedFallbackFormat ConvertedFallback;
		ConvertedFallback.BaseFormat = GetFStringAsANSI(InUserFallbackStruct.BaseFormat);
		for (auto UserFallback : InUserFallbackStruct.FallbackFormats)
		{
			ConvertedFallback.FallbackFormats.Add(GetFStringAsANSI(UserFallback));
		}
		ConvertedFallbackFormats.Add(ConvertedFallback);
	}
	return ConvertedFallbackFormats;
}

// Creates the structures we need to pass to Cohtml from the available ANSI-converted fallback formats
TArray<cohtml::SystemSettings::FallBackFormats::FallBackFormat> CreateCohtmlFallbackStructures(const TArray<FCohtmlConvertedFallbackFormat>& inFormats)
{
	TArray<cohtml::SystemSettings::FallBackFormats::FallBackFormat> CohtmlFallbackFormats;
	for (const FCohtmlConvertedFallbackFormat& ConvertedFallbackFormat : inFormats)
	{
		cohtml::SystemSettings::FallBackFormats::FallBackFormat NewFallBackFormat = GetCohtmlFallbackFormat(ConvertedFallbackFormat);
		CohtmlFallbackFormats.Add(NewFallBackFormat);
	}
	return CohtmlFallbackFormats;
}
}
TSharedPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> FCohtmlSystemHolder::CreateSystem()
{
	if (s_System.IsValid())
		return s_System.Pin();

	using namespace cohtml;

	auto DefaultSettings = GetDefault<UCohtmlSettings>();
	if (!s_ResourceHandler)
	{
		s_ResourceHandler = new FCohtmlFileHandler();
	}
	s_ResourceHandler->LoadAtlasMetaData();

	// Init system
	SystemSettings settings;
#if !defined(COHTML_UE4_420_SUPPORT) && PLATFORM_XBOXONE
	if (DefaultSettings->DevToolsPort != DEFAULT_DEVTOOLS_PORT)
	{
		COHTML_UE_LOG(Warning, TEXT("Invalid debugger port set for Durango - %d.")
			TEXT("You can change it from %s -> Options -> Dev Tools Port.")
			TEXT("Defaulting to port %d."),
			DefaultSettings->DevToolsPort, COHTML_PRODUCT, DEFAULT_DEVTOOLS_PORT);
		settings.DebuggerPort = DEFAULT_DEVTOOLS_PORT;
	}
	else
	{
		settings.DebuggerPort = DefaultSettings->DevToolsPort;
	}
#else
	settings.DebuggerPort = DefaultSettings->DevToolsPort;
#endif
	settings.EnableDebugger = settings.DebuggerPort != -1 ? true : false;
	settings.ResourceHandler = s_ResourceHandler;
	if (DefaultSettings->EnableLocalization)
	{
		auto& LocalizationManagerOverride = ICohtmlPlugin::Get().OnGetLocalizationManager;
		if (LocalizationManagerOverride.IsBound())
		{
			settings.LocalizationManagerInstance = LocalizationManagerOverride.Execute();
		}
		else
		{
			s_LocalizationManager.Reset(new FCohtmlLocalizationManager);
			settings.LocalizationManagerInstance = s_LocalizationManager.Get();
		}
	}

	auto& TextTransformationOverride = ICohtmlPlugin::Get().OnGetTextTransformationManager;
	if (TextTransformationOverride.IsBound())
	{
		settings.TextTransformationManager = TextTransformationOverride.Execute();
	}
	else
	{
		s_TextTransformationManager.Reset(new FCohtmlTextTransformationManager);
		settings.TextTransformationManager = s_TextTransformationManager.Get();
	}

	auto OverridableFallbackFormats = GetOverridableFormats(DefaultSettings->FallbacksForAllFormats);

	auto FallbackFormatsOverride = ICohtmlPlugin::Get().OnGetFallbackFormats;
	if (FallbackFormatsOverride.IsBound())
	{
		FallbackFormatsOverride.Execute(OverridableFallbackFormats);
	}

	auto ANSIFallbackFormats = GetANSIConvertedFallbackFormats(OverridableFallbackFormats);
	auto FormatsToReturn = CreateCohtmlFallbackStructures(ANSIFallbackFormats);

	settings.Formats.FormatsSize = FormatsToReturn.Num();
	settings.Formats.Formats = FormatsToReturn.GetData();

	FCohtmlPlugin::Get().InitializeRendering();
	cohtml::System* System = FCohtmlPlugin::Get().GetLibrary()->CreateSystem(settings);

	if (!System)
	{
		return TSharedPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe>();
	}

	const auto FontDirectory = CohtmlGetProjectContentDir() / TEXT("Fonts");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DirectoryExists(*FontDirectory))
	{
		System->AddFontsFromFolder(TCHAR_TO_UTF8(*FontDirectory));
	}
	System->SetDefaultFallbackFontName("Droid Sans");

	TSharedPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> result(new FCohtmlSystemWrapper(System));

	s_System = TWeakPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe>(result);
	s_GamepadProvider.SetActiveSystem(s_System);
	return result;
}

void FCohtmlSystemHolder::DestroySystem(cohtml::System* nakedSystem)
{
	s_System.Reset();
	s_GamepadProvider.SetActiveSystem(TWeakPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe>(nullptr));
	if (nakedSystem)
	{
		nakedSystem->Destroy();
	}
}

bool FCohtmlSystemHolder::IsReady()
{
	return s_System.IsValid();
}

bool FCohtmlSystemHolder::IsLiveViewRegistered(const FString& Url)
{
	bool bRegisteredButNotInBackend = s_LiveViews.UrlHandlesNotInBackend.ContainsByPredicate([&Url](const TPair<FString, uint32_t>& UrlHandlePair)
	{
		return UrlHandlePair.Key == Url;
	});
	return bRegisteredButNotInBackend || s_LiveViews.URLs.Contains(Url);
}

void FCohtmlSystemHolder::RegisterLiveView(const FString& Url)
{
	s_LiveViews.UrlHandlesNotInBackend.Push(TPairInitializer<FString, uint32_t>(Url, s_LiveViews.s_NextLiveViewHandle));
	++s_LiveViews.s_NextLiveViewHandle;
}

void FCohtmlSystemHolder::UnregisterLiveView(const FString& Url)
{
	auto Index = s_LiveViews.URLs.Find(Url);
	// Index might be INDEX_NONE if we've called ResetLiveViewTrackingData
	// but the backend still hasn't destroyed the textures
	if (Index != INDEX_NONE)
	{
		s_LiveViews.URLs.RemoveAt(Index);
		s_LiveViews.Handles.RemoveAt(Index);
	}
}
void FCohtmlSystemHolder::LiveViewReachedBackend(const FString& Url)
{
	auto Index = s_LiveViews.UrlHandlesNotInBackend.IndexOfByPredicate([&Url](const TPair<FString, uint32_t>& UrlHandlePair)
	{
		return UrlHandlePair.Key == Url;
	});
	check(Index != INDEX_NONE);
	s_LiveViews.URLs.Add(Url);
	s_LiveViews.Handles.Add(s_LiveViews.UrlHandlesNotInBackend[Index].Value);
	s_LiveViews.UrlHandlesNotInBackend.RemoveAt(Index);
}

void FCohtmlSystemHolder::ResetLiveViewTrackingData()
{
	s_LiveViews.URLs.Empty();
	s_LiveViews.Handles.Empty();
	s_LiveViews.UrlHandlesNotInBackend.Empty();
}

unsigned int* FCohtmlSystemHolder::GetLiveViewHandles()
{
	return s_LiveViews.Handles.GetData();
}

int FCohtmlSystemHolder::GetLiveViewsNumber()
{
	check(s_LiveViews.URLs.Num() == s_LiveViews.Handles.Num());
	return s_LiveViews.URLs.Num();
}

unsigned int FCohtmlSystemHolder::GetLiveViewHandle(const FString& Url)
{
	auto NotInBackendIndex = s_LiveViews.UrlHandlesNotInBackend.IndexOfByPredicate([&Url](const TPair<FString, uint32_t>& UrlHandlePair)
	{
		return UrlHandlePair.Key == Url;
	});
	check(s_LiveViews.URLs.Find(Url) != INDEX_NONE || NotInBackendIndex != INDEX_NONE);
	if (NotInBackendIndex != INDEX_NONE)
	{
		return s_LiveViews.UrlHandlesNotInBackend[NotInBackendIndex].Value;
	}
	return s_LiveViews.Handles[s_LiveViews.URLs.Find(Url)];
}

FCohtmlGamepadProvider& FCohtmlSystemHolder::GetGamepadProvider()
{
	return s_GamepadProvider;
}

FCohtmlSystemWrapper::FCohtmlSystemWrapper(cohtml::System* system)
	: System(system)
	, TimepointAtSystemCreation(
#if PLATFORM_SWITCH
		std::chrono::high_resolution_clock::now())
#else
		FDateTime::Now().GetTicks())
#endif
{}

FCohtmlSystemWrapper::~FCohtmlSystemWrapper()
{
	FCohtmlSystemHolder::DestroySystem(System);
}

cohtml::System* FCohtmlSystemWrapper::GetSystemPtr() const
{
	return System;
}

cohtml::View* FCohtmlSystemWrapper::CreateView(const cohtml::ViewSettings& info)
{
	auto View = System->CreateView(info);
	return View;
}

void FCohtmlSystemWrapper::CreateSystemRenderer(TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe>* RendererOut)
{
	using namespace cohtml;

	ENQUEUE_COHTML_RENDERING_COMMAND_THREEPARAMETER(
		CreateSystemRendererRT,
		cohtml::System*, SystemIn, System,
		FCohtmlRendererHolderSharedPtr*, RendererHolder, RendererOut,
		FCohtmlRendererHolderWeakPtr*, WeakRendererOut, &Renderer,
		{
			auto ExistingRenderer = WeakRendererOut->Pin();
			if (ExistingRenderer.IsValid())
			{
				*RendererHolder = ExistingRenderer;
				return;
			}
			SystemRendererSettingsWithExternalRenderingLibrary Settings;
			auto SystemRenderer = SystemIn->CreateSystemRendererWithExternalRenderingLibrary(Settings);
			auto Backend = ICoherentRenderingPlugin::Get().GetBackend_RenderThread();

			auto RendererPtr = FCohtmlRendererHolderSharedPtr(new FCohtmlRendererHolder(SystemRenderer, Backend));
			*WeakRendererOut = RendererPtr;
			*RendererHolder = RendererPtr;
		});
}

FCohtmlRendererHolder::FCohtmlRendererHolder(cohtml::SystemRenderer* renderer, IRenderingBackend* backend)
	: Renderer(renderer)
	, Backend(backend)
{
	backend->OnLiveViewReachedBackend.BindStatic(&FCohtmlSystemHolder::LiveViewReachedBackend);
	backend->OnLiveViewTextureDestroyed.BindStatic(&FCohtmlSystemHolder::UnregisterLiveView);
}

FCohtmlRendererHolder::~FCohtmlRendererHolder()
{
	check(IsInRenderingThread());

	Backend->OnLiveViewReachedBackend.Unbind();
	Backend->OnLiveViewTextureDestroyed.Unbind();
	if (Renderer)
	{
		Renderer->Destroy();
	}

	check(ICoherentRenderingPlugin::IsAvailable());
	ICoherentRenderingPlugin::Get().ReleaseRenderingLibrary();
}

cohtml::SystemRenderer* FCohtmlRendererHolder::GetRenderer() const
{
	return Renderer;
}

IRenderingBackend* FCohtmlRendererHolder::GetBackend() const
{
	return Backend;
}
