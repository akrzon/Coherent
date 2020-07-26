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

#include <RenoirBackend/RendererBackend.h>
#include <RenoirBackend/ClickThroughProvider.h>
#include <RenoirBackend/CommonTypes.h>
#include "CohHelpers.h"
#include "CohTexture.h"
#include "CohStencilBuffer.h"
#include "CohRenoirShaders.h"

struct FRenoirRenderTarget
{
	renoir::Texture2D Description;
	FRHITexture2D* Texture;
	FCohStencilBuffer* DepthStencilTexture;
};
class FCohStencilBuffer;
class FCohVertexBuffer;
class FCohIndexBuffer;

struct FUE4BlendingState : public renoir::BlendingState
{
	renoir::ColorWriteMask RTColorWriteMask = renoir::ColorWriteMask::CWM_All;

	FUE4BlendingState(const BlendingState& blendState, renoir::ColorWriteMask rtColorWriteMask)
		: BlendingState(blendState)
		, RTColorWriteMask(rtColorWriteMask)
	{}

	bool operator==(const FUE4BlendingState& rhs) const
	{
		return BlendingState::operator==(rhs)
			&& RTColorWriteMask == rhs.RTColorWriteMask;
	}

	bool operator!=(const FUE4BlendingState& rhs) const
	{
		return !(*this == rhs);
	}
};

class FCohRenoirBackend : public IRenderingBackend
{
public:
	FCohRenoirBackend();
	virtual ~FCohRenoirBackend();

	// renoir::RendererBackend interface
	virtual void BeginCommands() override;

	virtual void FillCaps(renoir::RendererCaps& outCaps) override;

	virtual void WrapUserRenderTarget(void* userObject,
		const renoir::Texture2D& description,
		renoir::Texture2DObject object,
		void* depthStencil,
		const renoir::DepthStencilTexture& dsDescription,
		renoir::DepthStencilTextureObject dsObject) override;

	virtual void WrapUserTexture(void* userObject,
		const renoir::Texture2D& description,
		renoir::Texture2DObject object) override;

	virtual bool CreatePipelineState(const renoir::PipelineState& state, renoir::PipelineStateObject object) override;
	virtual void DestroyPipelineState(renoir::PipelineStateObject object) override;

	virtual bool CreateVertexBuffer(renoir::VertexType type, unsigned count, renoir::VertexBufferObject object, bool changesOften) override;
	virtual void DestroyVertexBuffer(renoir::VertexBufferObject object) override;
	virtual void* MapVertexBuffer(renoir::VertexBufferObject object) override;
	virtual void UnmapVertexBuffer(renoir::VertexBufferObject object, unsigned elementCount) override;

	virtual bool CreateIndexBuffer(renoir::IndexBufferType format, unsigned count, renoir::IndexBufferObject object, bool changesOften) override;
	virtual void DestroyIndexBuffer(renoir::IndexBufferObject object) override;
	virtual void* MapIndexBuffer(renoir::IndexBufferObject object) override;
	virtual void UnmapIndexBuffer(renoir::IndexBufferObject object, unsigned elementCount) override;

	virtual bool CreateConstantBuffer(renoir::CBType type, renoir::ConstantBufferObject object, unsigned size) override;
	virtual void DestroyConstantBuffer(renoir::ConstantBufferObject object) override;

	virtual bool CreateTexture(renoir::Texture2DObject texture, const renoir::Texture2D& description, const void* data, unsigned dataLen) override;
	virtual void DestroyTexture(renoir::Texture2DObject texture) override;
	virtual void UpdateTexture(renoir::Texture2DObject texture, const renoir::Texture2D& description, renoir::UpdateBox* boxes, const void** newBytes, unsigned count, bool willOverwrite) override;

	virtual bool CreateDepthStencilTexture(renoir::DepthStencilTextureObject object, const renoir::DepthStencilTexture& description) override;
	virtual void DestroyDepthStencilTexture(renoir::DepthStencilTextureObject object) override;

	virtual bool CreateSampler2D(renoir::Sampler2DObject sampler, const renoir::Sampler2D& description) override;
	virtual void DestroySampler2D(renoir::Sampler2DObject sampler) override;

	virtual void SetDebugName(renoir::Texture2DObject Texture, const char* Name) override;
	virtual void SetDebugName(renoir::DepthStencilTextureObject DS, const char* Name) override;

	virtual bool ReadTexture(renoir::TextureObject Source, const renoir::UpdateBox& ReadBox, void* Data) override;

	virtual void ExecuteRendering(const renoir::RendererBackend::BackendCommandsBuffer* buffers,
		unsigned buffersCount,
		const renoir::RendererBackend::ConstantBufferUpdateData* CBOUpdates,
		unsigned CBOUpdatesCount) override;
	virtual void EndCommands() override;

