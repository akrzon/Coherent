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
#include "Runtime/Slate/Public/Framework/MultiBox/MultiBoxExtender.h"
#include "CohtmlAtlasMappingData.h"
#include "CohtmlAtlasBuilder.h"

template <typename ItemType> class SListView;

class FCohtmlAtlasManagerCallbacks
{
public:
	static void RegisterCallbacks();
	static void UnregisterCallbacks();

	static const FSlateBrush* OnGetAtlasPreviewImageBrush();
	static TSharedRef<class ITableRow> OnGenerateRowForAtlasViewer(AtlasInfoPtr AtlasInfo, const TSharedRef<class STableViewBase>& OwnerTable);
	static TSharedRef<FExtender> OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths);
	static void OnCreateAtlasListContextSubmenu(FMenuBuilder& MenuBuilder, TArray<FString> SelectedPaths, bool AreFolders);
	static void OnCreateAtlasAssetContextMenu(FMenuBuilder& MenuBuilder, TArray<FString> SelectedPaths);

	static void OnAssetSaved(const FString& PackageFileName, UObject* Outer);
	static void OnAssetRemoved(const struct FAssetData& AssetData);
	static void OnAssetRenamed(const FAssetData& RenamedAssetData, const FString& OldObjectPath);

	static void OnAddAtlasButtonClicked();
	static void OnAddAssetsToAtlas(FString AtlasPath, TArray<FAssetData> AssetsToAtlas);
	static void OnAddAssetsToNewAtlas(TArray<FAssetData> AssetsToAtlas);

	// These both call FCohtmlAtlasManager::RebuildStaleAtlases but
	// we can't reuse a single function due to different delegate signatures
	static void OnLaunchCompleted(bool, double, int32);
	static void OnLaunchCanceled(double);

	static FDelegateHandle ContentBrowserPathExtenderDelegateHandle;
	static FDelegateHandle OnAssetRemovedDelegateHandle;
	static FDelegateHandle OnAssetRenamedDelegateHandle;
	static FDelegateHandle OnAssetSavedDelegateHandle;
	static FDelegateHandle OnLaunchCompletedDelegateHandle;
	static FDelegateHandle OnLaunchCanceledDelegateHandle;
};

class COHTMLEDITORPLUGIN_API FCohtmlAtlasManager
{
public:
	static FCohtmlAtlasManager& Get();

	bool CreateAtlas();
	bool BatchTexturesInNewAtlas(const TSet<UTexture2D*>& Textures);
	bool BatchTexturesInAtlas(FString AtlasPath, const TSet<UTexture2D*>& Textures);
	bool RebuildAtlas(const FString& AtlasToRebuild);

	void RenameAtlas(const FString& OldAtlasPath, const FString& NewAtlasPath);
	void RenameAtlasedAsset(const FString& OldAssetName, const FString& NewAssetName);
	void RemoveAtlas(const FString& AtlasPath);
	void RemoveAtlasedAsset(const FString& AssetName, const FString& AtlasPath);

	bool GetHandleOnAssetSaved();
	bool GetHandleOnAssetRemoved();
	void SetHandleOnAssetSaved(bool ShouldHandleAssetRemoved);
	void SetHandleOnAssetRemoved(bool ShouldHandleAssetRemoved);
	void SetAutoConfirmMessageBoxes(bool ShouldAutoConfirmMessageBoxes);

	void LaunchAtlasViewer();
	void LaunchAtlasPreview(const FString& AtlasPath);
	void RefreshAtlasViewerWidget();
	void CloseAtlasPreviewWindow(const FString& AtlasPath);

	const TArray<AtlasInfoPtr>& GetAtlases();
	void ReloadAtlasMetaData();
	const FTextureAtlasMetaData& GetAtlasMetaData();

private:
	FCohtmlAtlasManager();

	friend FCohtmlAtlasManagerCallbacks;

	TUniquePtr<FCohtmlAtlasBuilder> AtlasBuilder;

	FString GetAssetAtlasPath(const FString& AssetName);

	bool IsLaunchingFromEditor() const;
	void ScheduleAtlasForRebuild(const FString& AtlasPath);
	void RebuildStaleAtlases();
	const float AtlasRebuildIntervalSeconds;

	TSharedRef<ITableRow> GenerateRow(AtlasInfoPtr AtlasInfo, const TSharedRef<STableViewBase>& OwnerTable);
	const FSlateBrush* GetPreviewImage() const;

	TWeakPtr<SWindow> AtlasViewerWindow;
	TWeakPtr<SListView<AtlasInfoPtr>> AtlasTableWidget;
	TWeakPtr<SWindow> AtlasPreviewWindow;
#if defined(COHTML_UE4_419_SUPPORT)
	TSharedPtr<struct FSlateBrush> PreviewImageBrush;
#else
	TSharedPtr<class FDeferredCleanupSlateBrush> PreviewImageBrush;
#endif
	bool bIsCurrentlyUpdatingProperty;

	bool bShouldHandleOnAssetSaved;
	bool bShouldHandleOnAssetRemoved;

	FTextureAtlasMetaData AtlasMetaData;
};