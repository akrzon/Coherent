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
#include "CohRenoirBackend.h"

#include "RHIStaticStates.h"
#if !defined(COHERENT_RENDERING_UE4_415_SUPPORT)
#include "ClearQuad.h"
#include "PipelineStateCache.h"
#endif

#include "CohVertexBuffer.h"
#include "CohIndexBuffer.h"
#include "CohStencilBuffer.h"
#include "CohRenoirShaders.h"

#include "Containers/ResourceArray.h"
#include "SceneUtils.h"

#include "CohRHIClickThroughShader.h"

#if PLATFORM_IOS
// This include is only needed for the Metal scissor rect fix in RestoreDefaultState
#include "Engine/GameViewportClient.h"
#endif

using namespace CohShaders;

DECLARE_DWORD_COUNTER_STAT(TEXT("Coherent Rendering Number of Draw Calls"), STAT_CoherentRenderingCounterDrawBatches, STATGROUP_CoherentRenderingCounters);
DECLARE_DWORD_COUNTER_STAT(TEXT("Coherent Rendering Rendering Commands Count"), STAT_CoherentRenderingCounterRenderingCommands, STATGROUP_CoherentRenderingCounters);
#if !defined(COHERENT_RENDERING_UE4_413_SUPPORT)
#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
DECLARE_FLOAT_COUNTER_STAT(TEXT("Coherent Rendering"), Stat_GPU_CoherentRendering, STATGROUP_GPU);
#else
DECLARE_GPU_STAT(CoherentRendering);
#endif
#endif

DEFINE_STAT(STAT_CoherentRenderingGPUTotalMemory);
DEFINE_STAT(STAT_CoherentRenderingGPUTextureMemory);
DEFINE_STAT(STAT_CoherentRenderingGPUDepthStencilMemory);
DEFINE_STAT(STAT_CoherentRenderingGPUVertexBuffersMemory);
DEFINE_STAT(STAT_CoherentRenderingGPUIndexBuffersMemory);

namespace renoir
{
uint32 GetTypeHash(const FUE4BlendingState& State)
{
	uint32 Hash = 0;
	Hash += State.Enabled * 5;
	Hash += ((State.BlendOp << 16) | (State.SrcBlend << 8) | State.DestBlend) * 117;
	Hash += ((State.BlendOpAlpha << 16) | (State.SrcBlendAlpha << 8) | State.DestBlendAlpha) * 16567;
	Hash += State.RTColorWriteMask * 1201;

	return Hash;
}

uint32 GetTypeHash(const renoir::DepthStencilState& State)
{
	return (State.StencilEnable << 24) | (State.FailOp << 16) | (State.PassOp << 8) | State.Function;
}

}

class FCohVertexDecl : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;
	FCohRenoirBackend::VertexAttributes Attributes;
	uint32 Stride;

	FCohVertexDecl(const FCohRenoirBackend::VertexAttributes& attribs)
		: Attributes(attribs)
		, Stride(0)
	{}

	virtual ~FCohVertexDecl()
	{
		ReleaseResource();
	}

	virtual void FillDeclElements(FVertexDeclarationElementList& Elements)
	{
		int LastSize = 0;
		for (auto i = 0; i < Attributes.Num(); ++i)
		{
			int Size = 0;
			switch (Attributes[i].Type)
			{
			case VET_Float1:
				Size = sizeof(float);
				break;
			case VET_Float2:Size = 2 * sizeof(float);
				break;
			case VET_Float3:Size = 3 * sizeof(float);
				break;
			case VET_Float4:Size = 4 * sizeof(float);
				break;
			case VET_UByte4:Size = 4 * sizeof(char);
				break;
			default:
				check(false && "Add a new case for this type");
			}
			Stride += Size;
			LastSize = Size;
		}

		const auto lastId = Attributes.Num() - 1;
		check(Stride == (Attributes[lastId].Offset + LastSize));

		for (auto i = 0; i < Attributes.Num(); ++i)
		{
			const auto& Attr = Attributes[i];
			Elements.Add(FVertexElement(0, Attr.Offset, Attr.Type, i, Stride));
		}
	}

	virtual void InitRHI()
	{
		FVertexDeclarationElementList Elements;
		FillDeclElements(Elements);
		VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
	}

	virtual void ReleaseDynamicRHI()
	{
		VertexDeclarationRHI.SafeRelease();
	}
};

namespace {
template<typename ResourcePair, typename ResourceObject>
int32 IndexOfResource(const TArray<ResourcePair>& ResourceList, const ResourceObject& Object)
{
	return ResourceList.IndexOfByPredicate([Object](const ResourcePair& Pair)
	{
		return Pair.Key == Object;
	});
}

template<typename ResourcePair, typename ResourceObject>
void DestroyResourceFromList(TArray<ResourcePair>& ResourceList, const ResourceObject& Object)
{
	auto Index = IndexOfResource(ResourceList, Object);
	if (Index != INDEX_NONE)
	{
		ResourceList.RemoveAtSwap(Index);
	}
}

enum GPUMemoryChange
{
	Decrement = 0,
	Increment
};

template <typename ResourceType, typename ResourcePair, typename MemStatType>
void UpdateGPUMemory(ResourceType& Resource, TArray<ResourcePair>& ResourceList, MemStatType& MemStat, GPUMemoryChange Change)
{
	auto Index = IndexOfResource(ResourceList, Resource);
	check(Index != INDEX_NONE && TEXT("Trying to access untracked resource!"))
	auto ResFromList = &ResourceList[Index];
	auto Size = ResFromList->Value->GetMemorySize();
	if (Change == Increment)
	{
		INC_MEMORY_STAT_BY(STAT_CoherentRenderingGPUTotalMemory, Size);
		INC_MEMORY_STAT_BY_FName(MemStat.GetStatFName(), Size);
	}
	else
	{
		DEC_MEMORY_STAT_BY(STAT_CoherentRenderingGPUTotalMemory, Size);
		DEC_MEMORY_STAT_BY_FName(MemStat.GetStatFName(), Size);
	}
}

}

FCohRenoirBackend::FCohRenoirBackend()
	: CmdList(nullptr)
	, bIsScissorRectValid(true)
{
	{
		VertexAttributes StandardVertex;
		FCohVertexAttrib Position = { VET_Float4, 0 };
		FCohVertexAttrib Color = { VET_Float4, sizeof(float) * 4 };
		FCohVertexAttrib Additional = { VET_Float4, sizeof(float) * 8 };
		StandardVertex.Add(Position);
		StandardVertex.Add(Color);
		StandardVertex.Add(Additional);

		TUniquePtr<FCohVertexDecl> StandardVertexPtr(new FCohVertexDecl(StandardVertex));
		StandardVertexPtr->InitRHI();
		VertexDeclCache.Add(renoir::VT_Standard, MoveTemp(StandardVertexPtr));
	}

	{
		VertexAttributes SlimVertex;
		FCohVertexAttrib Position = { VET_Float4, 0 };
		SlimVertex.Add(Position);

		TUniquePtr<FCohVertexDecl> SlimVertexPtr(new FCohVertexDecl(SlimVertex));
		SlimVertexPtr->InitRHI();
		VertexDeclCache.Add(renoir::VT_Slim, MoveTemp(SlimVertexPtr));
	}

	TexturesToRebind.SetNum(MAX_BOUND_TEXTURES);
	SamplersToRebind.SetNum(MAX_BOUND_SAMPLERS);

	InitUniformBuffers();
	ResetTexturesToBind();
	ResetSamplersToBind();
	bShouldRebindTextures = false;
	bShouldRebindSamplers = false;
	RequestedVertexBuffer = nullptr;

	renoir::Texture2D Desc;
	Desc.Width = 1;
	Desc.Height = 1;
	DummyTexture.Reset(new FCohTexture(Desc, nullptr, 0));

	if (IsMetalPlatform(GMaxRHIShaderPlatform)
		|| IsPS4Platform(GMaxRHIShaderPlatform))
	{
		InitializeDummySampler();
	}
}

void FCohRenoirBackend::InitializeDummySampler()
{
	// The Metal and PS4 backends invalidate the texture<->sample binding
	// whenever a new shader is set. This can lead to errors when reading
	// some textures, so we bind a dummy sampler to each texture in order
	// to ensure that no undefined behavior occurs.
	FSamplerStateInitializerRHI Initializer(
	    ESamplerFilter::SF_Bilinear,
	    ESamplerAddressMode::AM_Clamp,
	    ESamplerAddressMode::AM_Clamp,
	    ESamplerAddressMode::AM_Clamp);
	Initializer.MaxAnisotropy = 1;
	DummySampler = RHICreateSamplerState(Initializer);
}

void FCohRenoirBackend::InitUniformBuffers()
{
	VertexShaderBuffersToRebind.SetNumZeroed(renoir::CBType::CB_Count);
	PixelShaderBuffersToRebind.SetNumZeroed(renoir::CBType::CB_Count);
	ResetUniformBuffersToBind();
}

FCohRenoirBackend::~FCohRenoirBackend()
{
	CurrentPipelineState = FPipelineState();
	DefaultRasterState.SafeRelease();

	VertexBuffers.Empty();
	IndexBuffers.Empty();
	DepthStencilTextureBuffers.Empty();
	RenderTargetList.Empty();
	Texture2DList.Empty();
	Sampler2DList.Empty();
	PipelineStateList.Empty();
	VertexShaderBuffersToRebind.Empty();
	PixelShaderBuffersToRebind.Empty();
	OcclusionQueryList.Empty();
	HWState = FHardwareState();
	RequestedVertexBuffer = nullptr;

	StencilCache.Empty();
	BlendCache.Empty();
	VertexDeclCache.Empty();
	VertexShaderCache.Empty();
	PixelShaderCache.Empty();
}

void FCohRenoirBackend::SetRHICmdList(FRHICommandListImmediate* list)
{
	CmdList = list;
}

void FCohRenoirBackend::RestoreDefaultState()
{
#if PLATFORM_IOS
	// If we are using Metal, then when we try to set the scissor rect, UE4 clamps it to the render target's size.
	// This is done, because Metal's SetScissorRect expect a scissor, which lies within the current render target.
	// Here we try to reset the scissor after our rendering, but the current render target is our texture and
	// it can be smaller than the backbuffer of the game.
	// This is why we need to first set the backbuffer of the game as a render target and then set the scissor.
#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
	bool bShouldEndRenderPass = false;
#endif
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport
		&& GEngine->GameViewport->Viewport->GetViewportRHI().IsValid())
	{
		FRHIViewport* ViewportRHI = GEngine->GameViewport->Viewport->GetViewportRHI().GetReference();
		FTexture2DRHIRef BackBuffer = CmdList->GetViewportBackBuffer(ViewportRHI);
		if (BackBuffer)
		{
#if defined(COHERENT_RENDERING_UE4_421_SUPPORT)
			FRHIRenderTargetView RTV(BackBuffer.GetReference(), ERenderTargetLoadAction::ENoAction);
			CmdList->SetRenderTargets(1, &RTV, nullptr, 0, nullptr);
#else
			// UE4 does not allow usage of the backbuffer here with a non-store action.
			// Load/storing every frame is slow, so we just use a dummy texture.
			FRHITexture* DummyTextureRef = DummyTexture->GetTextureRHI().GetReference();
			FRHIRenderPassInfo Info(1,
				&DummyTextureRef,
				ERenderTargetActions::Load_Store);

			CmdList->BeginRenderPass(Info, TEXT("Coherent Rendering"));
			bShouldEndRenderPass = true;
#endif
		}
		else
		{
			UE_LOG(LogCoherentRendering, Warning, TEXT("Unable to get the backbuffer of the game. This may lead to visual artifacts"));
		}
	}
	else
	{
		UE_LOG(LogCoherentRendering, Warning, TEXT("Unable to get the viewport of the game. This may lead to visual artifacts"));
	}