	// GT will usually call destroy/create in pairs when resizing the view.
	// We don't need to actually destroy anything or create anything during resize since we don't care about the size of the view
	// (and this also caused a very subtle crash - see COH-2999 for more info)
	// The RenderWrapper will take care to destroy the clickthrough resources when the view finally dies.
	virtual bool ClickThroughCreateResources(unsigned objectId, unsigned width, unsigned height) override;
	virtual void ClickThroughDestroyResources(unsigned objectId) override;
	// Important: This method assumes that the id for each view's clickthrough resources is the view's id.
	// This is an implementation detail of the native SDK so technically it is incorrect to depend on that.
	// However, it is extremely unlikely this will change so it is safe. If the assumtion fails, we'll hit an assert immediately.
	void ClickThroughDestroyResources_Internal(unsigned ViewId);
	virtual void ClickThroughIssueQuery(unsigned objectId, void* texture, float alphaThreshold, float normX, float normY) override;
	virtual bool ClickThroughIsQueryReady(unsigned objectId) override;
	virtual bool ClickThroughGetQueryResult(unsigned objectId) override;
public:
	struct FCohVertexAttrib
	{
		EVertexElementType Type;
		unsigned Offset;

		bool operator==(const FCohVertexAttrib& rhs) const
		{
			return Type == rhs.Type
				&& Offset == rhs.Offset;
		}

		bool operator!=(const FCohVertexAttrib& rhs) const
		{
			return !(*this == rhs);
		}
	};
	typedef TArray<FCohVertexAttrib> VertexAttributes;
private:
	void RestoreDefaultState();
	void SetRHICmdList(FRHICommandListImmediate* list);

	void SetScissorRect(const renoir::SetScissorRectCmd* Command);
	void SetViewport(const renoir::SetViewportCmd* Command);
	void ClearRenderTarget(const renoir::ClearRenderTargetCmd* Command);
	void SetVertexBuffer(const renoir::SetVertexBufferCmd* Command);
	void SetIndexBuffer(const renoir::SetIndexBufferCmd* Command);
	void SetPSSamplers(const renoir::SetPSSamplersCmd* Command, const void* DataAfter);
	void SetPSTextures(const renoir::SetPSTexturesCmd* Command, const void* DataAfter);
	void InitUniformBuffers();
	void BindConstantBuffers();
	void ResetUniformBuffersToBind();
	void BindTextures();
	void BindSamplers();
	void ResetTexturesToBind();
	void ResetSamplersToBind();
	void SetPSConstantBuffers(const renoir::SetPSConstantBuffersCmd* Command, const void* DataAfter);
	void SetVSConstantBuffers(const renoir::SetVSConstantBuffersCmd* Command, const void* DataAfter);
	void UpdateConstantBuffer(const renoir::UpdateConstantBufferCmd* Command);
	void UpdateConstantBufferData(const renoir::RendererBackend::ConstantBufferUpdateData* Updates, unsigned Count);
	void SetPipelineState(const renoir::SetPipelineStateCmd* Command);
	void SetStencilReference(const renoir::SetStencilReferenceCmd* Command);
	void SetRenderTarget(const renoir::SetRenderTargetCmd* Command);
	void SetRenderTarget(FRHITexture2D* RenderTarget, FCohStencilBuffer* DepthStencilTarget);
	void DrawIndexed(const renoir::DrawIndexedCmd* Command);
	void ResolveRenderTarget(const renoir::ResolveRenderTargetCmd* Command);
	TPair<FRHITexture2D*, FCohStencilBuffer*> FindRenderTargetPair(renoir::Texture2DObject RTObject, renoir::DepthStencilTextureObject DSObject);
	void InitializeDummySampler();
#if !defined(COHERENT_RENDERING_UE4_421_SUPPORT)
	void BeginRenderPass(const renoir::BeginRenderPassCmd* Command);
	void EndRenderPass(const renoir::EndRenderPassCmd* Command);
#endif

	void PushMarker(const char* Marker);
	void PopMarker();

	FRHICommandListImmediate* CmdList;

	struct FPipelineState
	{
		CohShaders::FCohShaderPS* PixelShader = nullptr;
		CohShaders::FCohShaderVS* VertexShader = nullptr;
#if defined(COHERENT_RENDERING_UE4_415_SUPPORT)
		FBlendStateRHIRef BlendState = nullptr;
		FDepthStencilStateRHIRef DepthStencilState = nullptr;
		FBoundShaderStateRHIRef BoundShaderState = nullptr;
#else
		FGraphicsPipelineStateInitializer PsoInitializer;
#endif
		uint32 StencilRef = 0u;
		// This is used to track whether the current DepthStencilState requires stencil writes (As we can't get that info from the RHI object)
		// and we need it in order to determine whether we need to restore the Pipeline state after Clear commands
		bool bRequiresStencilWrite = false;
	};
	FPipelineState CurrentPipelineState;
	FRasterizerStateRHIRef DefaultRasterState = nullptr;

#if !defined(COHERENT_RENDERING_UE4_422_SUPPORT)
	FRenderQueryPoolRHIRef QueryPool;
#endif

