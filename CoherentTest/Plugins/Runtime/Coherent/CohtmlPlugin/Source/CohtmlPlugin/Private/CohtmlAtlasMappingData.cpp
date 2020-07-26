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
#include "CohtmlAtlasMappingData.h"

#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

UCohtmlAtlasContainedTextures::UCohtmlAtlasContainedTextures(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Textures()
{
}

UCohtmlTextureAtlasDetails::UCohtmlTextureAtlasDetails(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AtlasPath("")
	, Width(0)
	, Height(0)
	, PixelFormat("")
	, MaxAtlasWidth(FTextureAtlasMetaData::GDefaultMaxAtlasSize)
	, MaxAtlasHeight(FTextureAtlasMetaData::GDefaultMaxAtlasSize)
	, MaxTextureWidth(FTextureAtlasMetaData::GDefaultMaxTextureSizeToPack)
	, MaxTextureHeight(FTextureAtlasMetaData::GDefaultMaxTextureSizeToPack)
{
}

const uint32 FTextureAtlasMetaData::GDefaultMaxAtlasSize = 4096u;
const uint32 FTextureAtlasMetaData::GDefaultMaxTextureSizeToPack = 1024u;

void FTextureAtlasMetaData::LoadAtlasMetaData()
{
	AtlasContainedTextures.Empty();
	AtlasDetails.Empty();
	AllAtlasedTextures.Empty();
	Atlases.Empty();

	TArray<uint8> Buffer;
	FString AtlasMappingDataPath = FPaths::ProjectContentDir() / FString("Atlases/AtlasMappingData.cohtmlamd");

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*AtlasMappingDataPath))
	{
		FFileHelper::LoadFileToArray(Buffer, *AtlasMappingDataPath);
	}

	if (Buffer.Num())
	{
		FMemoryReader MemoryReader(Buffer, true);
		FObjectAndNameAsStringProxyArchive AtlasArchive(MemoryReader, true);

		AtlasArchive << AllAtlasedTextures;

		int32 CurrentAtlasIndex = 0;
		while (!AtlasArchive.AtEnd())
		{
			auto TextureAtlasDetails = NewObject<UCohtmlTextureAtlasDetails>(
				GetTransientPackage(),
				FName(*FString::Printf(TEXT("TextureAtlasDetails%d"), CurrentAtlasIndex)),
				RF_Public | RF_Standalone);
			auto AtlasTextureList = NewObject<UCohtmlAtlasContainedTextures>(
				GetTransientPackage(),
				FName(*FString::Printf(TEXT("ContainedTextures%d"), CurrentAtlasIndex)),
				RF_Public | RF_Standalone);
			TextureAtlasDetails->Serialize(AtlasArchive);
			AtlasTextureList->Serialize(AtlasArchive);
			AtlasDetails.Add(TextureAtlasDetails->AtlasPath, TextureAtlasDetails);
			AtlasContainedTextures.Add(TextureAtlasDetails->AtlasPath, AtlasTextureList);

			Atlases.Add(MakeShared<FAtlasInfo>(TextureAtlasDetails->AtlasPath));
			CurrentAtlasIndex++;
		}
	}
}

void FTextureAtlasMetaData::SerializeAtlasMetaData()
{
	TArray<uint8> BinaryBlob;
	FMemoryWriter AtlasMemoryWriter(BinaryBlob, true);
	FObjectAndNameAsStringProxyArchive AtlasArchive(AtlasMemoryWriter, true);

	AtlasArchive << AllAtlasedTextures;

	for (const auto& Pair : AtlasDetails)
	{
		Pair.Value->Serialize(AtlasArchive);
		AtlasContainedTextures[Pair.Key]->Serialize(AtlasArchive);
	}

	if (!FFileHelper::SaveArrayToFile(BinaryBlob, *(FPaths::ProjectContentDir() / FString("Atlases/AtlasMappingData.cohtmlamd"))))
	{
		COHTML_UE_LOG(Error, TEXT("Failed to save atlas metadata!"));
		return;
	}
}

void FTextureAtlasMetaData::AddAtlasedAsset(const FString& AssetName, FTextureAtlasMappingInfo MappingInfo)
{
	AllAtlasedTextures.Add(AssetName, MappingInfo);
}

void FTextureAtlasMetaData::RenameAtlasedAsset(const FString& OldAssetName, const FString& NewAssetName)
{
	FTextureAtlasMappingInfo TextureMappingData = *(AllAtlasedTextures.Find(OldAssetName));
	AllAtlasedTextures.Remove(OldAssetName);
	AllAtlasedTextures.Add(NewAssetName, TextureMappingData);
}

void FTextureAtlasMetaData::RemoveAtlasedAsset(const FString& AssetName)
{
	AllAtlasedTextures.Remove(AssetName);
}

void FTextureAtlasMetaData::RemoveAllAssetsFromAtlas(const FString& AtlasPath)
{
	TArray<FString> AtlasedTexturesNames;
	AllAtlasedTextures.GetKeys(AtlasedTexturesNames);
	for (const auto& TextureName : AtlasedTexturesNames)
	{
		if (AllAtlasedTextures[TextureName].AtlasPath == AtlasPath)
		{
			AllAtlasedTextures.Remove(TextureName);
		}
	}
}

void FTextureAtlasMetaData::AddAtlas(const FString& AtlasPath)
{
	bool bAtlasExists = Atlases.ContainsByPredicate([&AtlasPath](const AtlasInfoPtr& AtlasInfo) {
		return AtlasInfo->AtlasPath == AtlasPath;
	});
	if (!bAtlasExists)
	{
		Atlases.Add(MakeShared<FAtlasInfo>(AtlasPath));
	}
}

void FTextureAtlasMetaData::RenameAtlas(const FString& OldAtlasPath, const FString& NewAtlasPath)
{
	Atlases.RemoveAll([&](const AtlasInfoPtr& Atlas) {
		return Atlas->AtlasPath == OldAtlasPath;
	});
	Atlases.Add(MakeShared<FAtlasInfo>(NewAtlasPath));

	for (auto& TextureMappingPair : AllAtlasedTextures)
	{
		if (TextureMappingPair.Value.AtlasPath == OldAtlasPath)
		{
			TextureMappingPair.Value.AtlasPath = NewAtlasPath;
		}
	}
}

void FTextureAtlasMetaData::RemoveAtlas(const FString& AtlasPath)
{
	Atlases.RemoveAll([&](const AtlasInfoPtr& Atlas) {
		return Atlas->AtlasPath == AtlasPath;
	});

	RemoveAllAssetsFromAtlas(AtlasPath);
}

void FTextureAtlasMetaData::SetAtlasNeedsRebuild(const FString& AtlasPath, bool bNeedsRebuild)
{
	AtlasInfoPtr* Atlas = Atlases.FindByPredicate([&AtlasPath](const AtlasInfoPtr& AtlasInfo) {
		return AtlasInfo->AtlasPath == AtlasPath;
	});

	if (Atlas)
	{
		(*Atlas)->bNeedsRebuild = bNeedsRebuild;
	}
}

const TArray<AtlasInfoPtr>& FTextureAtlasMetaData::GetAtlases() const
{
	return Atlases;
}

const TMap<FString, FTextureAtlasMappingInfo>& FTextureAtlasMetaData::GetAtlasedTextures() const
{
	return AllAtlasedTextures;
}