#endif
	CmdList->SetScissorRect(false,
		0,
		0,
		16384,
		16384);
#if defined (COHERENT_RENDERING_UE4_415_SUPPORT)
	CmdList->SetDepthStencilState(TStaticDepthStencilState<false, CF_Always>::GetRHI());
	CmdList->SetRasterizerState(TStaticRasterizerState<>::GetRHI());
#else
	// Do nothing
#endif

#if PLATFORM_IOS && !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
	if (bShouldEndRenderPass)
	{
		CmdList->EndRenderPass();
	}
#endif
}

void FCohRenoirBackend::BeginCommands()
{
	CurrentPipelineState = FPipelineState();
	HWState = FHardwareState();
	RequestedVertexBuffer = nullptr;
#if defined(COHERENT_RENDERING_UE4_411_SUPPORT)
	CmdList->PushEvent(TEXT("Coherent Renoir Begin Commands"));
#else
	CmdList->PushEvent(TEXT("Coherent Renoir Begin Commands"), FColor::Emerald);
#endif

	if (IsVulkanPlatform(GMaxRHIShaderPlatform))
	{
		CmdList->TransitionResource(EResourceTransitionAccess::EReadable, DummyTexture->GetTextureRHI().GetReference());
	}

	bShouldRebindUniformBuffers = true;

	for (auto& cb : ConstantBuffers)
	{
		cb.Value.Data = nullptr;
		cb.Value.CurrentOffset = 0;
	}

	ResetUniformBuffersToBind();
	ResetTexturesToBind();
	ResetSamplersToBind();
}

void FCohRenoirBackend::FillCaps(renoir::RendererCaps& outCaps)
{
	using namespace renoir;
	FMemory::Memset(&outCaps, 0, sizeof(renoir::RendererCaps));

	// Copied from DX11 backend
	outCaps.SupportsMSAATextures = true;
	outCaps.RequiresMSAAResolve = true;
	outCaps.SupportsA8RenderTarget = true;
	outCaps.RequiresRBSwapForImages = false;
	outCaps.RequiresDrawFences = false;
	outCaps.RequiresShaderTypeInShader = true;
	outCaps.RequiresYFlipForLayers = false;
	outCaps.SupportsNPOTTextureOps = true;
	outCaps.ShaderChangeRequiresResourcesRebind = true;
	outCaps.SupportsOnly16bitIndices = false;
#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
	outCaps.ShouldUseRenderPasses = true;
#else
	outCaps.ShouldUseRenderPasses = false;
#endif
	outCaps.ShouldClearRTWithClearQuad = true;
#if PLATFORM_ANDROID || PLATFORM_IOS
	outCaps.PreferCPUWorkload = true;
#else
	outCaps.PreferCPUWorkload = false;
#endif
	outCaps.ConstantBufferRingSize = 1;
	outCaps.ConstantBufferBlocksCount = 1;
	outCaps.ConstantBufferBlockAlignment = 1;
	outCaps.ShaderMapping[ST_Standard] = ST_Standard;
	outCaps.ShaderMapping[ST_StandardCircle] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StandardStrokeCircle] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StandardEllipse] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StandardStrokeEllipse] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StandardRRect] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StandardStrokeRRect] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StandardTexture] = ST_Standard;
	outCaps.ShaderMapping[ST_Path] = ST_Path;
	outCaps.ShaderMapping[ST_HairlinePath] = ST_Path;
	outCaps.ShaderMapping[ST_Hairline] = ST_StandardRare;
	outCaps.ShaderMapping[ST_Stencil] = ST_Stencil;
	outCaps.ShaderMapping[ST_StencilRRect] = ST_StencilRare;
	outCaps.ShaderMapping[ST_StencilCircle] = ST_StencilRare;
	outCaps.ShaderMapping[ST_StencilTexture] = ST_Stencil;
	outCaps.ShaderMapping[ST_StencilPath] = ST_StencilPath;
	outCaps.ShaderMapping[ST_Text] = ST_Standard;
	outCaps.ShaderMapping[ST_TextSDF] = ST_Standard;
	outCaps.ShaderMapping[ST_TextStrokeSDF] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StencilAnimatedPathBezier] = ST_StencilPath;
	outCaps.ShaderMapping[ST_StencilAnimatedPathTriangle] = ST_StencilPath;
	outCaps.ShaderMapping[ST_BatchedStandard] = ST_BatchedStandard;
	outCaps.ShaderMapping[ST_BatchedStandardTexture] = ST_BatchedStandard;
	outCaps.ShaderMapping[ST_BatchedText] = ST_BatchedStandard;
	outCaps.ShaderMapping[ST_BatchedTextSDF] = ST_BatchedStandard;

	for (auto blur = int(ST_Blur_1); blur <= int(ST_Blur_12); ++blur)
	{
		outCaps.ShaderMapping[ShaderType(blur)] = ST_StandardRare;
	}

	outCaps.ShaderMapping[ST_StandardRare] = ST_StandardRare;
	outCaps.ShaderMapping[ST_StencilRare] = ST_StencilRare;
	outCaps.ShaderMapping[ST_ClearQuad] = ST_ClearQuad;

	outCaps.ShaderMapping[ST_RenoirShader] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_LinearGradient2Point] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_LinearGradient3PointSymmetrical] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_LinearGradientFromTexture] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_RadialGradient2Point] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_RadialGradient3PointSymmetrical] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_RadialGradientFromTexture] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_LinearGradientMasked2Point] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_LinearGradientMasked3PointSymmetrical] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_LinearGradientMaskedFromTexture] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_RadialGradientMasked2Point] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_RadialGradientMasked3PointSymmetrical] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_RadialGradientMaskedFromTexture] = ST_RenoirShader;

	outCaps.ShaderMapping[ST_SimpleTexture] = ST_RenoirShader;
	outCaps.ShaderMapping[ST_SimpleTextureMasked] = ST_RenoirShader;

	outCaps.ShaderMapping[ST_StandardTextureWithColorMatrix] = ST_StandardRare;

	outCaps.ShaderMapping[ST_TexturesWithColorMix] = ST_TexturesWithColorMix;

	outCaps.ShaderMapping[ST_YUV2RGB] = ST_StandardRare;
	outCaps.ShaderMapping[ST_YUVA2RGB] = ST_StandardRare;
}

void FCohRenoirBackend::WrapUserRenderTarget(void* UserObject,
	const renoir::Texture2D& Description,
	renoir::Texture2DObject Object,
	void* DepthStencil,
	const renoir::DepthStencilTexture& DSDescription,
	renoir::DepthStencilTextureObject DSObject)
{
	FRenoirRenderTarget RenderTarget;
	RenderTarget.Texture = (FRHITexture2D*)UserObject;
	RenderTarget.DepthStencilTexture = (FCohStencilBuffer*)DepthStencil;
	RenderTarget.Description = Description;

	RenderTargetList.Add(TPairInitializer<renoir::Texture2DObject, FRenoirRenderTarget>(Object, RenderTarget));
}

void FCohRenoirBackend::WrapUserTexture(void* UserObject,
	const renoir::Texture2D& Description,
	renoir::Texture2DObject Object)
{
	auto WrapData = (FCohTextureUserWrapData*)UserObject;
	auto Texture = new FCohTexture(*WrapData);
	Texture->LiveViewUrl = WrapData->LiveViewUrl;
	delete WrapData;
	Texture2DList.Add(TPairInitializer<renoir::Texture2DObject, FCohTexture*>(Object, Texture));
	if (!Texture->LiveViewUrl.IsEmpty() && OnLiveViewReachedBackend.IsBound())
	{
		OnLiveViewReachedBackend.Execute(Texture->LiveViewUrl);
	}
}

