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

#include "RHIStaticStates.h"
#include "CoherentRenderingBackwardsCompatibility.h"

class FCohRHIClickThroughShaderVS : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FCohRHIClickThroughShaderVS, Global);
public:
	FCohRHIClickThroughShaderVS(){ }
	FCohRHIClickThroughShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) :
		FGlobalShader(Initializer)
	{

		ThresholdParam.Bind(Initializer.ParameterMap, TEXT("ThresholdParam"));
		TexCoordsParam.Bind(Initializer.ParameterMap, TEXT("TexCoordsParam"));
		TextureParam.Bind(Initializer.ParameterMap, TEXT("TextureParam"));
		TextureSamplerParam.Bind(Initializer.ParameterMap, TEXT("TextureSamplerParam"));
	}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
	static void ModifyCompilationEnvironment(EShaderPlatform Parameters, FShaderCompilerEnvironment& OutEnvironment)
#else
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
#endif
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
#if defined(COHERENT_RENDERING_UE4_416_SUPPORT)
		OutEnvironment.SetDefine(TEXT("__UE4_416_SUPPORT__"), TEXT("1"));
#endif
	}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
	static bool ShouldCache(EShaderPlatform Platform)
	{
		return IsFeatureLevelSupported(Platform, ERHIFeatureLevel::SM4);
	}
#else
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		ERHIFeatureLevel::Type FeatureLevel =
#if defined(COHERENT_RENDERING_UE4_423_SUPPORT)
			ERHIFeatureLevel::SM4;
#else
			ERHIFeatureLevel::SM5;
#endif
		return IsFeatureLevelSupported(Parameters.Platform, FeatureLevel);
	}
#endif

	void SetData(FRHICommandList* RHICmdList,
		float AlphaThreshold,
		const FVector2D& TexCoords,
		FTexture2DRHIRef Texture)
	{
		auto Shader = GetVertexShader();
		SetShaderValue(*RHICmdList, Shader, ThresholdParam, AlphaThreshold);
		SetShaderValue(*RHICmdList, Shader, TexCoordsParam, TexCoords);
		SetTextureParameter(*RHICmdList, Shader, TextureParam, TextureSamplerParam,
			TStaticSamplerState<SF_Point>::GetRHI(),
			Texture);
	}

	virtual bool Serialize(FArchive& Ar)
	{
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);

		Ar << ThresholdParam;
		Ar << TexCoordsParam;
		Ar << TextureParam;
		Ar << TextureSamplerParam;

		return bShaderHasOutdatedParameters;
	}

	FShaderParameter ThresholdParam;
	FShaderParameter TexCoordsParam;
	FShaderResourceParameter TextureParam;
	FShaderResourceParameter TextureSamplerParam;
};

class FCohRHIClickThroughShaderPS : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FCohRHIClickThroughShaderPS, Global);
public:
	FCohRHIClickThroughShaderPS(){ }
	FCohRHIClickThroughShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) :
		FGlobalShader(Initializer)
	{}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
	static void ModifyCompilationEnvironment(EShaderPlatform Parameters, FShaderCompilerEnvironment& OutEnvironment)
#else
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
#endif
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
#if defined(COHERENT_RENDERING_UE4_416_SUPPORT)
		OutEnvironment.SetDefine(TEXT("__UE4_416_SUPPORT__"), TEXT("1"));
#endif
	}

#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
	static bool ShouldCache(EShaderPlatform Platform)
	{
		return true;
	}
#else
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}
#endif
};
