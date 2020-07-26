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
#include "CohStencilBuffer.h"

#include "RHIUtilities.h"

FCohStencilBuffer::FCohStencilBuffer(
	int32 width, int32 height, int32 samplesCnt)
	: Width(width)
	, Height(height)
	, SamplesCnt(samplesCnt)
{
	ClampTextureSize(Width, Height);
	InitRHI();
}

void FCohStencilBuffer::ClampTextureSize(int& SizeX, int& SizeY)
{
	const int Max2DTexDim = int(GetMax2DTextureDimension());
	if (SizeX < 1 || SizeX > Max2DTexDim || SizeY < 1 || SizeY > Max2DTexDim)
	{
		UE_LOG(LogCoherentRendering, Warning, TEXT("Trying to create a stencil buffer with dimensions: %d x %d. ")
			TEXT("The texture will be clamped in the [1-%d] range!"), SizeX, SizeY, Max2DTexDim);
		SizeX = FMath::Clamp(SizeX, 1, Max2DTexDim);
		SizeY = FMath::Clamp(SizeY, 1, Max2DTexDim);
	}
}

void FCohStencilBuffer::InitRHI()
{
	FTexture2DRHIRef ShaderResourceUnused;
	FRHIResourceCreateInfo CreateInfo;
	CreateInfo.ClearValueBinding = FClearValueBinding(0.f, 1);
	const auto samplesCnt = FMath::Max(SamplesCnt, 1);
		RHICreateTargetableShaderResource2D(
		Width,
		Height,
		PF_DepthStencil, // 24 - 8
		1,
		TexCreate_None,
		TexCreate_DepthStencilTargetable,
		false,
		CreateInfo,
		StencilBufferRHI,
		ShaderResourceUnused,
		samplesCnt);
}

unsigned FCohStencilBuffer::GetBitsCount() const
{
	return 8;
}

unsigned FCohStencilBuffer::GetSamplesCount() const
{
	return SamplesCnt;
}

unsigned FCohStencilBuffer::GetSizeInBytes() const
{
	return Width * Height * 4;
}

unsigned FCohStencilBuffer::GetWidth() const
{
	return Width;
}

unsigned FCohStencilBuffer::GetHeight() const
{
	return Height;
}

FTexture2DRHIRef FCohStencilBuffer::GetStencilTexture() const
{
	return StencilBufferRHI;
}
