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

#include "CohtmlGamepadProvider.h"
#include "cohtml/Localization/LocalizationManager.h"

namespace cohtml
{
	class System;
}

class FCohtmlSystemWrapper;

// This is used to map live view URLs to specific image handles.
// New URLs are always added simultaneously with an image handle.
// Think of it as TMap<FString, unsigned int>. A struct with TArrays
// is used because we need to easily extract an array pointer and pass it to Cohtml.
struct FCohtmlLiveViews
{
	TArray<FString> URLs;
	TArray<uint32_t> Handles;
	// Holds pairs of URLs / Handles that are yet to reach the backend;
	// Elements in this collection shouldn't be passed to UserImageChanged yet
	TArray<TPair<FString, uint32_t>> UrlHandlesNotInBackend;

	// 0 is used to indicate a preloaded image.
	uint32_t s_NextLiveViewHandle = 1;
};

struct FCohtmlConvertedFallbackFormat
{
	TArray<char> BaseFormat;
	TArray<TArray<char>> FallbackFormats;

	const char** GetAsCharArrays() const
	{
		if (FallbackFormats.Num() == 0)
		{
			return nullptr;
		}

		for (auto& Format : FallbackFormats)
		{
			FallbackFormatPtrs.Add(Format.GetData());
		}
		return FallbackFormatPtrs.GetData();
	}

private:
	// Keeps the char** representation alive until we pass it
	mutable TArray<const char*> FallbackFormatPtrs;
};

class FCohtmlSystemHolder
{
public:
	static TSharedPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> CreateSystem();
	static void DestroySystem(cohtml::System* nakedSystem);

	static bool IsReady();
	static FCohtmlGamepadProvider& GetGamepadProvider();

	static bool IsLiveViewRegistered(const FString& Url);
	static void RegisterLiveView(const FString& Url);
	static void UnregisterLiveView(const FString& Url);
	static void LiveViewReachedBackend(const FString& Url);
	// Causes the system hold to stop tracking the currently active live views
	// Used to prevent warnings from Cohtml which will be caused
	// if you Stop the game in the UE4 editor and run play immediately
	// because the old live views wouldn't be destroyed / unregistered by the backend
	// if you click Stop before the Paint task is executed.
	static void ResetLiveViewTrackingData();
	static unsigned int GetLiveViewHandle(const FString& Url);
	static unsigned int GetNewLiveViewHandle() { return s_LiveViews.s_NextLiveViewHandle; }
	static unsigned int* GetLiveViewHandles();
	static int GetLiveViewsNumber();
private:
	static TWeakPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> s_System;
	static TUniquePtr<cohtml::ILocalizationManager> s_LocalizationManager;
	static TUniquePtr<cohtml::ITextTransformationManager> s_TextTransformationManager;
	static FCohtmlGamepadProvider s_GamepadProvider;
	static FCohtmlLiveViews s_LiveViews;
};
