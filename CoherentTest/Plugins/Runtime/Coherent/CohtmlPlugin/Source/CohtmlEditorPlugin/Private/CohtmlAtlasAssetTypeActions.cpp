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
#include "CohtmlAtlasAssetTypeActions.h"
#include "CohtmlEditorCommands.h"
#include "CohtmlAtlasManager.h"

#include <AssetRegistryModule.h>
#include <EditorStyleSet.h>
#include <Framework/MultiBox/MultiBoxBuilder.h>
#include <Engine/Texture2D.h>
#include <EditorFramework/AssetImportData.h>

#define LOCTEXT_NAMESPACE "AssetTypeActions"

TSharedPtr<IAssetTypeActions> FCohtmlAtlasAssetTypeActions::GetUTexture2DActions() const
{
	// The editor works in mysterious ways and even though the AssetTools module supports multiple actions for the same class,
	// the editor doesn't. Adding our asset type actions means we are effectively destroying the standard UTexture2D actions
	// so try to load them manually
	IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
	auto AssetActions = AssetTools.GetAssetTypeActionsListForClass(UTexture2D::StaticClass());
	for (auto& Actions : AssetActions)
	{
		auto ActionsPtr = Actions.Pin();
		if (ActionsPtr.IsValid() && ActionsPtr.Get() != this && ActionsPtr->GetSupportedClass() == UTexture2D::StaticClass())
		{
			return ActionsPtr;
		}
	}
	check(false && "No Asset type actions for UTexture2D asset! This can only be caused by " COHTML_PRODUCT " being loaded before any module with such actions.");
	return nullptr;
}

void FCohtmlAtlasAssetTypeActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	GetUTexture2DActions()->GetActions(InObjects, MenuBuilder);
	TArray<FString> TextureAssets;
	for (auto Object : InObjects)
	{
		FString AtlasPath = Object->GetPathName();
		if (AtlasPath.Contains("/Game/Atlases"))
		{
			continue;
		}
		TextureAssets.Add(Object->GetPathName());
	}

	if (TextureAssets.Num() == 0)
	{
		return;
	}

	MenuBuilder.AddSubMenu(
		LOCTEXT("CohtmlUTexture2D_AddToAtlas", "Add to Atlas"),
		LOCTEXT("CohtmlTexture2D_AddToAtlasTooltip", "Adds this asset to a texture atlas used by " COHTML_PRODUCT),
		FNewMenuDelegate::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnCreateAtlasListContextSubmenu, TextureAssets, /*AreFolders=*/false)
	);
}

#if !defined(COHTML_UE4_423_SUPPORT)
void FCohtmlAtlasAssetTypeActions::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	GetUTexture2DActions()->GetActions(InObjects, Section);
}
#endif

void FCohtmlAtlasAssetTypeActions::GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const
{
	for (auto& Asset : TypeAssets)
	{
		const auto TextureAsset = CastChecked<UTexture>(Asset);
		if (TextureAsset && TextureAsset->AssetImportData)
		{
			TextureAsset->AssetImportData->ExtractFilenames(OutSourceFilePaths);
		}
	}
}

UClass* FCohtmlAtlasAssetTypeActions::GetSupportedClass() const { return UTexture2D::StaticClass(); };


#undef LOCTEXT_NAMESPACE