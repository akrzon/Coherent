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
#include "CohRenoirShaders.h"

namespace CohShaders
{
#if defined(COHERENT_RENDERING_UE4_416_SUPPORT)
#define SHADER_DIRECTORY TEXT("")
#define SHADER_EXTENSION TEXT("")
#else
#define SHADER_DIRECTORY TEXT("/Plugin/CoherentRenderingPlugin/Private/")
#define SHADER_EXTENSION TEXT(".usf")
#endif
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStandardVS, SHADER_DIRECTORY TEXT("CohStandardVS") SHADER_EXTENSION, TEXT("StandardVS"), SF_Vertex);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStandardPS, SHADER_DIRECTORY TEXT("CohStandardPS") SHADER_EXTENSION, TEXT("StandardPS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStandardBatchedVS, SHADER_DIRECTORY TEXT("CohStandardBatchedVS") SHADER_EXTENSION, TEXT("StandardBatchedVS"), SF_Vertex);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStandardBatchedPS, SHADER_DIRECTORY TEXT("CohStandardBatchedPS") SHADER_EXTENSION, TEXT("StandardBatchedPS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStandardRareVS, SHADER_DIRECTORY TEXT("CohStandardVS") SHADER_EXTENSION, TEXT("StandardVS"), SF_Vertex);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStandardRarePS, SHADER_DIRECTORY TEXT("CohStandardRarePS") SHADER_EXTENSION, TEXT("StandardRarePS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FRenoirPathVS, SHADER_DIRECTORY TEXT("CohPathVS") SHADER_EXTENSION, TEXT("PathVS"), SF_Vertex);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirPathPS, SHADER_DIRECTORY TEXT("CohPathPS") SHADER_EXTENSION, TEXT("PathPS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FRenoirVS, SHADER_DIRECTORY TEXT("CohRenoirShaderVS") SHADER_EXTENSION, TEXT("RenoirShaderVS"), SF_Vertex);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirPS, SHADER_DIRECTORY TEXT("CohRenoirShaderPS") SHADER_EXTENSION, TEXT("RenoirShaderPS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStencilPS, SHADER_DIRECTORY TEXT("CohStencilPS") SHADER_EXTENSION, TEXT("StencilPS"), SF_Pixel);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStencilRarePS, SHADER_DIRECTORY TEXT("CohStencilRarePS") SHADER_EXTENSION, TEXT("StencilRarePS"), SF_Pixel);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirStencilPathPS, SHADER_DIRECTORY TEXT("CohStencilPathPS") SHADER_EXTENSION, TEXT("StencilPathPS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FTexturesWithColorMixPS, SHADER_DIRECTORY TEXT("CohColorMixingPS") SHADER_EXTENSION, TEXT("ColorMixingPS"), SF_Pixel);

	IMPLEMENT_SHADER_TYPE(template <>, FRenoirClearQuadVS, SHADER_DIRECTORY TEXT("CohClearQuadVS") SHADER_EXTENSION, TEXT("ClearQuadVS"), SF_Vertex);
	IMPLEMENT_SHADER_TYPE(template <>, FRenoirClearQuadPS, SHADER_DIRECTORY TEXT("CohClearQuadPS") SHADER_EXTENSION, TEXT("ClearQuadPS"), SF_Pixel);
