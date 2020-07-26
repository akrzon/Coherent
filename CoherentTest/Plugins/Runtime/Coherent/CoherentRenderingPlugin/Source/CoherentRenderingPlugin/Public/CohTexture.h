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
#pragma once

#include <RenderResource.h>
#include <RenoirBackend/Textures.h>

#include "CohTexture.generated.h"

#if PLATFORM_PS4 || PLATFORM_DPX || PLATFORM_XBOXONE
#define TRACK_TEXTURE_DRAWS 1
#else
#define TRACK_TEXTURE_DRAWS 0
#endif

// Uncomment this to start logging texture descriptions
//#define COHERENT_LOG_TEXTURE_DESC

USTRUCT(BlueprintInternalUseOnly)
struct COHERENTRENDERINGPLUGIN_API FCohTextureUserWrapData
{
	GENERATED_BODY();
public:
	FCohTextureUserWrapData() : Texture(NULL)
	{}

	FCohTextureUserWrapData(const renoir::Texture2D& Description,
		UTexture* Wrapped)
		: RenoirDescription(Description)
		, Texture(Wrapped)
	{}

	renoir::Texture2D GetDesc() const { return RenoirDescription; }
	UTexture* GetUTexture() const { return Texture; }

	// Non-empty only if this texture is used for live views
	FString LiveViewUrl;
private:
	renoir::Texture2D RenoirDescription;

	UPROPERTY()
	UTexture* Texture;
};

class COHERENTRENDERINGPLUGIN_API FCohTexture
{
public:
	FCohTexture(const renoir::Texture2D& Description,
		const void* SrcData,
		unsigned DataLen);
	FCohTexture(const renoir::Texture2D& Description,
		FRHITexture2D* Wrapped);
	FCohTexture(const FCohTextureUserWrapData& WrapData);
	~FCohTexture();

	void Update(const renoir::Texture2D& Description,
		renoir::UpdateBox* Boxes,
		const void** NewBytes,
		unsigned Count,
		bool WillOverwrite);

	const renoir::Texture2D& GetRenoirDescription() const;
	bool IsRenderTarget() const;
	FTexture2DRHIRef GetTextureRHI() const;
	FTexture2DRHIRef GetRenderTargetRHI() const;
	size_t GetMemorySize();

#if TRACK_TEXTURE_DRAWS
	bool bPossibleDrawInFlight;
#endif
	// Non-empty only if this texture is used for live views
	FString LiveViewUrl;
private:
	void ClampTextureSize(unsigned& Width, unsigned& Height);
	void InitRHI(const void* srcData, unsigned rowBytes);

	renoir::Texture2D RenoirDescription;
	FTexture2DRHIRef RenderTargetTextureRHI;
	FTexture2DRHIRef TextureRHI;
};