bool FCohRenoirBackend::CreatePipelineState(const renoir::PipelineState& State, renoir::PipelineStateObject Object)
{
	static_assert(static_cast<int>(renoir::ColorWriteMask::CWM_All) == static_cast<int>(EColorWriteMask::CW_RGBA)
		&& static_cast<int>(renoir::ColorWriteMask::CWM_None) == static_cast<int>(EColorWriteMask::CW_NONE),
		"Renoir ColorWriteMask values do not match UE4 EColorWriteMask values");

	FUE4BlendingState blendingUE4(State.Blending, State.ColorMask);

	auto BlendState = BlendCache.Find(blendingUE4);
	if (BlendState == nullptr)
	{
		FBlendStateInitializerRHI Initializer;
		FBlendStateInitializerRHI::FRenderTarget RenderTargetBlendState;
		RenderTargetBlendState.AlphaBlendOp = ToUnrealBlendOp(State.Blending.BlendOpAlpha);
		RenderTargetBlendState.AlphaDestBlend = ToUnrealBlendFactor(State.Blending.DestBlendAlpha);
		RenderTargetBlendState.AlphaSrcBlend = ToUnrealBlendFactor(State.Blending.SrcBlendAlpha);
		RenderTargetBlendState.ColorBlendOp = ToUnrealBlendOp(State.Blending.BlendOp);
		RenderTargetBlendState.ColorDestBlend = ToUnrealBlendFactor(State.Blending.DestBlend);
		RenderTargetBlendState.ColorSrcBlend = ToUnrealBlendFactor(State.Blending.SrcBlend);
		assert(State.ColorMask == renoir::ColorWriteMask::CWM_None || State.ColorMask == renoir::ColorWriteMask::CWM_All);
		RenderTargetBlendState.ColorWriteMask = EColorWriteMask(State.ColorMask);

#if PLATFORM_ANDROID
		// Artificially changed the blend mode so it ends up with the same result, but fixes bug in OpenGL renderer on Android
		// Snapdragon devices where if a call to glBlendFuncSeparate is invoked, glBlendFunc after that doesn't overwrite the alpha
		if (RenderTargetBlendState.AlphaDestBlend == RenderTargetBlendState.ColorDestBlend &&
			RenderTargetBlendState.AlphaSrcBlend == RenderTargetBlendState.ColorSrcBlend &&
			RenderTargetBlendState.AlphaSrcBlend.GetValue() == EBlendFactor::BF_One &&
			RenderTargetBlendState.AlphaDestBlend.GetValue() == EBlendFactor::BF_InverseSourceAlpha)
		{
			RenderTargetBlendState.AlphaDestBlend = EBlendFactor::BF_One;
			RenderTargetBlendState.AlphaSrcBlend = EBlendFactor::BF_InverseDestAlpha;
		}
#endif

		Initializer.RenderTargets[0] = RenderTargetBlendState;
		Initializer.bUseIndependentRenderTargetBlendStates = false;
		BlendCache.Add(blendingUE4, RHICreateBlendState(Initializer));
	}
	auto DepthStencilState = StencilCache.Find(State.DepthStencil);
	if (DepthStencilState == nullptr)
	{
		// Values are below are the same as in the DX11 backend, only the roles of the backface and the frontface are swapped
		FDepthStencilStateInitializerRHI Initializer;
		Initializer.DepthTest = ECompareFunction::CF_Always;
		Initializer.bEnableDepthWrite = false;

		Initializer.StencilReadMask = 0xFF;
		Initializer.StencilWriteMask = 0xFF;

		Initializer.bEnableBackFaceStencil = State.DepthStencil.StencilEnable;
		Initializer.BackFaceStencilFailStencilOp = ToUnrealStencilOp(State.DepthStencil.FailOp);
		Initializer.BackFacePassStencilOp = ToUnrealStencilOp(State.DepthStencil.PassOp);
		Initializer.BackFaceDepthFailStencilOp = EStencilOp::SO_Keep;
		Initializer.BackFaceStencilTest = ToUnrealStencilCompareFunction(State.DepthStencil.Function);

		Initializer.bEnableFrontFaceStencil = State.DepthStencil.StencilEnable;
		Initializer.FrontFaceStencilFailStencilOp = ToUnrealStencilOp(State.DepthStencil.FailOp);
		Initializer.FrontFacePassStencilOp = ToUnrealStencilOp(State.DepthStencil.PassOp);
		Initializer.FrontFaceDepthFailStencilOp = EStencilOp::SO_Keep;
		Initializer.FrontFaceStencilTest = ToUnrealStencilCompareFunction(State.DepthStencil.Function);

		StencilCache.Add(State.DepthStencil, RHICreateDepthStencilState(Initializer));
	}
	if (DefaultRasterState == nullptr)
	{
		FRasterizerStateInitializerRHI Initializer;
		Initializer.FillMode = ERasterizerFillMode::FM_Solid;
		Initializer.CullMode = ERasterizerCullMode::CM_None;
		Initializer.DepthBias = 0;
		Initializer.SlopeScaleDepthBias = 0;
		Initializer.bAllowMSAA = State.MSAASamples > 1;
		Initializer.bEnableLineAA = false;
		DefaultRasterState = RHICreateRasterizerState(Initializer);
	}
	auto VertexShaderRef = VertexShaderCache.Find(State.VertexShader);
	if (VertexShaderRef == nullptr)
	{
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		auto GlobalMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel), false);
#else
		auto GlobalMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel));
#endif
		CohShaders::FCohShaderVS* VertexShader = nullptr;
		switch (State.VertexShader)
		{
		case renoir::ST_Standard:
			VertexShader = *TShaderMapRef<FRenoirStandardVS>(GlobalMap);
			break;
		case renoir::ST_BatchedStandard:
			VertexShader = *TShaderMapRef<FRenoirStandardBatchedVS>(GlobalMap);
			break;
		case renoir::ST_StandardRare:
		case renoir::ST_Stencil:
		case renoir::ST_StencilRare:
		case renoir::ST_TexturesWithColorMix:
			VertexShader = *TShaderMapRef<FRenoirStandardRareVS>(GlobalMap);
			break;
		case renoir::ST_Path:
		case renoir::ST_StencilPath:
			VertexShader = *TShaderMapRef<FRenoirPathVS>(GlobalMap);
			break;
		case renoir::ST_RenoirShader:
			VertexShader = *TShaderMapRef<FRenoirVS>(GlobalMap);
			break;
		case renoir::ST_ClearQuad:
			VertexShader = *TShaderMapRef<FRenoirClearQuadVS>(GlobalMap);
			break;
		default:
			check(false && "Not implemented!");
		}
		VertexShaderCache.Add(State.VertexShader, VertexShader);
	}
	auto PixelShaderRef = PixelShaderCache.Find(State.PixelShader);
	if (PixelShaderRef == nullptr)
	{
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		auto GlobalMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel), false);
#else
		auto GlobalMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel));
#endif
		CohShaders::FCohShaderPS* PixelShader = nullptr;
		switch (State.PixelShader)
		{
		case renoir::ST_Standard:
			PixelShader = *TShaderMapRef<FRenoirStandardPS>(GlobalMap);
			break;
		case renoir::ST_BatchedStandard:
			PixelShader = *TShaderMapRef<FRenoirStandardBatchedPS>(GlobalMap);
			break;
		case renoir::ST_StandardRare:
			PixelShader = *TShaderMapRef<FRenoirStandardRarePS>(GlobalMap);
			break;
		case renoir::ST_Path:
			PixelShader = *TShaderMapRef<FRenoirPathPS>(GlobalMap);
			break;
		case renoir::ST_Stencil:
			PixelShader = *TShaderMapRef<FRenoirStencilPS>(GlobalMap);
			break;
		case renoir::ST_StencilRare:
			PixelShader = *TShaderMapRef<FRenoirStencilRarePS>(GlobalMap);
			break;
		case renoir::ST_StencilPath:
			PixelShader = *TShaderMapRef<FRenoirStencilPathPS>(GlobalMap);
			break;
		case renoir::ST_RenoirShader:
			PixelShader = *TShaderMapRef<FRenoirPS>(GlobalMap);
			break;
		case renoir::ST_TexturesWithColorMix:
			PixelShader = *TShaderMapRef<FTexturesWithColorMixPS>(GlobalMap);
			break;
		case renoir::ST_ClearQuad:
			PixelShader = *TShaderMapRef<FRenoirClearQuadPS>(GlobalMap);
			break;
		default:
			check(false && "Not implemented!");
		}
		PixelShaderCache.Add(State.PixelShader, PixelShader);
	}
	PipelineStateList.Add(TPairInitializer<renoir::PipelineStateObject, renoir::PipelineState>(Object, State));
	return true;
}
void FCohRenoirBackend::DestroyPipelineState(renoir::PipelineStateObject Object)
{
	DestroyResourceFromList(PipelineStateList, Object);
}

bool FCohRenoirBackend::CreateVertexBuffer(renoir::VertexType Type, unsigned Count, renoir::VertexBufferObject Object, bool ChangesOften)
{
	if (Type != renoir::VT_Standard
		&& Type != renoir::VT_Slim)
	{
		check(false && "Unable to use unsupported vertex declaration!");
		return false;
	}
	auto VB = new FCohVertexBuffer(Count, ChangesOften, Type);

	VertexBuffers.Add(TPairInitializer<renoir::VertexBufferObject, FCohVertexBuffer*>(Object, VB));
#if !UE_BUILD_SHIPPING && STATS
	UpdateGPUMemory(Object, VertexBuffers, GET_STAT_OBJECT(STAT_CoherentRenderingGPUVertexBuffersMemory), Increment);
#endif
	return true;
}

void FCohRenoirBackend::DestroyVertexBuffer(renoir::VertexBufferObject Object)
{
#if !UE_BUILD_SHIPPING && STATS
	UpdateGPUMemory(Object, VertexBuffers, GET_STAT_OBJECT(STAT_CoherentRenderingGPUVertexBuffersMemory), Decrement);
#endif
	DestroyResourceFromList(VertexBuffers, Object);
}

void* FCohRenoirBackend::MapVertexBuffer(renoir::VertexBufferObject Object)
{
	auto Index = IndexOfResource(VertexBuffers, Object);
	if (Index != INDEX_NONE)
	{
		auto& Buffer = VertexBuffers[Index].Value;
		return Buffer->Lock();
	}
	else
	{
		check(false && "Unable to map an unknown vertex buffer");
		return nullptr;
	}
}
void FCohRenoirBackend::UnmapVertexBuffer(renoir::VertexBufferObject Object, unsigned /* ElementCount */)
{
	auto Index = IndexOfResource(VertexBuffers, Object);
	if (Index != INDEX_NONE)
	{
		auto& Buffer = VertexBuffers[Index].Value;
		Buffer->Unlock();
	}
	else
	{
		check(false && "Unable to map an unknown vertex buffer");
	}
}

bool FCohRenoirBackend::CreateIndexBuffer(renoir::IndexBufferType Format, unsigned Count, renoir::IndexBufferObject Object, bool ChangesOften)
{
	auto IB = new FCohIndexBuffer(renoir::IndexType2BytesCount(Format), Count, ChangesOften);
	IndexBuffers.Add(TPairInitializer<renoir::IndexBufferObject, FCohIndexBuffer*>(Object, IB));
#if !UE_BUILD_SHIPPING && STATS
	UpdateGPUMemory(Object, IndexBuffers, GET_STAT_OBJECT(STAT_CoherentRenderingGPUIndexBuffersMemory), Increment);
#endif
	return true;
}

void FCohRenoirBackend::DestroyIndexBuffer(renoir::IndexBufferObject Object)
{
#if !UE_BUILD_SHIPPING && STATS
	UpdateGPUMemory(Object, IndexBuffers, GET_STAT_OBJECT(STAT_CoherentRenderingGPUIndexBuffersMemory), Decrement);
#endif
	DestroyResourceFromList(IndexBuffers, Object);
}

void* FCohRenoirBackend::MapIndexBuffer(renoir::IndexBufferObject Object)
{
	auto Index = IndexOfResource(IndexBuffers, Object);
	if (Index != INDEX_NONE)
	{
		auto& Buffer = IndexBuffers[Index].Value;
		return Buffer->Lock();
	}
	else
	{
		check(false && "Unable to map an unknown vertex buffer");
		return nullptr;
	}
}

void FCohRenoirBackend::UnmapIndexBuffer(renoir::IndexBufferObject Object, unsigned /* ElementCount */)
{
	auto Index = IndexOfResource(IndexBuffers, Object);
	if (Index != INDEX_NONE)
	{
		auto& Buffer = IndexBuffers[Index].Value;
		Buffer->Unlock();
	}
	else
	{
		check(false && "Unable to map an unknown vertex buffer");
	}
}

bool FCohRenoirBackend::CreateConstantBuffer(renoir::CBType Type, renoir::ConstantBufferObject Object, unsigned)
{
	FConstantBuffer BufferData;
	BufferData.Type = Type;
	BufferData.Data = nullptr;
	BufferData.CurrentOffset = 0;
	ConstantBuffers.Add(TPairInitializer<renoir::ConstantBufferObject, FConstantBuffer>(Object, BufferData));
	return true;
}