#undef SHADER_DIRECTORY
#undef SHADER_EXTENSION

	void FCohShaderVS::BindParams(const FGlobalShaderType::CompiledShaderInitializerType& Initializer)
	{
		TransformVS_Transform.Bind(Initializer.ParameterMap, TEXT("Transform"));
		RenoirShaderVS_CoordTransformVS.Bind(Initializer.ParameterMap, TEXT("CoordTransformVS"));
		RenoirShaderVS_MaskScaleAndOffset.Bind(Initializer.ParameterMap, TEXT("MaskScaleAndOffset"));
	}

	void FCohShaderVS::BindBuffer(FRHICommandList& CmdList, renoir::CBType BufferType, const void* BufferData)
	{
		if (!BufferData)
		{
			return;
		}

		switch (BufferType)
		{
		case renoir::CBType::CB_Transforms:
		{
			auto& Data = *reinterpret_cast<const renoir::CBTransforms*>(BufferData);
			::SetShaderValue<FRHIVertexShader*, renoir::float4x4>(
				CmdList, GetVertexShader(), TransformVS_Transform, Data.Transform);
			break;
		}
		case renoir::CBType::CB_RenoirShaderVS:
		{
			auto& Data = *reinterpret_cast<const renoir::RenoirShaderVS*>(BufferData);
			::SetShaderValue<FRHIVertexShader*, renoir::float4x4>(
				CmdList, GetVertexShader(), RenoirShaderVS_CoordTransformVS, Data.Matrix0);
			::SetShaderValue<FRHIVertexShader*, renoir::float4>(
				CmdList, GetVertexShader(), RenoirShaderVS_MaskScaleAndOffset, Data.Prop0);
			break;
		}
		case renoir::CBType::CB_GlobalPixel:
		case renoir::CBType::CB_StandardPrimitivePixel:
		case renoir::CBType::CB_StandardPrimitiveAdditionalPixel:
		case renoir::CBType::CB_RenoirShaderPS:
		case renoir::CBType::CB_EffectsPixel:
			check(false && "PS buffer used in a VS!");
			break;
		default:
			check(false && "Unknown constant buffer type!");
		}
	}


	bool FCohShaderVS::Serialize(FArchive& Ar)
	{
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << TransformVS_Transform
			<< RenoirShaderVS_CoordTransformVS << RenoirShaderVS_MaskScaleAndOffset;
		return bShaderHasOutdatedParameters;
	}

	void FCohShaderPS::SetShaderSampler(FRHICommandList* CmdList, int32 slot, FRHISamplerState* Sampler)
	{
		auto& SamplerParam = SamplerState[slot];
		::SetSamplerParameter(*CmdList, GetPixelShader(), SamplerParam, Sampler);
	}

	void FCohShaderPS::SetShaderTexture(FRHICommandList* CmdList, int32 slot, FRHITexture2D* Texture)
	{
		auto& TextureParam = TextureBuffer[slot];
		::SetTextureParameter(*CmdList, GetPixelShader(), TextureParam, Texture);
	}

	void FCohShaderPS::BindParams(const FGlobalShaderType::CompiledShaderInitializerType& Initializer)
	{
		GlobalPixelCB_ViewportSize.Bind(Initializer.ParameterMap, TEXT("ViewportSize"));
		StandardPrimitivePixel_ShaderType.Bind(Initializer.ParameterMap, TEXT("ShaderType"));
		StandardPrimitiveAdditionalPixel_PrimProps0.Bind(Initializer.ParameterMap, TEXT("PrimProps0"));
		StandardPrimitiveAdditionalPixel_PrimProps1.Bind(Initializer.ParameterMap, TEXT("PrimProps1"));
		RenoirShaderPS_GradientStartColor.Bind(Initializer.ParameterMap, TEXT("GradientStartColor"));
		RenoirShaderPS_GradientMidColor.Bind(Initializer.ParameterMap, TEXT("GradientMidColor"));
		RenoirShaderPS_GradientEndColor.Bind(Initializer.ParameterMap, TEXT("GradientEndColor"));
		RenoirShaderPS_GradientYCoord.Bind(Initializer.ParameterMap, TEXT("GradientYCoord"));
		EffectsPixelCB_Coefficients.Bind(Initializer.ParameterMap, TEXT("Coefficients"));
		EffectsPixelCB_PixelOffsets.Bind(Initializer.ParameterMap, TEXT("PixelOffsets"));

		TextureBuffer[0].Bind(Initializer.ParameterMap, TEXT("txBuffer"));
		TextureBuffer[1].Bind(Initializer.ParameterMap, TEXT("txBuffer1"));
		TextureBuffer[2].Bind(Initializer.ParameterMap, TEXT("txBuffer2"));
		TextureBuffer[3].Bind(Initializer.ParameterMap, TEXT("txBuffer3"));
		SamplerState[0].Bind(Initializer.ParameterMap, TEXT("txBufferSampler"));
		SamplerState[1].Bind(Initializer.ParameterMap, TEXT("txBuffer1Sampler"));
		SamplerState[2].Bind(Initializer.ParameterMap, TEXT("txBuffer2Sampler"));
		SamplerState[3].Bind(Initializer.ParameterMap, TEXT("txBuffer3Sampler"));
	}

	void FCohShaderPS::BindBuffer(FRHICommandList& CmdList, renoir::CBType BufferType, const void* BufferData)
	{
		if (!BufferData)
		{
			return;
		}

		switch (BufferType)
		{
		case renoir::CBType::CB_GlobalPixel:
		{
			auto& Data = *reinterpret_cast<const renoir::GlobalPixelCB*>(BufferData);
			::SetShaderValue<FRHIPixelShader*, renoir::float2>(
				CmdList, GetPixelShader(), GlobalPixelCB_ViewportSize, Data.ViewportSize);
			break;
		}
		case renoir::CBType::CB_StandardPrimitivePixel:
		{
			auto& Data = *reinterpret_cast<const renoir::StandardPrimitivePixel*>(BufferData);
			::SetShaderValue<FRHIPixelShader*, int>(
				CmdList, GetPixelShader(), StandardPrimitivePixel_ShaderType, Data.ShaderType);
			break;
		}
		case renoir::CBType::CB_StandardPrimitiveAdditionalPixel:
		{
			auto& Data = *reinterpret_cast<const renoir::StandardPrimitiveAdditionalPixel*>(BufferData);
			::SetShaderValue<FRHIPixelShader*, renoir::float4>(
				CmdList, GetPixelShader(), StandardPrimitiveAdditionalPixel_PrimProps0, Data.PrimProps0);
			::SetShaderValue<FRHIPixelShader*, renoir::float4>(
				CmdList, GetPixelShader(), StandardPrimitiveAdditionalPixel_PrimProps1, Data.PrimProps1);
			break;
		}
		case renoir::CBType::CB_RenoirShaderPS:
		{
			auto& Data = *reinterpret_cast<const renoir::RenoirShaderPS*>(BufferData);
			::SetShaderValue<FRHIPixelShader*, renoir::float4>(
				CmdList, GetPixelShader(), RenoirShaderPS_GradientStartColor, Data.Prop0);
			::SetShaderValue<FRHIPixelShader*, renoir::float4>(
				CmdList, GetPixelShader(), RenoirShaderPS_GradientMidColor, Data.Prop1);
			::SetShaderValue<FRHIPixelShader*, renoir::float4>(
				CmdList, GetPixelShader(), RenoirShaderPS_GradientEndColor, Data.Prop2);
			// Data.Prop3 is renoir::float4 but GradientYCoord is defined as float in the shader
			::SetShaderValue<FRHIPixelShader*, float>(
				CmdList, GetPixelShader(), RenoirShaderPS_GradientYCoord, Data.Prop3.x);
			break;
		}
		case renoir::CBType::CB_EffectsPixel:
		{
			// Note - We use SetShaderValueArray here!
			auto& Data = *reinterpret_cast<const renoir::EffectsPixelCB*>(BufferData);
			auto CoefficientsNum = sizeof(Data.Coefficients) / sizeof(float);
			::SetShaderValueArray<FRHIPixelShader*, float>(
				CmdList, GetPixelShader(), EffectsPixelCB_Coefficients, Data.Coefficients, CoefficientsNum);
			auto PixelOffsetsNum = sizeof(Data.PixelOffsets) / sizeof(renoir::float2);
			::SetShaderValueArray<FRHIPixelShader*, renoir::float2>(
				CmdList, GetPixelShader(), EffectsPixelCB_PixelOffsets, Data.PixelOffsets, PixelOffsetsNum);
			break;
		}
		case renoir::CBType::CB_Transforms: // Fall through
		case renoir::CBType::CB_RenoirShaderVS:
			check(false && "VS buffer used in a PS!");
			break;
		default:
			check(false && "Unknown constant buffer type!");
		}
	}

	bool FCohShaderPS::Serialize(FArchive& Ar)
	{
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << GlobalPixelCB_ViewportSize
			<< StandardPrimitivePixel_ShaderType
			<< StandardPrimitiveAdditionalPixel_PrimProps0
			<< StandardPrimitiveAdditionalPixel_PrimProps1
			<< RenoirShaderPS_GradientStartColor
			<< RenoirShaderPS_GradientMidColor
			<< RenoirShaderPS_GradientEndColor
			<< RenoirShaderPS_GradientYCoord
			<< EffectsPixelCB_Coefficients
			<< EffectsPixelCB_PixelOffsets
			<< TextureBuffer[0]
			<< TextureBuffer[1]
			<< TextureBuffer[2]
			<< TextureBuffer[3]
			<< SamplerState[0]
			<< SamplerState[1]
			<< SamplerState[2]
			<< SamplerState[3];
		return bShaderHasOutdatedParameters;
	}
}