	struct FOcclusionQueryData
	{
		FOcclusionQueryData();
		~FOcclusionQueryData();
		void Invalidate();

#if defined(COHERENT_RENDERING_UE4_422_SUPPORT)
		FRenderQueryRHIRef Query;
#else
		FRHIPooledRenderQuery Query;
#endif
		FRHIRenderQuery* OcclusionQueryIssued;
		FTexture2DRHIRef QueryRenderTarget;
		FTexture2DRHIRef QueryDepthTarget;
		FDepthStencilStateRHIRef QueryDepthState;
		FRasterizerStateRHIRef QueryRasterState;
		FVertexBufferRHIRef QueryVB;

		bool bHasIssuedQuery;
		bool bIsQueryReady;
		bool bLastResultIsOnUI;
	};
	FVertexDeclarationRHIRef ClickThroughQueryVertexDecl;

	bool TryFetchQueryResult(struct FOcclusionQueryData& QueryData);

	typedef TPair<renoir::VertexBufferObject, TUniquePtr<FCohVertexBuffer>> VertexBufferPair;
	typedef TPair<renoir::IndexBufferObject, TUniquePtr<FCohIndexBuffer>> IndexBufferPair;
	typedef TPair<renoir::DepthStencilTextureObject, TUniquePtr<FCohStencilBuffer>> DepthStencilTexturePair;
	typedef TPair<renoir::Texture2DObject, FRenoirRenderTarget> RenderTargetPair;
	typedef TPair<renoir::Texture2DObject, TUniquePtr<FCohTexture>> Texture2DPair;
	typedef TPair<renoir::Sampler2DObject, FSamplerStateRHIRef> Sampler2DPair;
	typedef TPair<renoir::PipelineStateObject, renoir::PipelineState> PipelineStatePair;
	typedef TPair<unsigned, FOcclusionQueryData> OcclusionQueryPair;

	renoir::VertexType CurrentVertexDeclaration;
	TArray<VertexBufferPair> VertexBuffers;
	TArray<IndexBufferPair> IndexBuffers;
	TArray<DepthStencilTexturePair> DepthStencilTextureBuffers;
	TArray<RenderTargetPair> RenderTargetList;
	TArray<Texture2DPair> Texture2DList;
	TArray<Sampler2DPair> Sampler2DList;
	TArray<PipelineStatePair> PipelineStateList;
	TArray<OcclusionQueryPair> OcclusionQueryList;

	struct FConstantBuffer
	{
		renoir::CBType Type;
		const uint8* Data;
		unsigned CurrentOffset;
	};
	typedef TPair<renoir::ConstantBufferObject, FConstantBuffer> ConstantBufferPair;
	TArray<ConstantBufferPair> ConstantBuffers;
	TArray<renoir::ConstantBufferObject> VertexShaderBuffersToRebind;
	TArray<renoir::ConstantBufferObject> PixelShaderBuffersToRebind;
	bool bShouldRebindUniformBuffers;

	TArray<renoir::Texture2DObject> TexturesToRebind;
	bool bShouldRebindTextures;

	TArray<renoir::Sampler2DObject> SamplersToRebind;
	bool bShouldRebindSamplers;

	TUniquePtr<FCohTexture> DummyTexture;
	FSamplerStateRHIRef DummySampler;

	struct FHardwareState
	{
		FCohVertexBuffer* VertexBuffer = nullptr;
		FCohIndexBuffer* IndexBuffer = nullptr;
		FRHITexture2D* RenderTarget = nullptr;
		FCohStencilBuffer* DepthStencilTarget = nullptr;
		FRHITexture2D* ResolveRenderTarget = nullptr;
		renoir::SetScissorRectCmd CurrentScissorRect = renoir::SetScissorRectCmd{ true, renoir::float4{0, 0, 16384, 16384} };
	};
	FHardwareState HWState;
	FCohVertexBuffer* RequestedVertexBuffer;

	template<typename KeyType, typename ValueType, typename SetAllocator = FDefaultSetAllocator, typename KeyFuncs = TDefaultMapKeyFuncs<KeyType, ValueType, false>>
	using TMapDefaultFuncs = TMap<KeyType, ValueType, SetAllocator, KeyFuncs>;

	TMapDefaultFuncs<renoir::DepthStencilState, FDepthStencilStateRHIRef> StencilCache;
	TMapDefaultFuncs<FUE4BlendingState, FBlendStateRHIRef> BlendCache;
	TMap<renoir::VertexType, TUniquePtr<class FCohVertexDecl>> VertexDeclCache;
	TMap<renoir::ShaderType, CohShaders::FCohShaderVS*> VertexShaderCache;
	TMap<renoir::ShaderType, CohShaders::FCohShaderPS*> PixelShaderCache;
	bool bIsScissorRectValid;

	friend struct IRenderingBackend::FCohRenoirBackendCmdListScope;
};
