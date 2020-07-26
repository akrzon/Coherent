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
#include "CohtmlAtlasBuilder.h"
#include "CohtmlEditorShaders.h"
#define STB_RECT_PACK_IMPLEMENTATION 1
#include "StbRectPack.h"

#include <Editor.h>
#include <AssetRegistryModule.h>
#include <Engine/TextureRenderTarget2D.h>
#include <FileHelpers.h>
#include <IAssetRegistry.h>
#include <Interfaces/IMainFrameModule.h>
#include <Misc/FileHelper.h>
#include <Misc/MessageDialog.h>
#include <PipelineStateCache.h>


#define LOCTEXT_NAMESPACE "CohtmlAtlasBuilder"

namespace
{
const auto GAtlasPaddingWidth = 4;
const auto GAtlasPaddingHeight = 1;

const FString DefaultAtlasBaseName = TEXT("UI_Atlas");
const FString DefaultAtlasPackageName = TEXT("/Game/Atlases/UI_Atlas");
}

FORCEINLINE unsigned AlignSizeToMultipleOf4(unsigned Size)
{
	return ((Size & 3) == 0) ? Size + GAtlasPaddingWidth : (Size + 3) & ~3;
}

TArray<FString> FCohtmlAtlasBuilder::PackageTexturesInAtlas(const FString& InAtlasPath,
	const TSet<UTexture2D*>& TexturesToPack, FTextureAtlasMetaData& OutMetaData, bool bAddToExistingAtlas,
	const FTextureSizeThresholds& SizeThresholds)
{
	using namespace Coherent;

	FString AtlasPath = InAtlasPath;
	FString AtlasName;
	AtlasPath.Split(".", nullptr, &AtlasName);
	TArray<FString> AtlasNames;

	int32 MaxAtlasSize = FMath::Max<int32>(SizeThresholds.MaxAtlasWidth, SizeThresholds.MaxAtlasHeight);
	TArray<stbrp_node> PackNodes;
	PackNodes.SetNum(MaxAtlasSize);
	stbrp_context PackContext;
	TArray<stbrp_rect> Rects;

	// Use a temporary array as it has TArray::StableSort whereas TSet::Sort leads to non-deterministic
	// order of the packed textures
	TArray<UTexture2D*> TexturesLeftToPack = TexturesToPack.Array();
	if (bAddToExistingAtlas)
	{
		TexturesLeftToPack.Append(OutMetaData.AtlasContainedTextures[AtlasPath]->Textures.Array());
	}
	TexturesLeftToPack.StableSort([](const UTexture2D& First, const UTexture2D& Second) {
		bool bIsWidthEqual = First.GetSizeX() == Second.GetSizeX();
		bool bIsHeightEqual = First.GetSizeY() == Second.GetSizeY();

		if (!bIsHeightEqual)
		{
			return First.GetSizeY() >= Second.GetSizeY();
		}
		else if (!bIsWidthEqual)
		{
			return First.GetSizeX() >= Second.GetSizeX();
		}

		return First.GetPathName().Compare(Second.GetPathName()) < 0;;
	});

	FString CurrentAtlasName = AtlasName;
	FString CurrentAtlasPath = AtlasPath;
	while (TexturesLeftToPack.Num() > 0)
	{
		bool bIsExistingAtlas = OutMetaData.AtlasDetails.Contains(CurrentAtlasPath);
		if (!bIsExistingAtlas)
		{
			OutMetaData.AtlasContainedTextures.Add(CurrentAtlasPath, NewObject<UCohtmlAtlasContainedTextures>(
				GetTransientPackage(),
				NAME_None,
				RF_Public | RF_Standalone));
		}

		PrepareTexturesForPacking(TexturesLeftToPack, Rects, SizeThresholds);

		stbrp_init_target(&PackContext,
			SizeThresholds.MaxAtlasWidth - GAtlasPaddingWidth,
			SizeThresholds.MaxAtlasHeight - GAtlasPaddingHeight,
			PackNodes.GetData(),
			MaxAtlasSize);
		stbrp_pack_rects(&PackContext, Rects.GetData(), Rects.Num());

		PopulateDataWithPackedTextures(CurrentAtlasPath, TexturesLeftToPack, OutMetaData, Rects, AtlasNames,
			SizeThresholds, bIsExistingAtlas);

		CurrentAtlasName = FString::Printf(TEXT("%s_%d"), *AtlasName, GetFirstAvailableIndex(AtlasName, OutMetaData.GetAtlases()));
		CurrentAtlasPath = FString("/Game/Atlases") / CurrentAtlasName + TEXT(".") + CurrentAtlasName;
	}

	return AtlasNames;
}

