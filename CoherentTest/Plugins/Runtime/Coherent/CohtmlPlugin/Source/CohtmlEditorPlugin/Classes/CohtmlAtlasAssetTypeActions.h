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

#include <CoreMinimal.h>
#include <ContentBrowserModule.h>
#include <Toolkits/IToolkitHost.h>
#include <AssetTypeActions_Base.h>

class FCohtmlAtlasAssetTypeActions : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	// Override only what we need
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
#if !defined(COHTML_UE4_423_SUPPORT)
	virtual void GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section) override;
#endif
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::UI; }

	// Forward all calls to the rest of the interface to the underlying UTexture2D actions
	virtual FText GetName() const override { return GetUTexture2DActions()->GetName(); }
	virtual FColor GetTypeColor() const override { return GetUTexture2DActions()->GetTypeColor(); }
	virtual bool CanLocalize() const override { return GetUTexture2DActions()->CanLocalize(); }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override
	{
		GetUTexture2DActions()->OpenAssetEditor(InObjects, EditWithinLevelEditor);
	}
	virtual void PerformAssetDiff(UObject* Asset1, UObject* Asset2, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override
	{
		GetUTexture2DActions()->PerformAssetDiff(Asset1, Asset2, OldRevision, NewRevision);
	}
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override
	{
		return GetUTexture2DActions()->GetAssetDescription(AssetData);
	}
	virtual bool IsImportedAsset() const override { return true; }
	virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override;
	// End IAssetTypeActions Implementation
private:
	inline TSharedPtr<IAssetTypeActions> GetUTexture2DActions() const;
};