void FCohRenoirBackend::DestroyConstantBuffer(renoir::ConstantBufferObject Object)
{
	DestroyResourceFromList(ConstantBuffers, Object);
}

bool FCohRenoirBackend::CreateTexture(renoir::Texture2DObject Object, const renoir::Texture2D& Description, const void* Data, unsigned DataLen)
{
	auto Texture = new FCohTexture(Description, Data, DataLen);
	Texture2DList.Add(TPairInitializer<renoir::Texture2DObject, FCohTexture*>(Object, Texture));
#if !UE_BUILD_SHIPPING && STATS
	UpdateGPUMemory(Object, Texture2DList, GET_STAT_OBJECT(STAT_CoherentRenderingGPUTextureMemory), Increment);
#endif
	return true;
}
void FCohRenoirBackend::DestroyTexture(renoir::Texture2DObject Texture)
{
	if (IndexOfResource(RenderTargetList, Texture) != INDEX_NONE)
	{
		DestroyResourceFromList(RenderTargetList, Texture);
	}
	else
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateGPUMemory(Texture, Texture2DList, GET_STAT_OBJECT(STAT_CoherentRenderingGPUTextureMemory), Decrement);
#endif
		// If this texture is a live view, notify the rest of the plugin to stop updating it
		auto TextureIdx = IndexOfResource(Texture2DList, Texture);
		auto& TexturePtr = Texture2DList[TextureIdx];
		if (!TexturePtr.Value->LiveViewUrl.IsEmpty() && OnLiveViewTextureDestroyed.IsBound())
		{
			OnLiveViewTextureDestroyed.Execute(TexturePtr.Value->LiveViewUrl);
		}
		DestroyResourceFromList(Texture2DList, Texture);
	}
}

void FCohRenoirBackend::UpdateTexture(renoir::Texture2DObject Object,
	const renoir::Texture2D& Description, renoir::UpdateBox* Boxes, const void** NewBytes, unsigned Count, bool WillOverwrite)
{
	auto Index = IndexOfResource(Texture2DList, Object);
	if (Index != INDEX_NONE)
	{
		auto Texture = Texture2DList[Index].Value.Get();
		Texture->Update(Description, Boxes, NewBytes, Count, WillOverwrite);
	}
	else
	{
		verify(false && "No texture found!");
	}
}

bool FCohRenoirBackend::CreateDepthStencilTexture(renoir::DepthStencilTextureObject Object, const renoir::DepthStencilTexture& Description)
{
	auto StencilBuffer = new FCohStencilBuffer(Description.Width,
		Description.Height,
		Description.SamplesCount);
	DepthStencilTextureBuffers.Add(TPairInitializer<renoir::DepthStencilTextureObject, FCohStencilBuffer*>(Object, StencilBuffer));
#if !UE_BUILD_SHIPPING && STATS
	UpdateGPUMemory(Object, DepthStencilTextureBuffers, GET_STAT_OBJECT(STAT_CoherentRenderingGPUDepthStencilMemory), Increment);
#endif
	return true;
}
void FCohRenoirBackend::DestroyDepthStencilTexture(renoir::DepthStencilTextureObject Object)
{
	if (IndexOfResource(DepthStencilTextureBuffers, Object) != INDEX_NONE)
	{
#if !UE_BUILD_SHIPPING && STATS
		UpdateGPUMemory(Object, DepthStencilTextureBuffers, GET_STAT_OBJECT(STAT_CoherentRenderingGPUDepthStencilMemory), Decrement);
#endif
		DestroyResourceFromList(DepthStencilTextureBuffers, Object);
	}
}

bool FCohRenoirBackend::CreateSampler2D(renoir::Sampler2DObject Object, const renoir::Sampler2D& Description)
{
	FSamplerStateInitializerRHI Initializer(
		ToUnrealSamplerFilter(Description.Filtering),
		ToUnrealSamplerAddressMode(Description.UAddress),
		ToUnrealSamplerAddressMode(Description.VAddress),
		ESamplerAddressMode::AM_Clamp);
	// Note: If this is not 1 UE will use ANISOTROPIC instead of D3D11_FILTER_MIN_MAG_MIP_LINEAR / D3D11_FILTER_MIN_MAG_MIP_POINT
	// See FD3D11DynamicRHI::RHICreateSamplerState
	Initializer.MaxAnisotropy = 1;
	Sampler2DList.Add(TPairInitializer<renoir::Sampler2DObject, FSamplerStateRHIRef>(Object, RHICreateSamplerState(Initializer)));
	return true;
}
void FCohRenoirBackend::DestroySampler2D(renoir::Sampler2DObject Sampler)
{
	DestroyResourceFromList(Sampler2DList, Sampler);
}

void FCohRenoirBackend::SetDebugName(renoir::Texture2DObject Texture, const char* Name)
{
	auto Index = IndexOfResource(Texture2DList, Texture);
	if (Index == INDEX_NONE)
	{
		check(false && "No texture found!");
		return;
	}

	FString TextureName(Name);
	auto CohTexture = Texture2DList[Index].Value.Get();
	if (CohTexture->IsRenderTarget() && CohTexture->GetRenderTargetRHI())
	{
		CmdList->BindDebugLabelName(CohTexture->GetRenderTargetRHI(), *TextureName);
	}
	else if (CohTexture->GetTextureRHI())
	{
		CmdList->BindDebugLabelName(CohTexture->GetTextureRHI(), *TextureName);
	}
}

void FCohRenoirBackend::SetDebugName(renoir::DepthStencilTextureObject DS, const char* Name)
{
	auto Index = IndexOfResource(DepthStencilTextureBuffers, DS);
	if (Index == INDEX_NONE)
	{
		check(false && "No depth-stencil found!");
		return;
	}

	FString dsName(Name);
	auto dsBuffer = DepthStencilTextureBuffers[Index].Value.Get();
	if (dsBuffer->GetStencilTexture())
	{
		CmdList->BindDebugLabelName(dsBuffer->GetStencilTexture(), *dsName);
	}
}

bool FCohRenoirBackend::ReadTexture(renoir::TextureObject Source, const renoir::UpdateBox& ReadBox, void* Data)
{
	verify(Source.Type == renoir::TextureObject::TT_2D);
	auto Index = IndexOfResource(Texture2DList, renoir::Texture2DObject{ Source.Id });
	if (Index == INDEX_NONE)
	{
		check(false && "No texture found!");
		return false;
	}

	auto Texture = Texture2DList[Index].Value.Get();
	auto& Description = Texture->GetRenoirDescription();
	if (ReadBox.Top != 0
		|| ReadBox.Left != 0
		|| ReadBox.Right != Description.Width
		|| ReadBox.Bottom != Description.Height)
	{
		check(false && "Cannot read sub image!");
		return false;
	}

	auto TexRHI = Texture->GetTextureRHI();
	uint32 Stride;
	auto TextureData = GDynamicRHI->RHILockTexture2D(TexRHI, 0, RLM_ReadOnly, Stride, false);
	if (!TextureData)
	{
		check(false && "Cannot Lock texture 2d");
		return false;
	}

	size_t DstRowPitch = 0u;
	size_t DstRowCount = 0u;
	renoir::GetTexture2DSizes(Description.Width, Description.Height, Description.Format, nullptr, &DstRowPitch, &DstRowCount);
	if (Stride == DstRowPitch)
	{
		FMemory::Memcpy(Data, TextureData, DstRowPitch * DstRowCount);
	}
	else
	{
		for (auto i = 0u; i < DstRowCount; ++i)
		{
			FMemory::Memcpy(reinterpret_cast<char*>(Data) + DstRowPitch * i,
				reinterpret_cast<char*>(TextureData) + Stride * i,
				DstRowPitch);
		}
	}
	GDynamicRHI->RHIUnlockTexture2D(TexRHI, 0, false);

	return true;
}

void FCohRenoirBackend::UpdateConstantBufferData(const renoir::RendererBackend::ConstantBufferUpdateData* Updates, unsigned Count)
{
	for (auto i = 0u; i < Count; ++i)
	{
		auto Index = IndexOfResource(ConstantBuffers, Updates[i].Object);
		check(Index != INDEX_NONE && "No constant buffer found!");
		auto& Buffer = ConstantBuffers[Index].Value;
		Buffer.Data = reinterpret_cast<const uint8*>(Updates[i].Data);
		Buffer.CurrentOffset = 0;
		bShouldRebindUniformBuffers = true;
	}
}

