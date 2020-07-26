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
#include "CohtmlEditorDirectoryWatcher.h"

#include "CohtmlDirectoryWatcher.h"
#include <cohtml/View.h>
#include "CohtmlBaseComponent.h"
#include "CohtmlSettings.h"
#include "CohtmlSystem.h"
#include "CohtmlSystemWrapper.h"

#if WITH_EDITOR
FCohtmlEditorDirectoryWatcher::FCohtmlEditorDirectoryWatcher()
{
	auto DirectoryWatcher = FModuleManager::LoadModulePtr<FDirectoryWatcherModule>("DirectoryWatcher");
	verify(DirectoryWatcher);

	const FString DirectoryToWatch = CohtmlGetProjectContentDir() / "uiresources";
	DirectoryWatcher->Get()->RegisterDirectoryChangedCallback_Handle(
		DirectoryToWatch,
		IDirectoryWatcher::FDirectoryChanged::CreateRaw(this, &FCohtmlEditorDirectoryWatcher::WatchDirectoryDelegate),
		WatcherDirectoryHandle);
}

namespace
{
// Converts the url to an absolute path on disk if the protocol is coui / file
// Otherwise, returns empty string
FString URLToAbsolutePath(const FString& URL)
{
	if (URL.StartsWith("http"))
	{
		return "";
	}
	const int ProtocolLength = 4; // file or http or coui
	FString Filepath = URL;
	int32 QueryParamsIndex = -1;
	if (Filepath.FindChar(TEXT('?'), QueryParamsIndex))
	{
		Filepath.RemoveAt(QueryParamsIndex, Filepath.Len() - QueryParamsIndex);
	}
	if (!Filepath.RemoveFromStart("file:///"))
	{
		Filepath.RemoveFromStart("coui://");
		FString CouiRoot = CohtmlGetProjectContentDir();
		CouiRoot = FPaths::ConvertRelativePathToFull(CouiRoot);
		Filepath = FPaths::Combine(*CouiRoot, *Filepath);
	}
	FPaths::NormalizeFilename(Filepath);
	FPaths::RemoveDuplicateSlashes(Filepath);
	return Filepath;
}

}

void FCohtmlEditorDirectoryWatcher::OnAssetLoadedByView(const FString& AssetPath)
{
	auto AbsoluteFilepath = URLToAbsolutePath(AssetPath);
	if (!AbsoluteFilepath.IsEmpty())
	{
		FScopeLock Lock(&CriticalSection);
		ViewDependencies.Add(AbsoluteFilepath);
	}
}

bool FCohtmlEditorDirectoryWatcher::IsViewDependency(const FString& AssetPath)
{
	FScopeLock Lock(&CriticalSection);
	return ViewDependencies.Contains(AssetPath);
}

void FCohtmlEditorDirectoryWatcher::OnViewCreated(cohtml::View* View, cohtml::System* System)
{
	Views.Add(View);
	SystemPtr = System;
}

void FCohtmlEditorDirectoryWatcher::OnViewDestroyed(cohtml::View* View)
{
	Views.Remove(View);
}

void FCohtmlEditorDirectoryWatcher::WatchDirectoryDelegate(const TArray<FFileChangeData>& Changes)
{
	auto Settings = GetDefault<UCohtmlSettings>();
	if (!Settings->EnableLiveReload || !Views.Num())
	{
		return;
	}
	check(SystemPtr);

	FString CouiRoot = CohtmlGetProjectContentDir();
	CouiRoot = FPaths::ConvertRelativePathToFull(CouiRoot);

	for (auto It = Changes.CreateConstIterator(); It; ++It)
	{
		auto Filename = It->Filename;
		if (Filename.StartsWith(".."))
		{
			// FPaths::ConvertRelativePathToFull used with paths that are starting with ".."
			// will result in a full path starting from the engine's root, which is wrong
			// in our case. That is why we are manually setting the root by combining the
			// CouiRoot with the file path.
			Filename = FPaths::Combine(*CouiRoot, *Filename);
		}
		Filename = FPaths::ConvertRelativePathToFull(Filename);
		FPaths::NormalizeFilename(Filename);
		FPaths::RemoveDuplicateSlashes(Filename);
		if ((It->Action == FFileChangeData::FCA_Modified || It->Action == FFileChangeData::FCA_Removed) && IsViewDependency(Filename))
		{
			COHTML_EDITOR_UE_LOG(Log, TEXT("Reloading all Views because file \"%s\" was changed or removed"), *Filename);

			SystemPtr->ClearCachedUnusedImages();
			for (auto View : Views)
			{
				View->Reload();
			}
			break;
		}
	}
}

FCohtmlEditorDirectoryWatcher& FCohtmlEditorDirectoryWatcher::Get()
{
	static FCohtmlEditorDirectoryWatcher Singleton;
	return Singleton;
}

void FCohtmlEditorDirectoryWatcher::Initialize()
{
	auto& EditorWatcher = FCohtmlEditorDirectoryWatcher::Get();
	auto& GameWatcher = FCohtmlDirectoryWatcher::Get();
	GameWatcher.OnAssetLoadedByView.BindRaw(&EditorWatcher, &FCohtmlEditorDirectoryWatcher::OnAssetLoadedByView);
	GameWatcher.OnViewDestroyed.BindRaw(&EditorWatcher, &FCohtmlEditorDirectoryWatcher::OnViewDestroyed);
	GameWatcher.OnViewCreated.BindRaw(&EditorWatcher, &FCohtmlEditorDirectoryWatcher::OnViewCreated);
}

void FCohtmlEditorDirectoryWatcher::Uninitialize()
{
	auto& GameWatcher = FCohtmlDirectoryWatcher::Get();
	GameWatcher.OnAssetLoadedByView.Unbind();
	GameWatcher.OnViewDestroyed.Unbind();
	GameWatcher.OnViewCreated.Unbind();
}


#endif