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

#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "RHIStaticStates.h"

#if WITH_EDITOR
// Editor Atlas building shaders
// Must be defined in a module which has a loading phase <= PostConfigInit
class FAtlasBuildingVS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FAtlasBuildingVS, Global, COHTMLPLUGIN_API);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	FAtlasBuildingVS() {}

public:
	FAtlasBuildingVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
	}
};

class FAtlasBuildingPS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FAtlasBuildingPS, Global, COHTMLPLUGIN_API);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	FAtlasBuildingPS() {}

public:
	FShaderResourceParameter SourceTexture;
	FShaderResourceParameter SourceTextureSampler;
	FShaderParameter DoGammaCorrection;

	FAtlasBuildingPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		SourceTexture.Bind(Initializer.ParameterMap, TEXT("PSInput0"));
		SourceTextureSampler.Bind(Initializer.ParameterMap, TEXT("PSInput0Sampler"));
		DoGammaCorrection.Bind(Initializer.ParameterMap, TEXT("DoGammaCorrection"));
	}

	void SetSourceTexture(FRHICommandList& RHICmdList, FTextureRHIRef Texture)
	{
		if (SourceTexture.IsBound())
		{
			FRHIPixelShader* ShaderRHI = GetPixelShader();

			SetTextureParameter(
				RHICmdList,
				ShaderRHI,
				SourceTexture,
				SourceTextureSampler,
				TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(),
				Texture);
		}
	}

	void SetDoGammaCorrection(FRHICommandList& RHICmdList, float DoGammaCorrectionParam)
	{
		if (DoGammaCorrection.IsBound())
		{
			FRHIPixelShader* ShaderRHI = GetPixelShader();

			::SetShaderValue<FRHIPixelShader*, float>(
				RHICmdList, ShaderRHI, DoGammaCorrection, DoGammaCorrectionParam);
		}
	}

	// FShader interface.
	virtual bool Serialize(FArchive& Ar) override
	{
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << SourceTexture << SourceTextureSampler << DoGammaCorrection;
		return bShaderHasOutdatedParameters;
	}
};
#endif