void FCohRenoirBackend::ExecuteRendering(const renoir::RendererBackend::BackendCommandsBuffer* Buffers,
	unsigned BuffersCount,
	const renoir::RendererBackend::ConstantBufferUpdateData* CBOUpdates,
	unsigned CBOUpdatesCount)
{
	SCOPED_DRAW_EVENT(*CmdList, CoherentRendering_ExecuteRendering);
#if !defined(COHERENT_RENDERING_UE4_413_SUPPORT)
#if defined(COHERENT_RENDERING_UE4_418_SUPPORT)
	SCOPED_GPU_STAT(*CmdList, Stat_GPU_CoherentRendering);
#else
	SCOPED_GPU_STAT(*CmdList, CoherentRendering);
#endif
#endif
	using namespace renoir;

	UpdateConstantBufferData(CBOUpdates, CBOUpdatesCount);

	for (auto i = 0u; i < BuffersCount; ++i)
	{
		// Reset all the "to bind" textures, uniform buffers and samplers for the new command buffer,
		// because we don't want them to persist from the last one
		ResetTexturesToBind();
		ResetUniformBuffersToBind();
		ResetSamplersToBind();

		auto Buffer = Buffers[i];
		INC_DWORD_STAT_BY(STAT_CoherentRenderingCounterRenderingCommands, Buffer.Count);
		for (auto Cmd = 0u; Cmd < Buffer.Count; ++Cmd)
		{
			const auto Offset = Buffer.Offsets[Cmd];

			switch (Offset.Command)
			{
			case BC_SetPipelineState:
			{
				const auto Command = reinterpret_cast<const SetPipelineStateCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetPipelineState(Command);
			}
			break;
			case BC_SetVSConstantBuffers:
			{
				const auto Command = reinterpret_cast<const SetVSConstantBuffersCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetVSConstantBuffers(Command, (const char*)Buffer.Commands + Offset.Offset + sizeof(SetVSConstantBuffersCmd));
			}
			break;
			case BC_SetPSConstantBuffers:
			{
				const auto Command = reinterpret_cast<const SetPSConstantBuffersCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetPSConstantBuffers(Command, (const char*)Buffer.Commands + Offset.Offset + sizeof(SetPSConstantBuffersCmd));
			}
			break;
			case BC_UpdateConstantBuffer:
			{
				const auto Command = reinterpret_cast<const UpdateConstantBufferCmd*>((const char*)Buffer.Commands + Offset.Offset);
				UpdateConstantBuffer(Command);
			}
			break;
			case BC_SetPSSamplers:
			{
				const auto Command = reinterpret_cast<const SetPSSamplersCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetPSSamplers(Command, (const char*)Buffer.Commands + Offset.Offset + sizeof(SetPSSamplersCmd));
			}
			break;
			case BC_SetPSTextures:
			{
				const auto Command = reinterpret_cast<const SetPSTexturesCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetPSTextures(Command, (const char*)Buffer.Commands + Offset.Offset + sizeof(SetPSTexturesCmd));
			}
			break;
			case BC_SetVertexBuffer:
			{
				const auto Command = reinterpret_cast<const SetVertexBufferCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetVertexBuffer(Command);
			}
			break;
			case BC_SetIndexBuffer:
			{
				const auto Command = reinterpret_cast<const SetIndexBufferCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetIndexBuffer(Command);
			}
			break;
			case BC_DrawIndexed:
			{
				const auto Command = reinterpret_cast<const DrawIndexedCmd*>((const char*)Buffer.Commands + Offset.Offset);
				DrawIndexed(Command);
			}
			break;
			case BC_SetRenderTarget:
			{
				const auto Command = reinterpret_cast<const SetRenderTargetCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetRenderTarget(Command);
			}
			break;
#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
			case BC_BeginRenderPass:
			{
				const auto Command = reinterpret_cast<const BeginRenderPassCmd*>((const char*)Buffer.Commands + Offset.Offset);
				BeginRenderPass(Command);
			}
			break;
			case BC_EndRenderPass:
			{
				const auto Command = reinterpret_cast<const EndRenderPassCmd*>((const char*)Buffer.Commands + Offset.Offset);
				EndRenderPass(Command);
			}
			break;
#endif
			case BC_ClearRenderTarget:
			{
				const auto Command = reinterpret_cast<const ClearRenderTargetCmd*>((const char*)Buffer.Commands + Offset.Offset);
				ClearRenderTarget(Command);
			}
			break;
			case BC_SetScissorRect:
			{
				const auto Command = reinterpret_cast<const SetScissorRectCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetScissorRect(Command);
			}
			break;
			case BC_SetViewport:
			{
				const auto Command = reinterpret_cast<const SetViewportCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetViewport(Command);
			}
			break;
			case BC_SetStencilReference:
			{
				const auto Command = reinterpret_cast<const SetStencilReferenceCmd*>((const char*)Buffer.Commands + Offset.Offset);
				SetStencilReference(Command);
			}
			break;
			case BC_ResolveRenderTarget:
			{
				const auto Command = reinterpret_cast<const ResolveRenderTargetCmd*>((const char*)Buffer.Commands + Offset.Offset);
				ResolveRenderTarget(Command);
			}
			break;
			case BC_PushMetadata:
			{
				const auto data = (const char*)Buffer.Commands + Offset.Offset + sizeof(PushMetadataCmd);
				PushMarker(data);
			}
			break;
			case BC_PopMetadata:
			{
				PopMarker();
			}
			break;
			default:
				verify(false && "Unimplemented command detected!");
				break;
			}
		}
	}
}
void FCohRenoirBackend::EndCommands()
{
	RestoreDefaultState();

	if (HWState.RenderTarget)
	{
		CmdList->TransitionResource(EResourceTransitionAccess::EReadable, HWState.RenderTarget);
	}

	CmdList->PopEvent();
	CmdList->SubmitCommandsHint();
}


FCohRenoirBackend::FOcclusionQueryData::FOcclusionQueryData()
{
	Invalidate();
}
FCohRenoirBackend::FOcclusionQueryData::~FOcclusionQueryData()
{
	Invalidate();
}

struct FCohClickThroughRTBulkData : public FResourceBulkDataInterface
{
	FCohClickThroughRTBulkData()
		: Data(0)
	{
	}

	virtual const void* GetResourceBulkData() const override
	{
		return &Data;
	}

	virtual uint32 GetResourceBulkDataSize() const override
	{
		return sizeof(Data);
	}

	virtual void Discard() override
	{
	}

private:
	const unsigned char Data;
};

void FCohRenoirBackend::FOcclusionQueryData::Invalidate()
{
#if defined(COHERENT_RENDERING_UE4_422_SUPPORT)
	Query.SafeRelease();
#else
	Query.ReleaseQuery();
#endif
	OcclusionQueryIssued = nullptr;
	QueryRenderTarget.SafeRelease();
	QueryDepthTarget.SafeRelease();
	QueryDepthState.SafeRelease();
	QueryRasterState.SafeRelease();
	QueryVB.SafeRelease();

	bHasIssuedQuery = false;
	bLastResultIsOnUI = false;
}

struct FCohClickThroughVBResourceArray : public FResourceArrayInterface
{
	FCohClickThroughVBResourceArray()
	{
		uint32 i = 0;

		// Fullscreen triangle vertices in CCW Order;
		// OnCreatePixelReadResources ensures the correct rasterizer state is used
		Data[i++] = -1; Data[i++] = 1;
		Data[i++] = -1; Data[i++] = -3;
		Data[i++] = 3; Data[i++] = 1;

		verify(GetResourceDataSize() == i * sizeof(Data[0]));
	}

	virtual const void* GetResourceData() const override
	{
		return Data;
	}

	virtual uint32 GetResourceDataSize() const override
	{
		return sizeof(Data);
	}

	virtual void Discard() override
	{
	}

	virtual bool IsStatic() const override
	{
		return true;
	}

	virtual bool GetAllowCPUAccess() const override
	{
		return false;
	}

	virtual void SetAllowCPUAccess(bool bInNeedsCPUAccess) override
	{
		verify(!bInNeedsCPUAccess);
	}
private:
	float Data[3 * 2]; // 3 Vertices * (2 floats[pos])
};

bool FCohRenoirBackend::ClickThroughCreateResources(unsigned Object, unsigned /*Width*/, unsigned /*Height*/)
{
	auto Index = IndexOfResource(OcclusionQueryList, Object);
	if (Index != INDEX_NONE)
	{
		// We already have created the data for this view; no need to do anything
		return true;
	}

	auto IndexNew = OcclusionQueryList.AddDefaulted(1);
	OcclusionQueryList[IndexNew].Key = Object;
	FOcclusionQueryData& QueryData = OcclusionQueryList[IndexNew].Value;

	FCohClickThroughRTBulkData BulkData;
	FRHIResourceCreateInfo RTCreateInfo(&BulkData);
#if defined(COHERENT_RENDERING_UE4_421_SUPPORT)
	FRHIResourceCreateInfo DepthStencilCreateInfo(&BulkData);
	DepthStencilCreateInfo.ClearValueBinding = FClearValueBinding(0.5f, 0);
#else
	FRHIResourceCreateInfo DepthStencilCreateInfo(FClearValueBinding(0.5f, 0));
#endif

	QueryData.QueryRenderTarget = RHICreateTexture2D(1, 1, PF_A8, 1, 1, TexCreate_RenderTargetable, RTCreateInfo);
	QueryData.QueryDepthTarget = RHICreateTexture2D(1, 1, PF_DepthStencil, 1, 1, TexCreate_DepthStencilTargetable, DepthStencilCreateInfo);

	FDepthStencilStateInitializerRHI DepthStateInitializer(false, CF_Less);
	QueryData.QueryDepthState = RHICreateDepthStencilState(DepthStateInitializer);

	FRasterizerStateInitializerRHI RasterizerStateInitializer;
	RasterizerStateInitializer.FillMode = FM_Solid;
	RasterizerStateInitializer.CullMode = CM_CW;
	RasterizerStateInitializer.DepthBias = 0;
	RasterizerStateInitializer.SlopeScaleDepthBias = 0;
	RasterizerStateInitializer.bAllowMSAA = false;
	RasterizerStateInitializer.bEnableLineAA = false;
	QueryData.QueryRasterState = RHICreateRasterizerState(RasterizerStateInitializer);

	FCohClickThroughVBResourceArray ClickThroughVB;
	FRHIResourceCreateInfo VBCreateInfo(&ClickThroughVB);
	QueryData.QueryVB = RHICreateVertexBuffer(ClickThroughVB.GetResourceDataSize(), BUF_Static, VBCreateInfo);

	if (!ClickThroughQueryVertexDecl.IsValid())
	{
		FVertexDeclarationElementList Elements;
		Elements.Add(FVertexElement(0, 0, VET_Float2, 0, 8)); // Attribute0
		ClickThroughQueryVertexDecl = RHICreateVertexDeclaration(Elements);
	}
#if defined(COHERENT_RENDERING_UE4_422_SUPPORT)
	QueryData.Query = RHICreateRenderQuery(RQT_Occlusion);
#else
	if (!QueryPool.IsValid())
	{
		QueryPool = RHICreateRenderQueryPool(RQT_Occlusion);
	}
	check(QueryPool.IsValid());
	QueryData.Query = QueryPool->AllocateQuery();
#endif
	return true;
}

void FCohRenoirBackend::ClickThroughDestroyResources(unsigned Object)
{
	// Don't do anything; the plugin will take to destroy the resource when the view is dying
}

