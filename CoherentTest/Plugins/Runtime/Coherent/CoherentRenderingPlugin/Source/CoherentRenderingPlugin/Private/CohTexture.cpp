/*
This file is part of Renoir, a modern graphics library.
Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

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
#include "CoherentRenderingPluginPrivatePCH.h"
#include "CohTexture.h"

#include "RHIUtilities.h"
#include "CohHelpers.h"

#include "Containers/ResourceArray.h"
#include "Engine/Texture2D.h"

void LogTextureDescription(FString textureType, const renoir::Texture2D& desc)
{
	UE_LOG(LogCoherentRendering, Log, TEXT("Creating a %s - %dW %dH / ContentRect - (%d, %d, %d, %d) / BaseAli - %d / Format - %d "),
		*textureType, desc.Width, desc.Height, desc.ContentRectWidth, desc.ContentRectHeight, desc.ContentRectX, desc.ContentRectY,
		desc.BaseAlignment, static_cast<int>(desc.Format));
	UE_LOG(LogCoherentRendering, Log, TEXT("Dynamic - %d / RenderTarget - %d / XBFormat - %d / MipsCount - %d / SamplesCount - %d / TileMode - %d / NeverOverwrite - %d"),
		!!(desc.Props & renoir::IMP_Dynamic), desc.IsRenderTarget, !!(desc.Props & renoir::IMP_XBDDS), desc.MipsCount, desc.SamplesCount, desc.TileMode, desc.WillNeverOverwrite);
}

FCohTexture::FCohTexture(const renoir::Texture2D& desc,
	const void* srcData,
	unsigned rowBytes)
	: RenoirDescription(desc)
{
#ifdef COHERENT_LOG_TEXTURE_DESC
	LogTextureDescription("Auxiliary texture", desc);
#endif

	ClampTextureSize(RenoirDescription.Width, RenoirDescription.Height);

	InitRHI(srcData, rowBytes);
}

void FCohTexture::ClampTextureSize(unsigned& Width, unsigned& Height)
{
	const auto Max2DTexDim = GetMax2DTextureDimension();
	if (Width < 1 || Width > Max2DTexDim || Height < 1 || Height > Max2DTexDim)
	{
		UE_LOG(LogCoherentRendering, Warning, TEXT("Trying to create a texture with dimensions: %d x %d. ")
			TEXT("The texture will be clamped in the [1-%d] range!"), Width, Height, Max2DTexDim);
		Width = FMath::Clamp(Width, 1u, Max2DTexDim);
		Height = FMath::Clamp(Height, 1u, Max2DTexDim);
	}
}

FCohTexture::FCohTexture(const renoir::Texture2D& Description,
	FRHITexture2D* wrapped)
	: RenoirDescription(Description)
{
#ifdef COHERENT_LOG_TEXTURE_DESC
	LogTextureDescription("Texture", Description);
#endif

	verify(!Description.IsRenderTarget);
	verify(wrapped);

	TextureRHI = wrapped;
}

FCohTexture::FCohTexture(const FCohTextureUserWrapData& WrapData)
	: RenoirDescription(WrapData.GetDesc())
{
#ifdef COHERENT_LOG_TEXTURE_DESC
	LogTextureDescription("Preloaded texture", Description);
#endif

	verify(!RenoirDescription.IsRenderTarget);
	UTexture* Wrapped = WrapData.GetUTexture();
	verify(Wrapped);

	if (!Wrapped->Resource->IsInitialized())
	{
		Wrapped->Resource->InitResource();
	}
	auto RHITexture = Wrapped->Resource->TextureRHI->GetTexture2D();
	check(RHITexture && TEXT("Invalid texture source for FCohTexture"));
	UE_LOG(LogCoherentRendering, Verbose, TEXT("RHI constructing user texture: %p"), RHITexture);
	this->TextureRHI = RHITexture;
}

FCohTexture::~FCohTexture()
{
	UE_LOG(LogCoherentRendering, Verbose, TEXT("Destroying texture: %p"), this);
}

struct FCohTexBulkData : public FResourceBulkDataInterface
{
	FCohTexBulkData(const void* srcData, uint32 size)
		: Data(srcData)
		, Size(size)
	{}

	virtual const void* GetResourceBulkData() const override
	{
		return Data;
	}

	virtual uint32 GetResourceBulkDataSize() const
	{
		return Size;
	}

	virtual void Discard() {}

private:
	const void* Data;
	uint32 Size;
};

void FCohTexture::InitRHI(const void* SrcData, unsigned DataLen)
{
	uint32 TexCreateFlags = 0;
	if (RenoirDescription.Props & renoir::IMP_Dynamic)
	{
		TexCreateFlags |= TexCreate_Dynamic;
	}

#if PLATFORM_XBOXONE && ENGINE_MINOR_VERSION >= 10 && ENGINE_MINOR_VERSION < 12
	TArray<uint8_t> PaddedSrcData;
	// Textures on the XBox require dimensions that are multiple of 8 so pad in a temp memory
	const uint8_t Padding = 8u;
	if (SrcData && (RenoirDescription.Width % Padding != 0))
	{
		const auto PaddedWidth = RenoirDescription.Width + Padding - (RenoirDescription.Width % Padding);
		const auto PaddedHeight = RenoirDescription.Height; // Do not pad height, as the only thing making a difference is the stride
		const auto Bpp = renoir::BitsPerPixel(RenoirDescription.Format);
		PaddedSrcData.SetNumUninitialized(PaddedWidth * PaddedHeight * Bpp / 8);
		const auto PaddedWidthBytes = PaddedWidth * Bpp / 8;
		const auto OriginalStrideBytes = RenoirDescription.Width * Bpp / 8;
		const auto AddedPaddingBytes = (PaddedWidth - RenoirDescription.Width) * Bpp / 8;
		for (auto RowIndex = 0u; RowIndex < RenoirDescription.Height; ++RowIndex)
		{
			FMemory::Memcpy(PaddedSrcData.GetData() + RowIndex * PaddedWidthBytes,
				static_cast<const uint8_t*>(SrcData) + RowIndex * OriginalStrideBytes,
				OriginalStrideBytes);
			FMemory::Memset(PaddedSrcData.GetData() + RowIndex * PaddedWidthBytes + OriginalStrideBytes, 0, AddedPaddingBytes);
		}
		SrcData = PaddedSrcData.GetData();
		DataLen = PaddedWidth * PaddedHeight * Bpp / 8;
	}
#endif

	FRHIResourceCreateInfo CreateInfo;
	FCohTexBulkData bulkData(SrcData, DataLen);

	const bool bUnableToInitCompressedTextureWithData = IsOpenGLPlatform(GMaxRHIShaderPlatform) && renoir::IsBlockCompressedFormat(RenoirDescription.Format);

	if (bUnableToInitCompressedTextureWithData)
	{
		UE_LOG(LogCoherentRendering, Error, TEXT("Unable to initialize compressed texture with data! Creating empty texture!"
			"This happens, because OpenGL RHI does not support creating RHITexture with data for compressed formats!"));
	}
	else if (SrcData)
	{
		CreateInfo.BulkData = &bulkData;
#if !defined(COHERENT_RENDERING_UE4_419_SUPPORT)
		// TODO: In Dx12 mode when we create a texture with initial data
		// The engine tries to update some residency on a resource.
		// However from time to time the current command list is closed
		// and the residency set is closed which leads to a crash inside
		// the engine. This call fixes this but it is probably a perf
		// problem so investigate better fix.
		RHIFlushResources();
#endif
	}

	const auto SamplesCount = FMath::Max(RenoirDescription.SamplesCount, 1u);

	if (RenoirDescription.IsRenderTarget)
	{
		RHICreateTargetableShaderResource2D(
			RenoirDescription.Width,
			RenoirDescription.Height,
			renoir::ToUnrealTextureFormat(RenoirDescription.Format),
			1,
			TexCreateFlags,
			TexCreate_RenderTargetable | TexCreate_NoFastClear,
			false,
			CreateInfo,
			RenderTargetTextureRHI,
			TextureRHI,
			SamplesCount);
		verify(RenderTargetTextureRHI);
	}
	else
	{
		TextureRHI = RHICreateTexture2D(
			RenoirDescription.Width,
			RenoirDescription.Height,
			renoir::ToUnrealTextureFormat(RenoirDescription.Format),
			1,
			SamplesCount,
			TexCreateFlags | TexCreate_ShaderResource,
			CreateInfo);
	}
	verify(TextureRHI);
#if TRACK_TEXTURE_DRAWS
	bPossibleDrawInFlight = false;
#endif
}

void FCohTexture::Update(const renoir::Texture2D& Description,
	renoir::UpdateBox* Boxes,
	const void** NewBytes,
	unsigned Count,
	bool WillOverwrite)
{
	if (renoir::IsBlockCompressedFormat(RenoirDescription.Format))
	{
		UE_LOG(LogCoherentRendering, Error, TEXT("Updating block compressed textures is not implemented!"));
		return;
	}

#if PLATFORM_XBOXONE
	// The XB1 driver crashes if one attempts to update a texture while commands to it have already been issued
	// which means we need to flush and wait for them. UE4 actually does flush and wait for these commands
	// when updating Texture3D, so the issue seems to be more general.
	// The next lines mimic the behaviour of FRHICommandListImmediate::ImmediateFlush(EImmediateFlushType::RHIThread)
	auto& ImmediateCmdList = FRHICommandListExecutor::GetImmediateCommandList();
	// Don't call directly ImmediateCmdList.Flush() here because the implementation expects
	// a deferred command list. FRHICommandListImmediate::ImmediateFlush does the same
	if (ImmediateCmdList.HasCommands())
	{
		GRHICommandList.ExecuteList(ImmediateCmdList);
	}
	ImmediateCmdList.WaitForDispatch();
#if defined(COHERENT_RENDERING_UE4_416_SUPPORT)
	if (GRHIThread)
#else
	if (GRHIThreadId)
#endif
	{
		ImmediateCmdList.WaitForRHIThreadTasks();
	}
	ImmediateCmdList.WaitForTasks(true);
#endif

	// TODO: Text Atlases get written too often
	// Maybe we should cache writes in RAM and flush them all after
	const auto Bpp = renoir::BitsPerPixel(Description.Format);
	for (auto i = 0u; i < Count; ++i)
	{
		const auto& Box = Boxes[i];
		FUpdateTextureRegion2D region;
		region.SrcX = 0;
		region.SrcY = 0;
		region.DestX = Box.Left;
		region.DestY = Box.Top;
		region.Width = Box.Right - Box.Left;
		region.Height = Box.Bottom - Box.Top;
		const auto RowLen = region.Width * Bpp / 8;
		RHIUpdateTexture2D(TextureRHI,
			0,
			region,
			RowLen,
			(const uint8*)NewBytes[i]);
	}
#if TRACK_TEXTURE_DRAWS
	bPossibleDrawInFlight = true;
#endif
}

size_t FCohTexture::GetMemorySize()
{
	size_t TexSize = 0;
	renoir::GetTexture2DSizes(RenoirDescription.Width, RenoirDescription.Height, RenoirDescription.Format, &TexSize, nullptr, nullptr);
	return  TexSize * RenoirDescription.SamplesCount;
}

FTexture2DRHIRef FCohTexture::GetTextureRHI() const
{
	return TextureRHI;
}

FTexture2DRHIRef FCohTexture::GetRenderTargetRHI() const
{
	return RenderTargetTextureRHI;
}

const renoir::Texture2D& FCohTexture::GetRenoirDescription() const
{
	return RenoirDescription;
}

bool FCohTexture::IsRenderTarget() const
{
	return RenoirDescription.IsRenderTarget;
}