void InitializeAtlasGraphicsState(int32 MaxAtlasWidth, int32 MaxAtlasHeight)
{
	typedef TStaticDepthStencilState<false, CF_Always> TStaticDepthStencilStateForUseWithinRenderCommand;
	// Setup graphics state
	ENQUEUE_COHTML_RENDERING_COMMAND_TWOPARAMETER(
		SetupAtlasBuilderState,
		int32, MaxWidth, MaxAtlasWidth,
		int32, MaxHeight, MaxAtlasHeight,
		{
			FGraphicsPipelineStateInitializer GraphicsPSOInit;

			GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
			GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
			GraphicsPSOInit.DepthStencilState = TStaticDepthStencilStateForUseWithinRenderCommand::GetRHI();

			auto GlobalMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel));
			TShaderMapRef<FAtlasBuildingVS> VertexShader(GlobalMap);
			TShaderMapRef<FAtlasBuildingPS> PixelShader(GlobalMap);

			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);
			GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
			GraphicsPSOInit.RenderTargetsEnabled = 1;
			GraphicsPSOInit.RenderTargetFormats[0] = PF_B8G8R8A8;
			GraphicsPSOInit.RenderTargetFlags[0] = TexCreate_RenderTargetable | TexCreate_ShaderResource;
			GraphicsPSOInit.NumSamples = 1;

			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);
			RHICmdList.SetViewport(0, 0, 0, MaxWidth, MaxHeight, 1);
			RHICmdList.SetScissorRect(false, 0, 0, MaxWidth, MaxHeight);
		});
}

void BeginAtlasRenderPass(UTextureRenderTarget2D* Atlas)
{
	// Set & Clear RT
#if !defined(COHTML_UE4_421_SUPPORT)
#define CohSetAndClearAtlasRT(AtlasRT)\
	FRHIRenderPassInfo Info(AtlasRT->Resource->TextureRHI.GetReference(),\
		ERenderTargetActions::Clear_Store);\
	RHICmdList.BeginRenderPass(Info, TEXT("CoHTML Atlas Builder"))
#else
#define CohSetAndClearAtlasRT(AtlasRT)\
	FRHIRenderTargetView ColorView(AtlasRT->Resource->TextureRHI.GetReference(), ERenderTargetLoadAction::EClear);\
	FRHISetRenderTargetsInfo RTInfo(1, &ColorView, FRHIDepthRenderTargetView());\
	RHICmdList.SetRenderTargetsAndClear(RTInfo)
#endif

	ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(
		BeginCohAtlasRenderPass,
		UTextureRenderTarget2D*, AtlasTexture, Atlas,
		{
			CohSetAndClearAtlasRT(AtlasTexture);
		});

#undef CohSetAndClearAtlasRT
}