void FCohRenoirBackend::ClickThroughDestroyResources_Internal(unsigned ViewId)
{
	DestroyResourceFromList(OcclusionQueryList, ViewId);
}
void FCohRenoirBackend::ClickThroughIssueQuery(unsigned Object, void* Texture, float AlphaThreshold, float NormX, float NormY)
{
	auto Index = IndexOfResource(OcclusionQueryList, Object);
	if (Index != INDEX_NONE)
	{
		auto& QueryData = OcclusionQueryList[Index].Value;
		if (QueryData.bHasIssuedQuery)
		{
			return;
		}
		QueryData.bHasIssuedQuery = true;
		QueryData.bIsQueryReady = false;

#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		FRHIRenderTargetView ColorView(QueryData.QueryRenderTarget);
		FRHISetRenderTargetsInfo RTInfo(1, &ColorView, FRHIDepthRenderTargetView(QueryData.QueryDepthTarget));
		RTInfo.SetClearDepthStencil(true);
#elif defined(COHERENT_RENDERING_UE4_419_SUPPORT)
		FRHIRenderTargetView ColorView(QueryData.QueryRenderTarget, ERenderTargetLoadAction::EClear);
		FRHISetRenderTargetsInfo RTInfo(1, &ColorView, FRHIDepthRenderTargetView(QueryData.QueryDepthTarget, ERenderTargetLoadAction::ELoad, ERenderTargetStoreAction::EStore));
		RTInfo.SetClearDepthStencil(true);
#else
		FRHITexture* ColorTarget = QueryData.QueryRenderTarget.GetReference();
		FRHIRenderPassInfo Pass(1,
			&ColorTarget,
			ERenderTargetActions::Clear_Store,
			QueryData.QueryDepthTarget.GetReference(),
			EDepthStencilTargetActions::ClearDepthStencil_DontStoreDepthStencil);
		Pass.bOcclusionQueries = true;
		Pass.NumOcclusionQueries = 1;
#endif

#if defined(COHERENT_RENDERING_UE4_411_SUPPORT)
		CmdList->PushEvent(TEXT("Coherent GT Click Through Query"));
#else
		CmdList->PushEvent(TEXT("Coherent GT Click Through Query"), FColor::Emerald);
#endif

#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		auto GlobalShaderMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel), false);
#else
		auto GlobalShaderMap = GetGlobalShaderMap(GetFeatureLevelShaderPlatform(GMaxRHIFeatureLevel));
#endif
		auto VertexShader = *TShaderMapRef<FCohRHIClickThroughShaderVS>(GlobalShaderMap);
		auto PixelShader = *TShaderMapRef<FCohRHIClickThroughShaderPS>(GlobalShaderMap);

#if defined(COHERENT_RENDERING_UE4_419_SUPPORT)
		CmdList->SetRenderTargetsAndClear(RTInfo);
		CmdList->BeginOcclusionQueryBatch();
#else
		CmdList->BeginRenderPass(Pass, TEXT("Coherent GT Click Through"));
#endif

#if defined(COHERENT_RENDERING_UE4_422_SUPPORT)
		FRHIRenderQuery* QueryPtr = QueryData.Query.GetReference();
#else
		FRHIRenderQuery* QueryPtr = QueryData.Query.GetQuery();
#endif
		CmdList->BeginRenderQuery(QueryPtr);

#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		static FGlobalBoundShaderState CohBoundShaderState;
		SetGlobalBoundShaderState(*CmdList, GMaxRHIFeatureLevel,
			CohBoundShaderState,
			ClickThroughQueryVertexDecl, VertexShader, PixelShader);
		CmdList->SetDepthStencilState(QueryData.QueryDepthState);
		CmdList->SetRasterizerState(QueryData.QueryRasterState);
#else
		FGraphicsPipelineStateInitializer PsoInitializer;
		CmdList->ApplyCachedRenderTargets(PsoInitializer);
		PsoInitializer.PrimitiveType = PT_TriangleList;
		PsoInitializer.BlendState = TStaticBlendState<>::GetRHI();
		PsoInitializer.DepthStencilState = QueryData.QueryDepthState;
		PsoInitializer.RasterizerState = QueryData.QueryRasterState;
		PsoInitializer.BoundShaderState.VertexDeclarationRHI = ClickThroughQueryVertexDecl;
		PsoInitializer.BoundShaderState.VertexShaderRHI = VertexShader->GetVertexShader();
		PsoInitializer.BoundShaderState.PixelShaderRHI = PixelShader->GetPixelShader();
		SetGraphicsPipelineState(*CmdList, PsoInitializer);
#endif

		auto RHITexture = (FRHITexture2D*)Texture;
		VertexShader->SetData(CmdList, AlphaThreshold, FVector2D(NormX, NormY), RHITexture);

#if defined(COHERENT_RENDERING_UE4_417_SUPPORT)
		CmdList->SetStreamSource(0, QueryData.QueryVB, 8, 0);
#else
		CmdList->SetStreamSource(0, QueryData.QueryVB, 0);
#endif

#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
		CmdList->DrawPrimitive(0, 1, 1);
#else
		CmdList->DrawPrimitive(PT_TriangleList, 0, 1, 1);
#endif

		CmdList->EndRenderQuery(QueryPtr);

		CmdList->PopEvent();
#if defined(COHERENT_RENDERING_UE4_419_SUPPORT)
		CmdList->EndOcclusionQueryBatch();
#else
		CmdList->EndRenderPass();
#endif
		RestoreDefaultState();
		QueryData.OcclusionQueryIssued = QueryPtr;
	}
	else
	{
		check(false && "Unable to issue a query using an unknown query data");
	}
}

bool FCohRenoirBackend::ClickThroughIsQueryReady(unsigned Object)
{
	auto Index = IndexOfResource(OcclusionQueryList, Object);
	if (Index != INDEX_NONE)
	{
		auto& QueryData = OcclusionQueryList[Index].Value;
		if (!QueryData.bHasIssuedQuery)
		{
			return false;
		}
		return TryFetchQueryResult(QueryData);
	}
	UE_LOG(LogCoherentRendering, Error, TEXT("Trying to check whether click through query is ready without valid query object!"));
	return false;
}

bool FCohRenoirBackend::ClickThroughGetQueryResult(unsigned Object)
{
	auto Index = IndexOfResource(OcclusionQueryList, Object);
	if (Index != INDEX_NONE)
	{
		auto& QueryData = OcclusionQueryList[Index].Value;
		// check that Query is already fetched and ready as a result of successful ClickThroughIsQueryReady
		check(QueryData.bIsQueryReady);

		// clear QueryData, breaking next TryFetch without new issued Query
		QueryData.bHasIssuedQuery = false;
		QueryData.bIsQueryReady = false;
		QueryData.OcclusionQueryIssued = nullptr;

		return QueryData.bLastResultIsOnUI;
	}
	UE_LOG(LogCoherentRendering, Error, TEXT("Trying to get click through query result without valid without valid query object!"));
	return false;
}

bool FCohRenoirBackend::TryFetchQueryResult(FOcclusionQueryData& QueryData)
{
#if defined(COHERENT_RENDERING_UE4_422_SUPPORT)
	FRHIRenderQuery* QueryPtr = QueryData.Query.GetReference();
#else
	FRHIRenderQuery* QueryPtr = QueryData.Query.GetQuery();
#endif

	if (QueryData.OcclusionQueryIssued != QueryPtr)
	{
		QueryData.bHasIssuedQuery = false;
		return false;
	}

	uint64 SamplesPassed;
	QueryData.bIsQueryReady = CmdList->GetRenderQueryResult(QueryPtr, SamplesPassed, false);

	if (QueryData.bIsQueryReady)
	{
		QueryData.bLastResultIsOnUI = (SamplesPassed == 0);
	}
	return QueryData.bIsQueryReady;
}

TPair<FRHITexture2D*, FCohStencilBuffer*> FCohRenoirBackend::FindRenderTargetPair(renoir::Texture2DObject RTObject, renoir::DepthStencilTextureObject DSObject)
{
	auto RenderTargetIndex = IndexOfResource(RenderTargetList, RTObject);
	FRHITexture2D* RenderTarget = nullptr;
	FCohStencilBuffer* DepthStencilTarget = nullptr;
	if (RenderTargetIndex != INDEX_NONE)
	{
		RenderTarget = RenderTargetList[RenderTargetIndex].Value.Texture;
		DepthStencilTarget = RenderTargetList[RenderTargetIndex].Value.DepthStencilTexture;
	}
	else
	{
		auto TextureIndex = IndexOfResource(Texture2DList, RTObject);
		if (TextureIndex != INDEX_NONE)
		{
			verify(Texture2DList[TextureIndex].Value->IsRenderTarget());
			RenderTarget = Texture2DList[TextureIndex].Value->GetRenderTargetRHI();
#if TRACK_TEXTURE_DRAWS
			Texture2DList[TextureIndex].Value->bPossibleDrawInFlight = true;
#endif
		}

		auto DepthStencilTextureIndex = IndexOfResource(DepthStencilTextureBuffers, DSObject);
		if (DepthStencilTextureIndex != INDEX_NONE)
		{
			DepthStencilTarget = DepthStencilTextureBuffers[DepthStencilTextureIndex].Value.Get();
		}
	}

	CmdList->TransitionResource(EResourceTransitionAccess::EWritable, RenderTarget);

	return TPairInitializer<FRHITexture2D*, FCohStencilBuffer*>(RenderTarget, DepthStencilTarget);
}

#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
void FCohRenoirBackend::BeginRenderPass(const renoir::BeginRenderPassCmd* Command)
{
	FRHIRenderPassInfo Info;
	const auto RenderTargetDepthStencilPair = FindRenderTargetPair(Command->Object, Command->DSObject);

	ERenderTargetLoadAction RTLoadAction;
	ERenderTargetStoreAction RTStoreAction;
	Info.ColorRenderTargets[0].RenderTarget = RenderTargetDepthStencilPair.Key;

	if (Command->ShouldClearColor)
	{
		check(Command->ClearColor.r == RenderTargetDepthStencilPair.Key->GetClearColor().R);
		check(Command->ClearColor.g == RenderTargetDepthStencilPair.Key->GetClearColor().G);
		check(Command->ClearColor.b == RenderTargetDepthStencilPair.Key->GetClearColor().B);
		check(Command->ClearColor.a == RenderTargetDepthStencilPair.Key->GetClearColor().A);
		RTLoadAction = ERenderTargetLoadAction::EClear;
	}
	else
	{
		RTLoadAction = ERenderTargetLoadAction::ELoad;
	}

	if (Command->ShouldResolveRT)
	{
		const auto ResolveRT = FindRenderTargetPair(Command->ResolveObject, Command->DSObject);
		Info.ColorRenderTargets[0].ResolveTarget = ResolveRT.Key;
		RTStoreAction = ERenderTargetStoreAction::EMultisampleResolve;

		CmdList->TransitionResource(EResourceTransitionAccess::EWritable, ResolveRT.Key);
		HWState.ResolveRenderTarget = ResolveRT.Key;
	}
	else
	{
		RTStoreAction = ERenderTargetStoreAction::EStore;
	}
	Info.ColorRenderTargets[0].Action = MakeRenderTargetActions(RTLoadAction, RTStoreAction);

	if (RenderTargetDepthStencilPair.Value != nullptr)
	{
		ERenderTargetActions DepthLoadStoreActions;
		ERenderTargetActions StencilLoadStoreActions;
		FRHIRenderPassInfo::FDepthStencilEntry DepthStencil;
		Info.DepthStencilRenderTarget.DepthStencilTarget = RenderTargetDepthStencilPair.Value->GetStencilTexture().GetReference();
		RTLoadAction = ERenderTargetLoadAction::ELoad;
		RTStoreAction = ERenderTargetStoreAction::ENoAction;
		DepthLoadStoreActions = MakeRenderTargetActions(RTLoadAction, RTStoreAction);

		if (Command->ShouldClearStencil)
		{
			float DepthClearValue;
			uint32 StencilClearValue;
			RenderTargetDepthStencilPair.Value->GetStencilTexture()->GetDepthStencilClearValue(DepthClearValue, StencilClearValue);
			check(Command->ClearClipValue == StencilClearValue);
			RTLoadAction = ERenderTargetLoadAction::EClear;
		}
		else
		{
			RTLoadAction = ERenderTargetLoadAction::ELoad;
		}

		RTStoreAction = ERenderTargetStoreAction::EStore;
		StencilLoadStoreActions = MakeRenderTargetActions(RTLoadAction, RTStoreAction);
		Info.DepthStencilRenderTarget.Action = MakeDepthStencilTargetActions(DepthLoadStoreActions, StencilLoadStoreActions);
		Info.DepthStencilRenderTarget.ExclusiveDepthStencil = FExclusiveDepthStencil::DepthWrite_StencilWrite;
	}

	HWState.RenderTarget = RenderTargetDepthStencilPair.Key;
	HWState.DepthStencilTarget = RenderTargetDepthStencilPair.Value;

	CmdList->BeginRenderPass(Info, TEXT("Coherent Rendering"));
}

