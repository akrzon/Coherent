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

#include "GlobalShader.h"
#include "ShaderParameterUtils.h"

#include <RenoirBackend/ConstantBuffers.h>
#include <RenoirBackend/PipelineState.h>

namespace
{
	const uint32 MAX_BOUND_TEXTURES = 4u;
	const uint32 MAX_BOUND_SAMPLERS = 4u;
}

namespace CohShaders
{
	// Split all cbuffers from the shaders into multiple global constants.
	// Prefix each member of the cbuffer with the cbuffer's name to separate them
	class FCohShaderVS : public FGlobalShader
	{
	public:
		FCohShaderVS() {}
		FCohShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
			: FGlobalShader(Initializer)
		{
			BindParams(Initializer);
		}
		void BindParams(const FGlobalShaderType::CompiledShaderInitializerType& Initializer);

		void BindBuffer(FRHICommandList& CmdList, renoir::CBType BufferType, const void* BufferData);

		virtual bool Serialize(FArchive& Ar) override;

	private:
		FShaderParameter TransformVS_Transform;
		FShaderParameter RenoirShaderVS_CoordTransformVS;
		FShaderParameter RenoirShaderVS_MaskScaleAndOffset;
	};

	class FCohShaderPS : public FGlobalShader
	{
	public:
		FCohShaderPS() {}
		FCohShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
			: FGlobalShader(Initializer)
		{
			BindParams(Initializer);
		}
		void BindParams(const FGlobalShaderType::CompiledShaderInitializerType& Initializer);

		void BindBuffer(FRHICommandList& CmdList, renoir::CBType BufferType, const void* BufferData);

		void SetShaderSampler(FRHICommandList* CmdList, int32 slot, FRHISamplerState* Sampler);
		void SetShaderTexture(FRHICommandList* CmdList, int32 slot, FRHITexture2D* Texture);

		virtual bool Serialize(FArchive& Ar) override;

	private:
		FShaderParameter GlobalPixelCB_ViewportSize;
		FShaderParameter StandardPrimitivePixel_ShaderType;
		FShaderParameter StandardPrimitiveAdditionalPixel_PrimProps0;
		FShaderParameter StandardPrimitiveAdditionalPixel_PrimProps1;
		FShaderParameter RenoirShaderPS_GradientStartColor;
		FShaderParameter RenoirShaderPS_GradientMidColor;
		FShaderParameter RenoirShaderPS_GradientEndColor;
		FShaderParameter RenoirShaderPS_GradientYCoord;
		FShaderParameter EffectsPixelCB_Coefficients;
		FShaderParameter EffectsPixelCB_PixelOffsets;
		FShaderResourceParameter TextureBuffer[MAX_BOUND_TEXTURES];
		FShaderResourceParameter SamplerState[MAX_BOUND_TEXTURES];
	};

	template <renoir::ShaderType ShaderType>
	class TCohShaderVS : public FCohShaderVS
	{
		DECLARE_SHADER_TYPE(TCohShaderVS, Global);

	public:
		TCohShaderVS() {}
		TCohShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
			: FCohShaderVS(Initializer) {}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
		static void ModifyCompilationEnvironment(EShaderPlatform Parameters, FShaderCompilerEnvironment& OutEnvironment)
#else
		static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
#endif
		{
			OutEnvironment.SetDefine(TEXT("__UE4__"), TEXT("1"));
#if defined(COHERENT_RENDERING_UE4_416_SUPPORT)
			OutEnvironment.SetDefine(TEXT("__UE4_416_SUPPORT__"), TEXT("1"));
#endif
		}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
		static bool ShouldCache(EShaderPlatform Platform)
#else
		static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
#endif
		{
			return true;
		}
	};

	template <renoir::ShaderType ShaderType>
	class TCohShaderPS : public FCohShaderPS
	{
		DECLARE_SHADER_TYPE(TCohShaderPS, Global);

	public:
		TCohShaderPS() {}
		TCohShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
			: FCohShaderPS(Initializer) {}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
		static void ModifyCompilationEnvironment(EShaderPlatform Parameters, FShaderCompilerEnvironment& OutEnvironment)
#else
		static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
#endif
		{
			OutEnvironment.SetDefine(TEXT("__UE4__"), TEXT("1"));
#if defined(COHERENT_RENDERING_UE4_416_SUPPORT)
			OutEnvironment.SetDefine(TEXT("__UE4_416_SUPPORT__"), TEXT("1"));
#endif
		}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
		static bool ShouldCache(EShaderPlatform Platform)
#else
		static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
#endif
		{
			return true;
		}
	};

	typedef TCohShaderVS<renoir::ST_Standard> FRenoirStandardVS;
	typedef TCohShaderVS<renoir::ST_BatchedStandard> FRenoirStandardBatchedVS;
	typedef TCohShaderVS<renoir::ST_StandardRare> FRenoirStandardRareVS;
	typedef TCohShaderVS<renoir::ST_RenoirShader> FRenoirVS;
	typedef TCohShaderVS<renoir::ST_Path> FRenoirPathVS;
	typedef TCohShaderVS<renoir::ST_ClearQuad> FRenoirClearQuadVS;

	typedef TCohShaderPS<renoir::ST_Standard> FRenoirStandardPS;
	typedef TCohShaderPS<renoir::ST_BatchedStandard> FRenoirStandardBatchedPS;
	typedef TCohShaderPS<renoir::ST_StandardRare> FRenoirStandardRarePS;
	typedef TCohShaderPS<renoir::ST_Stencil> FRenoirStencilPS;
	typedef TCohShaderPS<renoir::ST_StencilRare> FRenoirStencilRarePS;
	typedef TCohShaderPS<renoir::ST_RenoirShader> FRenoirPS;
	typedef TCohShaderPS<renoir::ST_TexturesWithColorMix> FTexturesWithColorMixPS;
	typedef TCohShaderPS<renoir::ST_Path> FRenoirPathPS;
	typedef TCohShaderPS<renoir::ST_StencilPath> FRenoirStencilPathPS;
	typedef TCohShaderPS<renoir::ST_ClearQuad> FRenoirClearQuadPS;
}