void DrawTextureInAtlas(UTextureRenderTarget2D* Atlas, UTexture2D* Texture,
	const FTextureAtlasMappingInfo* TextureMappingInfo, const FTextureSizeThresholds& SizeThresholds)
{
#if !defined(COHTML_UE4_421_SUPPORT)
#define CohDrawPrimitive(BaseVertexIndex, NumPrimitives, NumInstances)\
	RHICmdList.DrawPrimitive(BaseVertexIndex, NumPrimitives, NumInstances)
#else
#define CohDrawPrimitive(BaseVertexIndex, NumPrimitives, NumInstances)\
	RHICmdList.DrawPrimitive(PT_TriangleStrip, BaseVertexIndex, NumPrimitives, NumInstances)
#endif

	ENQUEUE_COHTML_RENDERING_COMMAND_FOURPARAMETER(
		DrawTextureInAtlas,
		UTextureRenderTarget2D*, DestTexture, Atlas,
		UTexture2D*, SrcTexture, Texture,
		const FTextureAtlasMappingInfo*, MappingInfo, TextureMappingInfo,
		const FTextureSizeThresholds&, Thresholds, SizeThresholds,
		{
			auto DestRHI = static_cast<FTextureRenderTarget2DResource*>(DestTexture->Resource)->GetTextureRHI();
			auto SrcRHI = static_cast<FTexture2DResource*>(SrcTexture->Resource)->GetTexture2DRHI();

			auto GlobalMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel));

			TShaderMapRef<FAtlasBuildingPS> PixelShader(GlobalMap);
			PixelShader->SetSourceTexture(RHICmdList, SrcTexture->Resource->TextureRHI);
			PixelShader->SetDoGammaCorrection(RHICmdList, static_cast<float>(SrcTexture->SRGB));

			// Setup the vertices
			FVector4 ClipSpacePositions(MappingInfo->OriginX, MappingInfo->OriginY,
				MappingInfo->OriginX + MappingInfo->Width, MappingInfo->OriginY + MappingInfo->Height);
			ClipSpacePositions[0] *= 2.0f / Thresholds.MaxAtlasWidth;        // Scale X to [0,2]
			ClipSpacePositions[2] *= 2.0f / Thresholds.MaxAtlasWidth;        // Scale X to [0,2]
			ClipSpacePositions[1] *= 2.0f / Thresholds.MaxAtlasHeight;        // Scale Y to [0,2]
			ClipSpacePositions[3] *= 2.0f / Thresholds.MaxAtlasHeight;        // Scale Y to [0,2]
			ClipSpacePositions.Y = 2.0f - ClipSpacePositions.Y; // Flip Y
			ClipSpacePositions.W = 2.0f - ClipSpacePositions.W; // Flip W
			ClipSpacePositions -= FVector4(1, 1, 1, 1);         // Offset to [-1,1]

			FVector4 Vertices[4];
			Vertices[0].Set(ClipSpacePositions.X, ClipSpacePositions.Y, 0, 0);
			Vertices[1].Set(ClipSpacePositions.Z, ClipSpacePositions.Y, 1, 0);
			Vertices[2].Set(ClipSpacePositions.X, ClipSpacePositions.W, 0, 1);
			Vertices[3].Set(ClipSpacePositions.Z, ClipSpacePositions.W, 1, 1);

			// Draw the quad
			const uint32 NumPrimitives = 2;
			const uint32 VertexDataStride = sizeof(Vertices[0]);
			const uint32 VertexCount = GetVertexCountForPrimitiveCount(NumPrimitives, PT_TriangleStrip);

			FRHIResourceCreateInfo CreateInfo;
			FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(VertexDataStride * VertexCount, BUF_Volatile, CreateInfo);
			void* VoidPtr = RHILockVertexBuffer(VertexBufferRHI, 0, VertexDataStride * VertexCount, RLM_WriteOnly);
			FPlatformMemory::Memcpy(VoidPtr, Vertices, VertexDataStride * VertexCount);
			RHIUnlockVertexBuffer(VertexBufferRHI);

			RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);
			CohDrawPrimitive(0, NumPrimitives, 1);

			VertexBufferRHI.SafeRelease();
		});

#undef CohDrawPrimitive
}

void EndAtlasRenderPass()
{
#if !defined(COHTML_UE4_421_SUPPORT)
#define CohEndAtlasRenderPass()\
	RHICmdList.EndRenderPass()
#else
#define CohEndAtlasRenderPass()
#endif

	ENQUEUE_COHTML_RENDERING_COMMAND(EndCohAtlasRenderPass,
		{
			CohEndAtlasRenderPass();
		});

#undef CohEndAtlasRenderPass
}

