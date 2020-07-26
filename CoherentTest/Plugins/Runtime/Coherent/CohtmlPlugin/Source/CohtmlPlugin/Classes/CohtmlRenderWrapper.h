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

#include "Engine/TextureRenderTarget2D.h"

#include "cohtml/View.h"
#include "cohtml/TextInputHandler.h"
#include "cohtml/ViewRenderer.h"
#include "cohtml/System.h"
#include "cohtml/SystemRenderer.h"

#include "CohtmlJSEvent.h"

#include "CohtmlMeshData.h"
#include "Containers/CircularQueue.h"
#include "HAL/ThreadSafeBool.h"

class FCohtmlRendererHolder;
class FCohtmlSystemWrapper;
typedef TSharedPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> FCohtmlSystemWrapperSharedPtr;
typedef TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe> FCohtmlRendererHolderSharedPtr;

namespace cohtml
{
	class SystemRenderer;
}

class COHTMLPLUGIN_API FCohtmlRenderWrapper
{
public:
	FCohtmlRenderWrapper(TSharedPtr<cohtml::IViewListener> ViewListener,
		TSharedPtr<cohtml::ITextInputHandler> TextInputHandler,
		UTextureRenderTarget2D** Texture,
		TEnumAsByte<enum TextureFilter>* Filter);
	~FCohtmlRenderWrapper();

	cohtml::View* GetView() const;
	FRHITexture2D* GetTextureRHI() const;
	UTexture* GetTexture() const { return *Texture; }

	void BeginDestroy();
	bool IsReadyForFinishDestroy();
	void WaitForFinishDestroy();
	void FinishDestroy();

	void Resize(uint32 width, uint32 height);
	void Paint(FRHICommandListImmediate& list);

	void CreateView(const cohtml::ViewSettings& info, const FString& url);
	void RecreateView(const cohtml::ViewSettings& info, const FString& url);
	// Returns whether the View was Advanced and we need to issue paint
	bool Tick(float DeltaSeconds);

	bool IsReadyForBindings() const;
	bool HasRequestedView() const;
	bool IsTransparent() const;

	cohtml::ViewRenderer* GetViewRenderer() const;

	// TCircularQueue<uint32> FrameQueue member requires the object to be with alignment (PLATFORM_CACHE_LINE_SIZE)
	void* operator new(size_t Size)
	{
		return FMemory::Malloc(Size, PLATFORM_CACHE_LINE_SIZE);
	}

	void operator delete(void* Ptr)
	{
		FMemory::Free(Ptr);
	}

	void Paint_GameThread();
	FThreadSafeBool bPainted;

protected:

	cohtml::View* View;

private:
	void DestroyCurrentTexture();
	void ResizeOrRecreateTexture(int32 width, int32 height);
	void RecreateMSAATextureIfNeeded_RenderThread(uint32 Width, uint32 Height);
	void ResolveMSAATextureIfNeeded_RenderThread(FRHICommandListImmediate& CmdList);
	FRHITexture2D* GetRenderTarget();
	void CreateViewRenderer(cohtml::SystemRenderer* renderer, void* nativeTexture, void* nativeDepthStencil);
	bool IsReadyToCreateView() const;

	FRenderCommandFence ReleaseResourcesFence;
	unsigned PendingLayoutFence;

	cohtml::ViewRenderer* ViewRenderer;
	TSharedPtr<cohtml::IViewListener> ViewListener;
	TSharedPtr<cohtml::ITextInputHandler> TextInputHandler;
	FCohtmlSystemWrapperSharedPtr System;
	FCohtmlRendererHolderSharedPtr SystemRenderer;

	cohtml::ViewSettings RequestedInfo;
	FString RequestedURL;

	UTextureRenderTarget2D** Texture;
	// If we are rendering with MSAA enabled, this is null
	FRHITexture2D* RHITexture;
	// If we are rendering with MSAA disabled, the next two are null
	FTexture2DRHIRef MSAATexture;
	FTexture2DRHIRef MSAARenderTarget;
	TUniquePtr<class FCohStencilBuffer> DepthStencilTexture;
	TEnumAsByte<enum TextureFilter>* Filter;

	class IRenderingBackend* RenoirBackend;

	// Lock-free Queue, ThreadSafe for 2 threads, constructs with CapacityPlusOne
	TCircularQueue<uint32> FrameQueue;

	// Used to trigger re-draws after a certain amount of frames happened
	uint32 NeedsRedrawFrameCounter;
	uint32 MSAASampleCount;
	bool bHasReqView;
	bool bRegisteredBindings;
};