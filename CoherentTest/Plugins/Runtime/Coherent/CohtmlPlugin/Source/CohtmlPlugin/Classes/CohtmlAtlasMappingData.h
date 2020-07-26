
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

#include "CohtmlAtlasMappingData.generated.h"

USTRUCT()
struct FTextureAtlasMappingInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString AtlasPath;

	UPROPERTY()
	int32 Width;

	UPROPERTY()
	int32 Height;

	UPROPERTY()
	int32 OriginX;

	UPROPERTY()
	int32 OriginY;

	friend FArchive& operator<<(FArchive& Ar, FTextureAtlasMappingInfo& Data)
	{
		Ar << Data.AtlasPath;
		Ar << Data.Width;
		Ar << Data.Height;
		Ar << Data.OriginX;
		Ar << Data.OriginY;
		return Ar;
	}

	bool operator==(const FTextureAtlasMappingInfo& Right) const
	{
		return AtlasPath == Right.AtlasPath &&
			Width == Right.Width &&
			Height == Right.Height &&
			OriginX == Right.OriginX &&
			OriginY == Right.OriginY;
	}
};

UCLASS(meta=(DisplayName = "Prysm Atlas Contained Textures"))
class COHTMLPLUGIN_API UCohtmlAtlasContainedTextures : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = "Textures")
	TSet<UTexture2D*> Textures;
};

UCLASS(meta=(DisplayName = "Prysm Texture Atlas Details"))
class COHTMLPLUGIN_API UCohtmlTextureAtlasDetails : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, Category = "AtlasInfo")
	FString AtlasPath;

	UPROPERTY(VisibleAnywhere, Category = "AtlasInfo")
	int32 Width;

	UPROPERTY(VisibleAnywhere, Category = "AtlasInfo")
	int32 Height;

	UPROPERTY(VisibleAnywhere, Category = "AtlasInfo")
	FString PixelFormat;

	UPROPERTY(EditAnywhere, Category = "AtlasThresholds", Meta = (ToolTip = "The maximum allowed width of the texture atlas" , ClampMin = 0, UIMin = 0, UIMax = 4096))
	int32 MaxAtlasWidth;

	UPROPERTY(EditAnywhere, Category = "AtlasThresholds", Meta = (ToolTip = "The maximum allowed height of the texture atlas", ClampMin = 0, UIMin = 0, UIMax = 4096))
	int32 MaxAtlasHeight;

	UPROPERTY(EditAnywhere, Category = "AtlasThresholds", Meta = (ToolTip = "The maximum allowed width for a texture contained in the atlas", ClampMin = 0, UIMin = 0, UIMax = 4096))
	int32 MaxTextureWidth;

	UPROPERTY(EditAnywhere, Category = "AtlasThresholds", Meta = (ToolTip = "The maximum allowed height for a texture contained in the atlas", ClampMin = 0, UIMin = 0, UIMax = 4096))
	int32 MaxTextureHeight;
};

struct FAtlasInfo
{
	FString AtlasPath;
	bool bNeedsRebuild;
	FTimerHandle RebuildTimerHandle;

	FAtlasInfo() : AtlasPath("")
		, bNeedsRebuild(false)
	{
	}

	FAtlasInfo(const FString& Path) : AtlasPath(Path)
		, bNeedsRebuild(false)
	{
	}
};

typedef TSharedPtr<FAtlasInfo> AtlasInfoPtr;

USTRUCT()
struct COHTMLPLUGIN_API FTextureAtlasMetaData
{
	static const uint32 GDefaultMaxAtlasSize;
	static const uint32 GDefaultMaxTextureSizeToPack;

	GENERATED_USTRUCT_BODY()

	// A UCohtmlAtlasContainedTextures object is passed to PropertyEditor::CreateDetailsView
	// to create a widget containing the textures contained in a given atlas.
	UPROPERTY()
	TMap<FString, UCohtmlAtlasContainedTextures*> AtlasContainedTextures;

	// A UCohtmlTextureAtlasDetails object is passed to PropertyEditor::CreateDetailsView
	// to create a widget containing the atlas information (size, pixel format, size thresholds).
	UPROPERTY()
	TMap<FString, UCohtmlTextureAtlasDetails*> AtlasDetails;

	void LoadAtlasMetaData();
	void SerializeAtlasMetaData();

	void AddAtlasedAsset(const FString& AssetName, FTextureAtlasMappingInfo MappingInfo);
	void RenameAtlasedAsset(const FString& OldAssetName, const FString& NewAssetName);
	void RemoveAtlasedAsset(const FString& AssetName);
	void RemoveAllAssetsFromAtlas(const FString& AtlasPath);

	void AddAtlas(const FString& AtlasPath);
	void RenameAtlas(const FString& OldAtlasPath, const FString& NewAtlasPath);
	void RemoveAtlas(const FString& AtlasPath);

	void SetAtlasNeedsRebuild(const FString& AtlasPath, bool bNeedsRebuild);

	const TArray<AtlasInfoPtr>& GetAtlases() const;
	const TMap<FString, FTextureAtlasMappingInfo>& GetAtlasedTextures() const;

private:
	// Used when listing all the generated atlases in the atlas viewer window.
	// They need to be kept alive in a collection so that we can prevent GC,
	// update them when necessary and refresh the Slate widget displaying them.
	TArray<AtlasInfoPtr> Atlases;

	// Used by the FileHandler to detect whether a preloaded image is contained
	// in an atlas and should be loaded from there.
	TMap<FString, FTextureAtlasMappingInfo> AllAtlasedTextures;

};