bool FCohtmlAtlasBuilder::RebuildAtlas(const FString& AtlasPath, FTextureAtlasMetaData& OutMetaData)
{
	auto& TexturesToRepack = OutMetaData.AtlasContainedTextures[AtlasPath]->Textures;
	for (auto TextureIt = TexturesToRepack.CreateIterator(); TextureIt; ++TextureIt)
	{
		if (!(*TextureIt))
		{
			TextureIt.RemoveCurrent();
		}
	}
	UCohtmlTextureAtlasDetails* AtlasDetails = OutMetaData.AtlasDetails[AtlasPath];
	FTextureSizeThresholds SizeThresholds(AtlasDetails->MaxAtlasWidth, AtlasDetails->MaxAtlasHeight,
		AtlasDetails->MaxTextureWidth, AtlasDetails->MaxTextureHeight);
	FTextureAtlasMetaData MetaDataCopy = OutMetaData;

	TArray<FString> AtlasNames;
	if (TexturesToRepack.Num() == 0 ||
		TexturesToRepack.Num() == 1 && TexturesToRepack.Contains(nullptr))
	{
		AtlasNames = CreateNewEmptyAtlasEntry(AtlasPath, OutMetaData, SizeThresholds);
	}
	else
	{
		AtlasNames = PackageTexturesInAtlas(AtlasPath, TexturesToRepack, OutMetaData, /*bAddToExistingAtlas=*/false, SizeThresholds);
	}

	if (AtlasNames.Num() > 1)
	{
		if (GIsAutomationTesting)
		{
			if (!bShouldAutoConfirmMessageBoxes)
			{
				OutMetaData = MetaDataCopy;
				return false;
			}
		}
		else
		{
			FText Message = FText::Format(LOCTEXT("Warning_BuildMoreThanOneAtlas", "Rebuilding atlas "
				"{0} would require creating additional atlases due to modifications to the assets it "
				"contains.\n\nDo you want to continue rebuilding?"), FText::FromString(AtlasPath));
			const EAppReturnType::Type Choice = FMessageDialog::Open(EAppMsgType::YesNo, Message);
			if (Choice == EAppReturnType::Type::No)
			{
				OutMetaData = MetaDataCopy;
				return false;
			}
		}
	}

	return BuildAtlases(AtlasNames, OutMetaData);
}

bool FCohtmlAtlasBuilder::RebuildAtlasWithAddedTextures(const FString& AtlasPath, const TSet<UTexture2D*>& TexturesToAdd, FTextureAtlasMetaData& OutMetaData)
{
	UCohtmlTextureAtlasDetails* AtlasDetails = OutMetaData.AtlasDetails[AtlasPath];
	FTextureAtlasMetaData MetaDataCopy = OutMetaData;
	FTextureSizeThresholds SizeThresholds(AtlasDetails->MaxAtlasWidth, AtlasDetails->MaxAtlasHeight,
		AtlasDetails->MaxTextureWidth, AtlasDetails->MaxTextureHeight);
	TArray<FString> AtlasNames = PackageTexturesInAtlas(AtlasPath, TexturesToAdd, OutMetaData, /*bAddToExistingAtlas*/true, SizeThresholds);

	if (AtlasNames.Num() > 1)
	{
		if (GIsAutomationTesting)
		{
			if (!bShouldAutoConfirmMessageBoxes)
			{
				OutMetaData = MetaDataCopy;
				return false;
			}
		}
		else
		{
			FText Message = FText::Format(LOCTEXT("Warning_BuildMoreThanOneAtlas", "Adding textures to "
				"atlas {0} would require creating additional atlases due to the quantity of items to be "
				"included in it and their dimensions.\n\nDo you want to continue (Alternatively, you can "
				"change the atlas dimensions so that it has enough space for all the textures)?"), FText::FromString(AtlasPath));
			const EAppReturnType::Type Choice = FMessageDialog::Open(EAppMsgType::YesNo, Message);
			if (Choice == EAppReturnType::Type::No)
			{
				OutMetaData = MetaDataCopy;
				return false;
			}
		}
	}

	return BuildAtlases(AtlasNames, OutMetaData);
}

