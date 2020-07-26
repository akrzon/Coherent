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

#include <RenoirBackend/CommonTypes.h>
#include <RenoirBackend/Textures.h>
#include <RenoirBackend/PipelineState.h>

namespace renoir
{
inline FColor ToUnrealColor(renoir::Color Color)
{
	return FColor(Color.r, // R
		Color.g,  // G
		Color.b, // B
		Color.a  // A
		);
}

inline FLinearColor ToUnrealLinearColor(renoir::Color Color)
{
	const float OneOver255 = 1 / 255.f;
	return FLinearColor(Color.r * OneOver255, // R
		Color.g * OneOver255,  // G
		Color.b * OneOver255, // B
		Color.a * OneOver255   // A
		);
}

inline EPixelFormat ToUnrealTextureFormat(renoir::PixelFormat Format)
{
	switch (Format)
	{
	case renoir::PF_A8:
#if PLATFORM_XBOXONE
		// G8 is actually R8, see the comment above its definition.
		return EPixelFormat::PF_G8;
#else
		return EPixelFormat::PF_A8;
#endif
	case renoir::PF_R8G8B8A8:
		return EPixelFormat::PF_R8G8B8A8;
	case renoir::PF_BC1:
		return EPixelFormat::PF_DXT1;
	case renoir::PF_BC2:
		return EPixelFormat::PF_DXT3;
	case renoir::PF_BC3:
		return EPixelFormat::PF_DXT5;
	case renoir::PF_BC4:
		return EPixelFormat::PF_BC4;
	case renoir::PF_BC5:
		return EPixelFormat::PF_BC5;
	case renoir::PF_BC6:
		return EPixelFormat::PF_BC6H;
	case renoir::PF_BC7:
		return EPixelFormat::PF_BC7;
	default:
		check(false && "Unknown pixel format!");
		return EPixelFormat::PF_Unknown;
	}
}

inline renoir::PixelFormat FromUnrealTextureFormat(EPixelFormat Format)
{
	switch (Format)
	{
	case EPixelFormat::PF_A8:
		return renoir::PF_A8;
	// UE4 uses G8 for grayscale images (by compressing the image to single channel texture).
	// ToDo: Uncomment when renoir supports this type of compression
	// case EPixelFormat::PF_G8:
	//	return renoir::PF_G8;
	case EPixelFormat::PF_R8G8B8A8: // Fall-through
	// UE4 uses BRGA for pngs while loading, yet converts them to RGBA on the rendering thread
	// So map BRGA to RGBA
	case EPixelFormat::PF_B8G8R8A8:
		return renoir::PF_R8G8B8A8;
	case EPixelFormat::PF_DXT1:
		return renoir::PF_BC1;
	case EPixelFormat::PF_DXT3:
		return renoir::PF_BC2;
	case EPixelFormat::PF_DXT5:
		return renoir::PF_BC3;
	case EPixelFormat::PF_BC4:
		return renoir::PF_BC4;
	case EPixelFormat::PF_BC5:
		return renoir::PF_BC5;
	case EPixelFormat::PF_ETC2_RGB:
		return renoir::PF_RGB8_ETC2;
	case EPixelFormat::PF_ETC2_RGBA:
		return renoir::PF_RGBA8_ETC2_EAC;
	case EPixelFormat::PF_ASTC_4x4:
		return renoir::PF_ASTC_RGBA_4x4;
	case EPixelFormat::PF_ASTC_6x6:
		return renoir::PF_ASTC_RGBA_6x6;
	case EPixelFormat::PF_ASTC_8x8:
		return renoir::PF_ASTC_RGBA_8x8;
	case EPixelFormat::PF_ASTC_10x10:
		return renoir::PF_ASTC_RGBA_10x10;
	case EPixelFormat::PF_ASTC_12x12:
		return renoir::PF_ASTC_RGBA_12x12;
	default:
		//Unknown pixel format! Handled in function Caller
		return renoir::PF_USER_FORMAT;
	}
}

inline ESamplerAddressMode ToUnrealSamplerAddressMode(renoir::SamplerAddressing AddressMode)
{
	switch (AddressMode)
	{
	case renoir::SAMA_Wrap:
		return ESamplerAddressMode::AM_Wrap;
	case renoir::SAMA_Mirror:
		return ESamplerAddressMode::AM_Mirror;
	case renoir::SAMA_Clamp:
		return ESamplerAddressMode::AM_Clamp;
	}
	check(false && "Unrecognized sampler address mode!");
	return (ESamplerAddressMode)0;
}

inline ESamplerFilter ToUnrealSamplerFilter(renoir::SamplerFilter Filter)
{
	switch (Filter)
	{
	case renoir::SAMF_Point:
		return ESamplerFilter::SF_Point;
	case renoir::SAMF_Linear:
		return ESamplerFilter::SF_Bilinear;
	case renoir::SAMF_Trilinear:
		return ESamplerFilter::SF_Trilinear;
	}
	check(false && "Unrecognized sampler filter mode!");
	return (ESamplerFilter)0;
}

inline EBlendOperation ToUnrealBlendOp(renoir::BlendingOp Operation)
{
	switch (Operation)
	{
	case renoir::BLOP_Add:
		return EBlendOperation::BO_Add;
	case renoir::BLOP_Subtract:
		return EBlendOperation::BO_Subtract;
	case renoir::BLOP_Min:
		return EBlendOperation::BO_Min;
	case renoir::BLOP_Max:
		return EBlendOperation::BO_Max;
	case renoir::BLOP_ReverseSubtract:
		return EBlendOperation::BO_ReverseSubtract;
	}
	check(false && "Unrecognized blend operation!");
	return (EBlendOperation)0;
}

inline EBlendFactor ToUnrealBlendFactor(renoir::BlendingCoeff Coeff)
{
	switch (Coeff)
	{
	case renoir::BC_Zero:
		return EBlendFactor::BF_Zero;
	case renoir::BC_One:
		return EBlendFactor::BF_One;
	case renoir::BC_SrcColor:
		return EBlendFactor::BF_SourceColor;
	case renoir::BC_InvSrcColor:
		return EBlendFactor::BF_InverseSourceColor;
	case renoir::BC_SrcAlpha:
		return EBlendFactor::BF_SourceAlpha;
	case renoir::BC_InvSrcAlpha:
		return EBlendFactor::BF_InverseSourceAlpha;
	case renoir::BC_DestAlpha:
		return EBlendFactor::BF_DestAlpha;
	case renoir::BC_InvDestAlpha:
		return EBlendFactor::BF_InverseDestAlpha;
	case renoir::BC_DestColor:
		return EBlendFactor::BF_DestColor;
	case renoir::BC_InvDestColor:
		return EBlendFactor::BF_InverseDestColor;
	case renoir::BC_SrcAlphaSat:
		check(false && "Unsupported blend factor");
		return (EBlendFactor)0;
	case renoir::BC_BlendFactor:
		return EBlendFactor::BF_ConstantBlendFactor;
	case renoir::BC_InvBlendFactor:
		return EBlendFactor::BF_InverseConstantBlendFactor;
	}
	check(false && "Unrecognized blend factor!");
	return (EBlendFactor)0;
}

inline ECompareFunction ToUnrealStencilCompareFunction(renoir::StencilFunc Func)
{
	switch (Func)
	{
		case renoir::STEF_Never:
			return ECompareFunction::CF_Never;
		case renoir::STEF_Less:
			return ECompareFunction::CF_Less;
		case renoir::STEF_LessEqual:
			return ECompareFunction::CF_LessEqual;
		case renoir::STEF_Greater:
			return ECompareFunction::CF_Greater;
		case renoir::STEF_GreaterEqual:
			return ECompareFunction::CF_GreaterEqual;
		case renoir::STEF_Equal:
			return ECompareFunction::CF_Equal;
		case renoir::STEF_NotEqual:
			return ECompareFunction::CF_NotEqual;
		case renoir::STEF_Always:
			return ECompareFunction::CF_Always;
	}
	check(false && "Unrecognized stencil func");
	return (ECompareFunction)0;
}

inline EStencilOp ToUnrealStencilOp(renoir::StencilOp Operation)
{
	switch (Operation)
	{
		case renoir::STEO_Keep:
			return EStencilOp::SO_Keep;
		case renoir::STEO_Zero:
			return EStencilOp::SO_Zero;
		case renoir::STEO_Replace:
			return EStencilOp::SO_Replace;
		case renoir::STEO_Increment:
			return EStencilOp::SO_SaturatedIncrement;//EStencilOp::SO_Increment;
		case renoir::STEO_Decrement:
			return EStencilOp::SO_SaturatedDecrement;// EStencilOp::SO_Decrement;
		case renoir::STEO_Invert:
			return EStencilOp::SO_Invert;
		case renoir::STEO_IncrementWrap:
			return EStencilOp::SO_Increment;
		case renoir::STEO_DecrementWrap:
			return EStencilOp::SO_Decrement;
	}
	check(false && "Unrecognized stencil operation!");
	return (EStencilOp)0;
}

}
