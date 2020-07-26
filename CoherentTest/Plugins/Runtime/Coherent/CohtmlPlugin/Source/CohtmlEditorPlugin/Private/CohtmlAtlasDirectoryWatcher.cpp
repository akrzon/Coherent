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
#include "CohtmlAtlasDirectoryWatcher.h"
#include "CohtmlBackwardsCompatibility.h"

#include <Settings/ProjectPackagingSettings.h>
#include <HAL/PlatformFilemanager.h>

#if WITH_EDITOR
FCohtmlAtlasDirectoryWatcher& FCohtmlAtlasDirectoryWatcher::Get()
{
	static FCohtmlAtlasDirectoryWatcher Singleton;
	return Singleton;
}

void FCohtmlAtlasDirectoryWatcher::AtlasesDirectoryDelegate(const TArray<FFileChangeData>& Changes)
{
	FString AtlasesDirectory = FPaths::ConvertRelativePathToFull(CohtmlGetProjectContentDir() / "Atlases");
	for (const auto& Change : Changes)
	{
		if ((Change.Action == FFileChangeData::FCA_Modified && Change.Filename == AtlasesDirectory) ||
			(Change.Action == FFileChangeData::FCA_Removed && Change.Filename.Contains("/Content/Atlases/")))
		{
			AddOrRemoveAtlasesDirFromPackagingSettings(AtlasesDirectory);
		}
	}
}

void FCohtmlAtlasDirectoryWatcher::AddOrRemoveAtlasesDirFromPackagingSettings(const FString& FullAtlasesPath)
{
	auto ProjectPackagingSettings = GetMutableDefault<UProjectPackagingSettings>();
	FDirectoryPath AtlasesPath;
	AtlasesPath.Path = TEXT("/Game/Atlases");
	FDirectoryPath AtlasesDir;
	AtlasesDir.Path = TEXT("Atlases");
	auto FindAtlasesPathLambda = [&AtlasesPath](const FDirectoryPath& Dir) {
		return Dir.Path == AtlasesPath.Path;
	};
	auto FindAtlasesDirLambda = [&AtlasesDir](const FDirectoryPath& Dir) {
		return Dir.Path == AtlasesDir.Path;
	};

	if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*FullAtlasesPath))
	{
		if (!ProjectPackagingSettings->DirectoriesToAlwaysCook.ContainsByPredicate(FindAtlasesPathLambda))
		{
			ProjectPackagingSettings->DirectoriesToAlwaysCook.Add(AtlasesPath);
		}

		if (!ProjectPackagingSettings->DirectoriesToAlwaysStageAsUFS.ContainsByPredicate(FindAtlasesDirLambda))
		{
			ProjectPackagingSettings->DirectoriesToAlwaysStageAsUFS.Add(AtlasesDir);
		}
	}
	else
	{
		ProjectPackagingSettings->DirectoriesToAlwaysCook.RemoveAll(FindAtlasesPathLambda);
		ProjectPackagingSettings->DirectoriesToAlwaysStageAsUFS.RemoveAll(FindAtlasesDirLambda);
	}

	ProjectPackagingSettings->UpdateDefaultConfigFile();
}

void FCohtmlAtlasDirectoryWatcher::Initialize()
{
	auto DirectoryWatcher = FModuleManager::LoadModulePtr<FDirectoryWatcherModule>("DirectoryWatcher");
	verify(DirectoryWatcher);

	auto AtlasDirectoryWatcher = FCohtmlAtlasDirectoryWatcher::Get();

	FString ContentPathOnDisk = CohtmlGetProjectContentDir();
	FString AtlasesDirectory = FPaths::ConvertRelativePathToFull(ContentPathOnDisk / "Atlases");
	AtlasDirectoryWatcher.AddOrRemoveAtlasesDirFromPackagingSettings(AtlasesDirectory);

	DirectoryWatcher->Get()->RegisterDirectoryChangedCallback_Handle(
		ContentPathOnDisk,
		IDirectoryWatcher::FDirectoryChanged::CreateRaw(&AtlasDirectoryWatcher, &FCohtmlAtlasDirectoryWatcher::AtlasesDirectoryDelegate),
		AtlasDirectoryWatcher.AtlasesDirectoryDelegateHandle);
}

void FCohtmlAtlasDirectoryWatcher::Uninitialize()
{
	auto DirectoryWatcher = FModuleManager::LoadModulePtr<FDirectoryWatcherModule>("DirectoryWatcher");
	verify(DirectoryWatcher);

	auto AtlasDirectoryWatcher = FCohtmlAtlasDirectoryWatcher::Get();
	DirectoryWatcher->Get()->UnregisterDirectoryChangedCallback_Handle(CohtmlGetProjectContentDir(), AtlasDirectoryWatcher.AtlasesDirectoryDelegateHandle);
}
#endif