bool FCohtmlAtlasBuilder::BuildNewAtlasFromTextures(const TSet<UTexture2D*>& TexturesToBeAtlased, FTextureAtlasMetaData& OutMetaData)
{
	int32 FirstAvailableIndex = GetFirstAvailableIndex(DefaultAtlasBaseName, OutMetaData.GetAtlases());
	FString DefaultAtlasPath = DefaultAtlasPackageName;
	DefaultAtlasPath += FString::FromInt(FirstAvailableIndex) + TEXT(".") + DefaultAtlasBaseName + FString::FromInt(FirstAvailableIndex);
	FTextureAtlasMetaData MetaDataCopy = OutMetaData;
	TArray<FString> AtlasNames = PackageTexturesInAtlas(DefaultAtlasPath, TexturesToBeAtlased, OutMetaData);

	if (AtlasNames.Num() > 1)
	{
		if (GIsAutomationTesting)
		{
			if (!bShouldAutoConfirmMessageBoxes)
			{
				OutMetaData = MetaDataCopy;
				return false;
			}
		}
		else
		{
			FText Message = FText::Format(LOCTEXT("Warning_BuildMoreThanOneAtlas", "Building atlas "
				"{0} would require creating additional atlases due to the quantity of items to be "
				"included in it and their dimensions.\n\nDo you want to continue?"), FText::FromString(DefaultAtlasPath));
			const EAppReturnType::Type Choice = FMessageDialog::Open(EAppMsgType::YesNo, Message);
			if (Choice == EAppReturnType::Type::No)
			{
				OutMetaData = MetaDataCopy;
				return false;
			}
		}
	}

	return BuildAtlases(AtlasNames, OutMetaData);
}

bool FCohtmlAtlasBuilder::BuildNewEmptyAtlas(FTextureAtlasMetaData& OutMetaData)
{
	int32 FirstAvailableIndex = GetFirstAvailableIndex(DefaultAtlasBaseName, OutMetaData.GetAtlases());
	FString DefaultAtlasPath = DefaultAtlasPackageName;
	DefaultAtlasPath += FString::FromInt(FirstAvailableIndex) + TEXT(".") + DefaultAtlasBaseName + FString::FromInt(FirstAvailableIndex);
	TArray<FString> AtlasNames = CreateNewEmptyAtlasEntry(DefaultAtlasPath, OutMetaData);
	return BuildAtlases(AtlasNames, OutMetaData);
}

void FCohtmlAtlasBuilder::SetAutoConfirmMessageBoxes(bool ShouldAutoConfirmMessageBoxes)
{
	bShouldAutoConfirmMessageBoxes = ShouldAutoConfirmMessageBoxes;
}

bool FCohtmlAtlasBuilder::BuildAtlases(const TArray<FString>& AtlasNames, const FTextureAtlasMetaData& InMetaData)
{
	for (const FString& AtlasName : AtlasNames)
	{
		const FString PackagePath = FString("/Game/Atlases") / AtlasName;
		UPackage* AtlasPackage = CreatePackage(nullptr, *PackagePath);
		const auto AtlasPath = AtlasPackage->GetFName().ToString() + TEXT(".") + AtlasName;

		UTextureRenderTarget2D* Atlas = NewObject<UTextureRenderTarget2D>(
				GetTransientPackage(),
				FName(*(AtlasName + FString::FormatAsNumber(FMath::Rand()))),
				RF_Public | RF_Standalone);
		// We need the atlas to live through until we finish the whole
		// atlas building procedure
		Atlas->AddToRoot();
		Atlas->SizeX = InMetaData.AtlasDetails[AtlasPath]->MaxAtlasWidth;
		Atlas->SizeY = InMetaData.AtlasDetails[AtlasPath]->MaxAtlasHeight;
		Atlas->RenderTargetFormat = RTF_RGBA8;
		Atlas->MipGenSettings = TMGS_NoMipmaps;
		Atlas->SRGB = false;
		Atlas->ClearColor = FLinearColor(0, 0, 0, 0);
		Atlas->CompressionSettings = TC_VectorDisplacementmap; // Don't compress texture to preserve detail
		Atlas->UpdateResource();

		BeginAtlasRenderPass(Atlas);
		InitializeAtlasGraphicsState(InMetaData.AtlasDetails[AtlasPath]->MaxAtlasWidth, InMetaData.AtlasDetails[AtlasPath]->MaxAtlasHeight);
		BuildAtlasTexture(Atlas, AtlasPath, InMetaData);
		EndAtlasRenderPass();
		SaveAtlasPackage(AtlasPackage, Atlas, AtlasPath, AtlasName);
	}

	return true;
}