void FCohRenoirBackend::EndRenderPass(const renoir::EndRenderPassCmd* Command)
{
	CmdList->EndRenderPass();

	CmdList->TransitionResource(EResourceTransitionAccess::EReadable, HWState.RenderTarget);
	if (HWState.ResolveRenderTarget)
	{
		CmdList->TransitionResource(EResourceTransitionAccess::EReadable, HWState.ResolveRenderTarget);
	}

	HWState.RenderTarget = nullptr;
	HWState.ResolveRenderTarget = nullptr;
}
#endif

void FCohRenoirBackend::SetRenderTarget(const renoir::SetRenderTargetCmd* Command)
{
	const auto RenderTargetDepthStencilPair = FindRenderTargetPair(Command->Object, Command->DSObject);

	SetRenderTarget(RenderTargetDepthStencilPair.Key, RenderTargetDepthStencilPair.Value);
}

void FCohRenoirBackend::SetRenderTarget(FRHITexture2D* RenderTarget, FCohStencilBuffer* DepthStencilTarget)
{
#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
	check(false && "SetRenderTarget shouldn't be called when renoir::RendererCaps::ShouldUseRenderPasses is true.");
#else
	if (RenderTarget)
	{
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		FRHIRenderTargetView RTV(RenderTarget);
#else
		FRHIRenderTargetView RTV(RenderTarget, ERenderTargetLoadAction::ELoad);
#endif
		if (DepthStencilTarget == nullptr)
		{
			CmdList->SetRenderTargets(1, &RTV, NULL, 0, NULL);
		}
		else
		{
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
			FRHIDepthRenderTargetView DepthRenderView(DepthStencilTarget->GetStencilTexture());
#else
			FRHIDepthRenderTargetView DepthRenderView(DepthStencilTarget->GetStencilTexture(), ERenderTargetLoadAction::ELoad, ERenderTargetStoreAction::EStore);
#endif
			CmdList->SetRenderTargets(1, &RTV, &DepthRenderView, 0, NULL);
		}
	}
	else
	{
		if (DepthStencilTarget)
		{
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
			FRHIDepthRenderTargetView DepthRenderView(DepthStencilTarget->GetStencilTexture());
#else
			FRHIDepthRenderTargetView DepthRenderView(DepthStencilTarget->GetStencilTexture(), ERenderTargetLoadAction::ELoad, ERenderTargetStoreAction::EStore);
#endif
			CmdList->SetRenderTargets(0, NULL, &DepthRenderView, 0, NULL);
		}
		else
		{
			CmdList->SetRenderTargets(0, NULL, NULL, 0, NULL);
		}
	}

	if (HWState.RenderTarget)
	{
		CmdList->TransitionResource(EResourceTransitionAccess::EReadable, HWState.RenderTarget);
	}

	HWState.RenderTarget = RenderTarget;
	HWState.DepthStencilTarget = DepthStencilTarget;
#endif
}

void FCohRenoirBackend::SetPipelineState(const renoir::SetPipelineStateCmd* Command)
{
	auto Index = IndexOfResource(PipelineStateList, Command->Object);
	if (Index != INDEX_NONE)
	{
		auto& NewPipelineState = PipelineStateList[Index].Value;
		auto NewBlendState = BlendCache[FUE4BlendingState(NewPipelineState.Blending, NewPipelineState.ColorMask)];
		auto NewStencilState = StencilCache[NewPipelineState.DepthStencil];
		auto NewVertexShader = VertexShaderCache.FindChecked(NewPipelineState.VertexShader);
		auto NewPixelShader = PixelShaderCache.FindChecked(NewPipelineState.PixelShader);
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		if (CurrentPipelineState.BlendState != NewBlendState)
		{
			CmdList->SetBlendState(NewBlendState, FLinearColor::Transparent);
			CurrentPipelineState.BlendState = NewBlendState;
		}
		if (CurrentPipelineState.DepthStencilState != NewStencilState)
		{
			CmdList->SetDepthStencilState(NewStencilState, CurrentPipelineState.StencilRef);
			CurrentPipelineState.DepthStencilState = NewStencilState;
		}
		CmdList->SetRasterizerState(DefaultRasterState);
		if (CurrentPipelineState.VertexShader != NewVertexShader
			|| CurrentPipelineState.PixelShader != NewPixelShader)
#endif
		{
			FCohVertexDecl* VertexDecl;
			if (NewPipelineState.VertexShader == renoir::ST_Path
				|| NewPipelineState.VertexShader == renoir::ST_StencilPath)
			{
				VertexDecl = VertexDeclCache[renoir::VT_Slim].Get();
			}
			else
			{
				VertexDecl = VertexDeclCache[renoir::VT_Standard].Get();
			}
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
			auto NewBoundShaderState = RHICreateBoundShaderState(VertexDecl->VertexDeclarationRHI, NewVertexShader->GetVertexShader(),
				nullptr, nullptr, NewPixelShader->GetPixelShader(), nullptr);

			CmdList->SetBoundShaderState(NewBoundShaderState);

			CurrentPipelineState.VertexShader = NewVertexShader;
			CurrentPipelineState.PixelShader = NewPixelShader;
			CurrentPipelineState.BoundShaderState = NewBoundShaderState;
#else
			FGraphicsPipelineStateInitializer PsoInitializer;
			CmdList->ApplyCachedRenderTargets(PsoInitializer);
			PsoInitializer.PrimitiveType = PT_TriangleList;
			PsoInitializer.BlendState = NewBlendState;
			PsoInitializer.RasterizerState = DefaultRasterState;
			PsoInitializer.DepthStencilState = NewStencilState;

			PsoInitializer.BoundShaderState.VertexDeclarationRHI = VertexDecl->VertexDeclarationRHI;
			PsoInitializer.BoundShaderState.VertexShaderRHI = NewVertexShader->GetVertexShader();
			PsoInitializer.BoundShaderState.PixelShaderRHI = NewPixelShader->GetPixelShader();

			CurrentPipelineState.PsoInitializer = PsoInitializer;
			CurrentPipelineState.VertexShader = NewVertexShader;
			CurrentPipelineState.PixelShader = NewPixelShader;

			CurrentPipelineState.bRequiresStencilWrite = NewPipelineState.DepthStencil.StencilEnable;

			SetGraphicsPipelineState(*CmdList, PsoInitializer);
			CmdList->SetStencilRef(CurrentPipelineState.StencilRef);
#endif
			bShouldRebindUniformBuffers = true;
			bShouldRebindTextures = true;
			bShouldRebindSamplers = true;
		}
	}
	else
	{
		check(false && "Unable to use an unknown pipeline state!");
	}

	if (IsMetalPlatform(GMaxRHIShaderPlatform)
		|| IsPS4Platform(GMaxRHIShaderPlatform))
	{
		for (auto i = 0; i < MAX_BOUND_SAMPLERS; i++)
		{
			CurrentPipelineState.PixelShader->SetShaderSampler(CmdList, i, DummySampler);
		}
	}
}


void FCohRenoirBackend::SetStencilReference(const renoir::SetStencilReferenceCmd* Command)
{
	auto StencilRef = Command->Value;
	if (CurrentPipelineState.StencilRef == StencilRef)
	{
		return;
	}
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
	if (CurrentPipelineState.DepthStencilState)
	{
		CmdList->SetDepthStencilState(CurrentPipelineState.DepthStencilState, StencilRef);
	}
#else
	CmdList->SetStencilRef(StencilRef);
#endif
	CurrentPipelineState.StencilRef = StencilRef;
}

void FCohRenoirBackend::SetScissorRect(const renoir::SetScissorRectCmd* Command)
{
	// TODO: This is here because WebCore is sending ScissorRect with zero width and height.
	// It will be removed when we find a way how to fix it globally.
	bIsScissorRectValid = (Command->Rect.z * Command->Rect.w) != 0;

	if (!bIsScissorRectValid)
	{
		return;
	}

	if (Command->Enabled )
	{
		CmdList->SetScissorRect(true,
			Command->Rect.x,
			Command->Rect.y,
			Command->Rect.x + Command->Rect.z,
			Command->Rect.y + Command->Rect.w);
	}
	else
	{
		CmdList->SetScissorRect(false,
			0,
			0,
			16384,
			16384);
	}
	HWState.CurrentScissorRect = *Command;
}

void FCohRenoirBackend::SetViewport(const renoir::SetViewportCmd* Command)
{
	CmdList->SetViewport(
		Command->Rect.x,
		Command->Rect.y,
		0,
		Command->Rect.x + Command->Rect.z,
		Command->Rect.y + Command->Rect.w,
		1.0f);
}

void FCohRenoirBackend::ClearRenderTarget(const renoir::ClearRenderTargetCmd* Command)
{
	verify(false && "Clearing render targets is done only with Clear Quad."
		"The backend capability ShouldClearRTWithClearQuad must be enabled.");
}

void FCohRenoirBackend::SetVertexBuffer(const renoir::SetVertexBufferCmd* Command)
{
	auto Index = IndexOfResource(VertexBuffers, Command->Object);
	if (Index != INDEX_NONE)
	{
		RequestedVertexBuffer = VertexBuffers[Index].Value.Get();
	}
	else
	{
		verify(false && "Unable to find vertex buffer!");
	}
}

void FCohRenoirBackend::SetIndexBuffer(const renoir::SetIndexBufferCmd* Command)
{
	auto Index = IndexOfResource(IndexBuffers, Command->Object);
	if (Index != INDEX_NONE)
	{
		HWState.IndexBuffer = IndexBuffers[Index].Value.Get();
	}
	else
	{
		verify(false && "Unable to find vertex buffer!");
	}
}

void FCohRenoirBackend::SetPSSamplers(const renoir::SetPSSamplersCmd* Command, const void* DataAfter)
{
	const renoir::Sampler2DObject* SamplerObjects = reinterpret_cast<const renoir::Sampler2DObject*>(DataAfter);
	const auto Count = Command->Count;
	for (auto i = 0u; i < Count; ++i)
	{
		check(Command->StartSlot + i < MAX_BOUND_SAMPLERS);
		SamplersToRebind[Command->StartSlot + i] = SamplerObjects[i];
	}

	bShouldRebindSamplers = true;
}

void FCohRenoirBackend::SetPSTextures(const renoir::SetPSTexturesCmd* Command, const void* DataAfter)
{
	const renoir::Texture2DObject* TextureObjects = reinterpret_cast<const renoir::Texture2DObject*>(DataAfter);
	const auto Count = Command->Count;
	for (auto i = 0u; i < Count; ++i)
	{
		check(Command->StartSlot + i < MAX_BOUND_TEXTURES);
		TexturesToRebind[Command->StartSlot + i] = TextureObjects[i];
	}
	bShouldRebindTextures = true;
}

