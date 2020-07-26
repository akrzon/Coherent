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
#include "CohtmlEditorPluginPrivatePCH.h"
#include "CohtmlEditorPaths.h"

#include "CohtmlSettings.h"

#include "HAL/PlatformFilemanager.h"
#include "HAL/PlatformFile.h"

FCohtmlEditorPaths::FCohtmlEditorPaths()
{
	Initialize();
}

FCohtmlEditorPaths& FCohtmlEditorPaths::Get()
{
	static FCohtmlEditorPaths CoherentPaths;
	return CoherentPaths;
}

void FCohtmlEditorPaths::Initialize()
{
	PluginResourcesDir = FPaths::Combine(*FPaths::EnginePluginsDir(),
		TEXT("Runtime"),
		TEXT("Coherent"),
		TEXT("CohtmlPlugin"),
		TEXT("Resources"));

	auto bIsEnginePlugin = FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*PluginResourcesDir);
	if (!bIsEnginePlugin)
	{
#if defined(COHTML_UE4_417_SUPPORT)
		PluginResourcesDir = FPaths::Combine(*FPaths::GamePluginsDir(),
#else
		PluginResourcesDir = FPaths::Combine(*FPaths::ProjectPluginsDir(),
#endif
		TEXT("Runtime"),
		TEXT("Coherent"),
		TEXT("CohtmlPlugin"),
		TEXT("Resources"));
	}
	auto bIsInstallationValid = FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*PluginResourcesDir);
	if (!bIsInstallationValid)
	{
		COHTML_EDITOR_UE_LOG(Error, TEXT("Editor resources are missing! Some features might now work. Please reinstall the plugin."));
	}

	GameContentDir = CohtmlGetProjectContentDir();
	GameUIResourcesDir = FPaths::Combine(*GameContentDir,
		TEXT("uiresources"));

	GameJSDir = FPaths::Combine(*GameUIResourcesDir, TEXT("javascript"));

	DefaultHTMLPagePath = FPaths::Combine(*PluginResourcesDir,
		TEXT("uiresources"),
		TEXT("cohtml_plane.html"));

	CoherentJSPath = FPaths::Combine(*PluginResourcesDir,
		TEXT("uiresources"),
		TEXT("javascript"),
		TEXT("cohtml.js"));

	HUDHTMLPagePath = FPaths::Combine(*PluginResourcesDir,
		TEXT("uiresources"),
		TEXT("cohtml_hud.html"));


	DefaultLogoPath = FPaths::Combine(*PluginResourcesDir,
		TEXT("uiresources"),
		TEXT("coherent_logo_white.png"));
#if COHTML_IS_GAMEFACE
	DocsURL = FString("http://coherent-labs.com/Documentation/UnrealEngine4-Prysm/");
	ChangelogURL = FString("http://coherent-labs.com/changelog-gameface/");
#else
	DocsURL = FString("http://coherent-labs.com/Documentation/UnrealEngine4-Prysm/");
	ChangelogURL = FString("http://coherent-labs.com/changelog-prysm/");
#endif

	DevPortalURL = FString("https://developers.coherent-labs.com/");

	CoherentCohtmlJS = FString("cohtml.js");
	DefaultPageName = FString("coherent_view_");
	HUDHTMLPageName = FString("cohtml_hud.html");
	PlaneHTMLPageName = FString("cohtml_plane.html");
	DefaultLogoName = FString("Logo/coherent_logo_white.png");

	DefaultFontsDir = FPaths::Combine(*PluginResourcesDir, TEXT("Fonts"));
	GameDefaultFontsDir = FPaths::Combine(*GameContentDir, TEXT("Fonts"));
}

FString FCohtmlEditorPaths::GetBrowserURL(const FString& Path) const
{
	return FString("file://") +
		FPaths::ConvertRelativePathToFull(Path);
}