int32 FCohtmlAtlasBuilder::GetFirstAvailableIndex(const FString& AtlasName, const TArray<AtlasInfoPtr>& Atlases)
{
	TArray<int32> AllIndices;
	for (const AtlasInfoPtr& AtlasInfo : Atlases)
	{
		FString CurrentAtlasName;
		AtlasInfo->AtlasPath.Split(TEXT("."), nullptr, &CurrentAtlasName);
		if (CurrentAtlasName.StartsWith(AtlasName))
		{
			int32 Offset = AtlasName.Len();
			FString IndexAsString = CurrentAtlasName.Mid(Offset);

			if (IndexAsString.StartsWith("_"))
			{
				IndexAsString = IndexAsString.Mid(1);
			}

			if (!IndexAsString.IsNumeric())
			{
				continue;
			}

			AllIndices.AddUnique(FCString::Atoi(*IndexAsString));
		}
	}
	AllIndices.Sort();
	for (int32 ArrayIndex = 0; ArrayIndex < AllIndices.Num(); ArrayIndex++)
	{
		if (ArrayIndex + 1 != AllIndices[ArrayIndex])
		{
			return ArrayIndex + 1;
		}
	}
	return AllIndices.Num() + 1;
}

TArray<FString> FCohtmlAtlasBuilder::CreateNewEmptyAtlasEntry(const FString& AtlasPath, FTextureAtlasMetaData& OutMetaData,
	const FTextureSizeThresholds& SizeThresholds)
{
	FString CurrentAtlasPath = AtlasPath;
	FString CurrentAtlasName;
	CurrentAtlasPath.Split(".", nullptr, &CurrentAtlasName);
	TArray<FString> AtlasNames;

	if (!OutMetaData.AtlasContainedTextures.Contains(AtlasPath) &&
		!OutMetaData.AtlasDetails.Contains(AtlasPath))
	{
		OutMetaData.AtlasContainedTextures.Add(CurrentAtlasPath, NewObject<UCohtmlAtlasContainedTextures>(
			GetTransientPackage(),
			NAME_None,
			RF_Public | RF_Standalone));

		OutMetaData.AtlasDetails.Add(CurrentAtlasPath, NewObject<UCohtmlTextureAtlasDetails>(
			GetTransientPackage(),
			NAME_None,
			RF_Public | RF_Standalone));
		OutMetaData.AtlasDetails[CurrentAtlasPath]->AtlasPath = CurrentAtlasPath;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->Width = SizeThresholds.MaxAtlasWidth;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->Height = SizeThresholds.MaxAtlasHeight;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->PixelFormat = GPixelFormats[PF_B8G8R8A8].Name;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->MaxAtlasWidth = SizeThresholds.MaxAtlasWidth;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->MaxAtlasHeight = SizeThresholds.MaxAtlasHeight;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->MaxTextureWidth = SizeThresholds.MaxTextureWidth;
		OutMetaData.AtlasDetails[CurrentAtlasPath]->MaxTextureHeight = SizeThresholds.MaxTextureHeight;

		OutMetaData.AddAtlas(CurrentAtlasPath);
	}
	else
	{
		OutMetaData.AtlasContainedTextures[AtlasPath]->Textures.Empty();
	}

	AtlasNames.Add(CurrentAtlasName);

	return AtlasNames;
}