void FCohRenoirBackend::ResetUniformBuffersToBind()
{
	// Set all buffers to rebind to -1
	for (auto i = 0; i < renoir::CBType::CB_Count; i++)
	{
		VertexShaderBuffersToRebind[i].Id = PixelShaderBuffersToRebind[i].Id = RENOIR_INVALID;
	}
}

void FCohRenoirBackend::ResetTexturesToBind()
{
	for (auto i = 0; i < TexturesToRebind.Num(); i++)
	{
		TexturesToRebind[i].Id = RENOIR_INVALID;
	}
}

void FCohRenoirBackend::ResetSamplersToBind()
{
	for (auto i = 0; i < SamplersToRebind.Num(); i++)
	{
		SamplersToRebind[i] = renoir::Sampler2DObject();
	}
}

void FCohRenoirBackend::BindConstantBuffers()
{
	auto VertexShader = CurrentPipelineState.VertexShader;
	for (auto& BufferObject : VertexShaderBuffersToRebind)
	{
		auto Index = IndexOfResource(ConstantBuffers, BufferObject);
		if (Index != INDEX_NONE)
		{
			auto& Buffer = ConstantBuffers[Index].Value;
			VertexShader->BindBuffer(*CmdList, Buffer.Type, Buffer.Data + Buffer.CurrentOffset);
		}
	}
	auto PixelShader = CurrentPipelineState.PixelShader;
	for (auto& BufferObject : PixelShaderBuffersToRebind)
	{
		auto Index = IndexOfResource(ConstantBuffers, BufferObject);
		if (Index != INDEX_NONE)
		{
			auto& Buffer = ConstantBuffers[Index].Value;
			PixelShader->BindBuffer(*CmdList, Buffer.Type, Buffer.Data + Buffer.CurrentOffset);
		}
	}
}

void FCohRenoirBackend::BindTextures()
{
	for (auto i = 0; i < TexturesToRebind.Num(); ++i)
	{
		if (!TexturesToRebind[i].IsValid())
		{
			FRHITexture2D* DummyTextureRef = DummyTexture->GetTextureRHI().GetReference();
			CurrentPipelineState.PixelShader->SetShaderTexture(CmdList, i, DummyTextureRef);
			continue;
		}

		FRHITexture2D* Texture = nullptr;
		auto Index = IndexOfResource(Texture2DList, TexturesToRebind[i]);
		bool bIsTextureUserRT = false;
		if (Index != INDEX_NONE)
		{
			Texture = Texture2DList[Index].Value->GetTextureRHI().GetReference();
		}
		else
		{
			Index = IndexOfResource(RenderTargetList, TexturesToRebind[i]);
			check(Index != INDEX_NONE && "Attempt to use an unknown texture!");
			Texture = RenderTargetList[Index].Value.Texture;
			bIsTextureUserRT = true;
		}
		CurrentPipelineState.PixelShader->SetShaderTexture(CmdList, i, Texture);

#if TRACK_TEXTURE_DRAWS
		if (bIsTextureUserRT || Texture2DList[Index].Value->bPossibleDrawInFlight)
		{
#if defined(COHERENT_RENDERING_UE4_410_SUPPORT)
			auto RenderTargetParamRef = bIsTextureUserRT ?
				Texture :
				Texture2DList[Index].Value->GetRenderTargetRHI().GetReference();
			FResolveParams ResolveParams;
			CmdList->CopyToResolveTarget(RenderTargetParamRef, RenderTargetParamRef, true, ResolveParams);
#else
			CmdList->TransitionResource(EResourceTransitionAccess::EReadable, Texture);
#endif
			if (!bIsTextureUserRT)
			{
				Texture2DList[Index].Value->bPossibleDrawInFlight = false;
			}
		}
#endif
	}
}

void FCohRenoirBackend::BindSamplers()
{
	for (auto i = 0; i < SamplersToRebind.Num(); ++i)
	{
		if (!SamplersToRebind[i].IsValid())
		{
			continue;
		}

		auto Index = IndexOfResource(Sampler2DList, SamplersToRebind[i]);
		if (Index != INDEX_NONE)
		{
			CurrentPipelineState.PixelShader->SetShaderSampler(CmdList, i, Sampler2DList[Index].Value);

			// This is a workaround for the VulkanRHI as UE4 seems to shuffle the samplers binding indices
			// during crosscompilation of our shaders and this results in sampling text with a wrong Point sampler.
			// We currently don't know how to tell UE4 to keep our shader bindings. In order to workaround this problem we just
			// set our first sampler to all the bindings. This is acceptable, because we generally use only one sampler in our rendering pipeline.
			if (IsVulkanPlatform(GMaxRHIShaderPlatform) && !i)
			{
				CurrentPipelineState.PixelShader->SetShaderSampler(CmdList, 1, Sampler2DList[Index].Value);
				CurrentPipelineState.PixelShader->SetShaderSampler(CmdList, 2, Sampler2DList[Index].Value);
				CurrentPipelineState.PixelShader->SetShaderSampler(CmdList, 3, Sampler2DList[Index].Value);
			}
		}
		else
		{
			check(false && "Attempt to use an unknown pixel shader sampler!");
		}
	}
}

void FCohRenoirBackend::SetVSConstantBuffers(const renoir::SetVSConstantBuffersCmd* Command, const void* DataAfter)
{
	const renoir::ConstantBufferObject* UniformBufferObjects = reinterpret_cast<const renoir::ConstantBufferObject*>(DataAfter);
	const auto Count = Command->Count;
	for (auto i = 0u; i < Count; ++i)
	{
		VertexShaderBuffersToRebind[Command->StartSlot + i] = UniformBufferObjects[i];
	}
	bShouldRebindUniformBuffers = true;
}

void FCohRenoirBackend::SetPSConstantBuffers(const renoir::SetPSConstantBuffersCmd* Command, const void* DataAfter)
{
	const renoir::ConstantBufferObject* UniformBufferObjects = reinterpret_cast<const renoir::ConstantBufferObject*>(DataAfter);
	const auto Count = Command->Count;
	for (auto i = 0u; i < Count; ++i)
	{
		PixelShaderBuffersToRebind[Command->StartSlot + i] = UniformBufferObjects[i];
	}
	bShouldRebindUniformBuffers = true;
}

void FCohRenoirBackend::UpdateConstantBuffer(const renoir::UpdateConstantBufferCmd* Command)
{
	auto Index = IndexOfResource(ConstantBuffers, Command->Object);
	check(Index != INDEX_NONE && "No constant buffer found!");
	auto& Buffer = ConstantBuffers[Index].Value;
	Buffer.CurrentOffset = Command->Offset;
	bShouldRebindUniformBuffers = true;
}

void FCohRenoirBackend::DrawIndexed(const renoir::DrawIndexedCmd* Command)
{
	if (!bIsScissorRectValid)
	{
		return;
	}
	SCOPED_DRAW_EVENT(*CmdList, CoherentRendering_DrawIndexed);
	INC_DWORD_STAT_BY(STAT_CoherentRenderingCounterDrawBatches, 1);
	if (RequestedVertexBuffer != HWState.VertexBuffer)
	{
		HWState.VertexBuffer = RequestedVertexBuffer;
#if defined(COHERENT_RENDERING_UE4_417_SUPPORT)
		auto VertexType = HWState.VertexBuffer->GetVertexDecl();
		auto VertexDecl = VertexDeclCache[VertexType].Get();
		CmdList->SetStreamSource(0, HWState.VertexBuffer->VertexBufferRHI, VertexDecl->Stride, 0);
#else
		CmdList->SetStreamSource(0, HWState.VertexBuffer->VertexBufferRHI, 0);
#endif
	}
	if (bShouldRebindUniformBuffers)
	{
		BindConstantBuffers();
		bShouldRebindUniformBuffers = false;
	}
	if (bShouldRebindTextures)
	{
		BindTextures();
		bShouldRebindTextures = false;
	}
	if (bShouldRebindSamplers)
	{
		BindSamplers();
		bShouldRebindSamplers = false;
	}
	static const EPrimitiveType PrimitiveMap[] = {
		PT_TriangleList,
		PT_Num
	};
	check(HWState.IndexBuffer);
	check(HWState.VertexBuffer);

	uint32 PrimitiveCount = 0;

	switch (Command->Topology)
	{
	case renoir::PTO_TriangleList:
		PrimitiveCount = Command->IndexCount / 3;
		break;
	default:
		check(false && "Unsupported primitive type");
		break;
	}

	if (Command->IndexCount)
	{
		CmdList->DrawIndexedPrimitive(
			HWState.IndexBuffer->IndexBufferRHI,
#if defined(COHERENT_RENDERING_UE4_421_SUPPORT)
			PrimitiveMap[Command->Topology],
#endif
			Command->BaseVertex,
			0,
			Command->IndexCount * 3,
			Command->StartIndex,
			PrimitiveCount,
			1);
	}
	else
	{
		CmdList->DrawPrimitive(
#if defined(COHERENT_RENDERING_UE4_421_SUPPORT)
			PrimitiveMap[Command->Topology],
#endif
			Command->BaseVertex,
			PrimitiveCount,
			1);
	}
}

void FCohRenoirBackend::ResolveRenderTarget(const renoir::ResolveRenderTargetCmd* Command)
{
	auto SrcIndex = IndexOfResource(Texture2DList, Command->Source);
	auto DstIndex = IndexOfResource(Texture2DList, Command->Destination);
	if (SrcIndex != INDEX_NONE && DstIndex != INDEX_NONE)
	{
		auto& Src = Texture2DList[SrcIndex].Value;
		auto& Dst = Texture2DList[DstIndex].Value;
		FResolveParams ResolveParams;
		CmdList->CopyToResolveTarget(Src->GetRenderTargetRHI(),
			Dst->GetTextureRHI(),
#if defined(COHERENT_RENDERING_UE4_419_SUPPORT)
			true,
#endif
			ResolveParams);
	}
	else
	{
		check(false && "Unable to resolve an unknown render target");
	}
}

void FCohRenoirBackend::PushMarker(const char* Marker)
{
	FString MarkerString(Marker);
#if !defined(COHERENT_RENDERING_UE4_411_SUPPORT)
	CmdList->PushEvent(*MarkerString, FColor(200, 10, 160));
#else
	CmdList->PushEvent(*MarkerString);
#endif
}

void FCohRenoirBackend::PopMarker()
{
	CmdList->PopEvent();
}

#undef ActOnUniformBuffer

IRenderingBackend::FCohRenoirBackendCmdListScope::FCohRenoirBackendCmdListScope(IRenderingBackend* backend, FRHICommandListImmediate& list)
	: Backend(backend)
{
	static_cast<FCohRenoirBackend*>(Backend)->SetRHICmdList(&list);
}

IRenderingBackend::FCohRenoirBackendCmdListScope::~FCohRenoirBackendCmdListScope()
{
	static_cast<FCohRenoirBackend*>(Backend)->SetRHICmdList(nullptr);
}