bool FCohtmlAtlasBuilder::PrepareTexturesForPacking(TArray<UTexture2D*>& TexturesLeftToPack,
	TArray<Coherent::stbrp_rect>& Rects, const FTextureSizeThresholds& SizeThresholds)
{
	for (auto TextureIt = TexturesLeftToPack.CreateIterator(); TextureIt; ++TextureIt)
	{
		auto Texture = *TextureIt;

		if (!Texture)
		{
			continue;
		}

		if (Texture->Source.GetFormat() != TSF_BGRA8)
		{
			COHTML_EDITOR_UE_LOG(Warning, TEXT("Unable to Atlas texture: %s because it is NOT in the BGRA8 format!"), *Texture->GetFullName());
			continue;
		}

		const auto Width = Texture->GetSizeX();
		const auto Height = Texture->GetSizeY();

		// This texture is too big - don't pack it
		if (Width >= SizeThresholds.MaxTextureWidth || Height >= SizeThresholds.MaxTextureHeight)
		{
			FText Message = FText::FromString(FString::Printf(TEXT("Texture \"%s\" exceeds the")
				TEXT(" maximum texture size thresholds for this atlas and will be removed from it. Size: %dx%dpx,")
				TEXT(" Thresholds: %dx%dpx."),
				*Texture->GetFName().ToString(),
				Width, Height, SizeThresholds.MaxTextureWidth, SizeThresholds.MaxTextureHeight));
			FMessageDialog::Open(EAppMsgType::Ok, Message);
			TextureIt.RemoveCurrent();
			continue;
		}

		const unsigned AlignedWidth = AlignSizeToMultipleOf4(Width);
		const unsigned PaddedHeight = Height + GAtlasPaddingHeight;

		Coherent::stbrp_rect Rect{ 0 };
		Rect.w = static_cast<Coherent::stbrp_coord>(AlignedWidth);
		Rect.h = static_cast<Coherent::stbrp_coord>(PaddedHeight);
		Rects.Add(Rect);
	}

	return true;
}

void FCohtmlAtlasBuilder::PopulateDataWithPackedTextures(const FString& InAtlasPath, TArray<UTexture2D*>& TexturesToPack, FTextureAtlasMetaData& OutMetaData,
	TArray<Coherent::stbrp_rect>& Rects, TArray<FString>& AtlasNames, const FTextureSizeThresholds& SizeThresholds, bool bIsExistingAtlas)
{
	FString AtlasPath = InAtlasPath;
	FString AtlasName;
	AtlasPath.Split(".", nullptr, &AtlasName);
	TSet<UTexture2D*> PackedTextures;
	TArray<UTexture2D*> TexturesLeftToPack;
	for (const auto& Texture : TexturesToPack)
	{
		if (!Texture)
		{
			continue;
		}

		Coherent::stbrp_rect Rect = Rects[0];
		Rects.RemoveAt(0);
		if (Rect.was_packed)
		{
			PackedTextures.Add(Texture);

			Rect.x += GAtlasPaddingWidth;
			Rect.y += GAtlasPaddingHeight;

			FTextureAtlasMappingInfo MappingData;
			MappingData.AtlasPath = AtlasPath;
			MappingData.Width = Rect.w;
			MappingData.Height = Rect.h;
			MappingData.OriginX = Rect.x;
			MappingData.OriginY = Rect.y;

			OutMetaData.AddAtlasedAsset(Texture->GetPathName(), MappingData);
		}
		else
		{
			TexturesLeftToPack.Add(Texture);
		}
	}

	OutMetaData.AtlasContainedTextures[AtlasPath]->Textures = PackedTextures;
	TexturesToPack = TexturesLeftToPack;
	if (!bIsExistingAtlas)
	{
		OutMetaData.AtlasDetails.Add(AtlasPath, NewObject<UCohtmlTextureAtlasDetails>(
			GetTransientPackage(),
			NAME_None,
			RF_Public | RF_Standalone));
	}
	OutMetaData.AtlasDetails[AtlasPath]->AtlasPath = AtlasPath;
	// TODO: Once we start clamping the atlas, these two won't be
	// set to max width / height and will be taken from stbrp
	OutMetaData.AtlasDetails[AtlasPath]->Width = SizeThresholds.MaxAtlasWidth;
	OutMetaData.AtlasDetails[AtlasPath]->Height = SizeThresholds.MaxAtlasHeight;
	// We always create atlas textures in that format
	OutMetaData.AtlasDetails[AtlasPath]->PixelFormat = GPixelFormats[PF_B8G8R8A8].Name;
	OutMetaData.AtlasDetails[AtlasPath]->MaxAtlasWidth = SizeThresholds.MaxAtlasWidth;
	OutMetaData.AtlasDetails[AtlasPath]->MaxAtlasHeight = SizeThresholds.MaxAtlasHeight;
	OutMetaData.AtlasDetails[AtlasPath]->MaxTextureWidth = SizeThresholds.MaxTextureWidth;
	OutMetaData.AtlasDetails[AtlasPath]->MaxTextureHeight = SizeThresholds.MaxTextureHeight;

	OutMetaData.AddAtlas(AtlasPath);

	AtlasNames.Add(AtlasName);
}

void FCohtmlAtlasBuilder::BuildAtlasTexture(UTextureRenderTarget2D* Atlas, const FString& AtlasPath, const FTextureAtlasMetaData& InMetaData)
{
	// Use a temporary array as it has TArray::StableSort whereas TSet::Sort leads to non-deterministic
	// order of the packed textures
	TArray<UTexture2D*> TexturesToAtlasArray = InMetaData.AtlasContainedTextures[AtlasPath]->Textures.Array();
	TexturesToAtlasArray.StableSort([](const UTexture2D& First, const UTexture2D& Second) {
		if (First.GetSizeX() == Second.GetSizeX())
		{
			return First.GetSizeY() >= Second.GetSizeY();
		}
		return First.GetSizeX() >= Second.GetSizeX();
	});
	for (const auto& Texture : TexturesToAtlasArray)
	{
		if (!Texture)
		{
			continue;
		}

		const FTextureAtlasMappingInfo* TextureMappingInfo = InMetaData.GetAtlasedTextures().Find(Texture->GetPathName());
		FTextureSizeThresholds SizeThresholds;
		SizeThresholds.MaxAtlasWidth = InMetaData.AtlasDetails[AtlasPath]->MaxAtlasWidth;
		SizeThresholds.MaxAtlasHeight = InMetaData.AtlasDetails[AtlasPath]->MaxAtlasHeight;
		DrawTextureInAtlas(Atlas, Texture, TextureMappingInfo, SizeThresholds);
		FlushRenderingCommands();
	}
}

void FCohtmlAtlasBuilder::SaveAtlasPackage(UPackage* AtlasPackage, UTextureRenderTarget2D* Atlas, const FString& AtlasPath, const FString& AtlasName)
{
#if defined(COHTML_UE4_419_SUPPORT)
	UTexture2D* AtlasTexture2D = Atlas->ConstructTexture2D(AtlasPackage, AtlasName, RF_Public | RF_Standalone, CTF_DeferCompression);
#else
	UTexture2D* AtlasTexture2D = FindObject<UTexture2D>(nullptr, *AtlasPath);

	// Construct a temp package for the newly built atlas and copy the pixel
	// data in the existing one if we're rebuilding. This will avoid recreating
	// the actual texture object which is used by the Slate brush to draw it
	// in our atlas preview window
	UPackage* PackageToConstructIn = AtlasTexture2D ? GetTransientPackage() : AtlasPackage;
	FString NameToConstructWith = AtlasTexture2D ? FString::Printf(TEXT("TempPackage%d"), FMath::Rand()) : AtlasName;
	UTexture2D* AtlasTexture2DCopy = Atlas->ConstructTexture2D(PackageToConstructIn, NameToConstructWith, RF_Public | RF_Standalone, CTF_DeferCompression);

	const uint32 AtlasWidth = static_cast<uint32>(AtlasTexture2DCopy->GetSizeX());
	const uint32 AtlasHeight = static_cast<uint32>(AtlasTexture2DCopy->GetSizeY());

	if (!AtlasTexture2D)
	{
		AtlasTexture2D = AtlasTexture2DCopy;
	}
	else
	{
		uint8* TexData = AtlasTexture2DCopy->Source.LockMip(0);
		AtlasTexture2D->Source.Init(AtlasWidth, AtlasHeight, 1, 1, TSF_BGRA8, TexData);
		AtlasTexture2DCopy->Source.UnlockMip(0);
	}
#endif
	// We no longer need it
	Atlas->RemoveFromRoot();

	AtlasTexture2D->SRGB = false;
	AtlasTexture2D->CompressionSettings = TC_VectorDisplacementmap; // Don't compress texture to preserve detail
	AtlasTexture2D->UpdateResource();

	TArray<UPackage*> Packages = { AtlasPackage };
	UEditorLoadingAndSavingUtils::SavePackages(Packages, false);
}

#undef LOCTEXT_NAMESPACE