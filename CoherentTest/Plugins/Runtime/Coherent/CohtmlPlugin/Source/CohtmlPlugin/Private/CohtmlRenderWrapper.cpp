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
#include "CohtmlPluginPrivatePCH.h"
#include "CohtmlRenderWrapper.h"

#include "CohtmlPlugin.h"
#include "CohtmlDirectoryWatcher.h"
#include "CohtmlSettings.h"
#include "CohtmlSystem.h"
#include "CohtmlSystemHolder.h"
#include "cohtml/System.h"
#include "cohtml/Binding/Binding.h"
#include "cohtml/Binding/Binder.h"
#include "CohtmlFStringBinder.h"
#include "cohtml/Binding/EventHandler.h"

#include "CohTexture.h"
#include "CohStencilBuffer.h"

#include "SceneUtils.h"
#include "TextureResource.h"

#include "ICoherentRenderingPlugin.h"

typedef TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe> RendererPtr;

FCohtmlRenderWrapper::FCohtmlRenderWrapper(TSharedPtr<cohtml::IViewListener> viewListener,
	TSharedPtr<cohtml::ITextInputHandler> textInputHandler,
	UTextureRenderTarget2D** texture,
	TEnumAsByte<enum TextureFilter>* filter)
		: bPainted(false)
		, ViewListener(viewListener)
		, TextInputHandler(textInputHandler)
		, Texture(texture)
		, Filter(filter)
		, FrameQueue(3) //queue max 2 frames plus one item for detecting full/empty states
		, NeedsRedrawFrameCounter(0)
{
	View = nullptr;
	ViewRenderer = nullptr;
	RenoirBackend = nullptr;

	bHasReqView = false;
	bRegisteredBindings = false;

	auto Settings = GetDefault<UCohtmlSettings>();
	switch (Settings->MSAA)
	{
	case ECohtmlMSAA::MSAA_1x:
		MSAASampleCount = 1;
		break;
	case ECohtmlMSAA::MSAA_2x:
		MSAASampleCount = 2;
		break;
	case ECohtmlMSAA::MSAA_4x:
		MSAASampleCount = 4;
		break;
	default:
		check(false && "Unsupported number of samples for MSAA");
	}

	System = FCohtmlSystemHolder::CreateSystem();
	if (System.IsValid())
	{
		System->CreateSystemRenderer(&SystemRenderer);
	}
}

FCohtmlRenderWrapper::~FCohtmlRenderWrapper()
{

}

cohtml::View* FCohtmlRenderWrapper::GetView() const
{
	return View;
}

FRHITexture2D* FCohtmlRenderWrapper::GetTextureRHI() const
{
	return RHITexture;
}

bool FCohtmlRenderWrapper::IsReadyToCreateView() const
{
	return FCohtmlSystemHolder::IsReady();
}

void FCohtmlRenderWrapper::CreateView(const cohtml::ViewSettings& info, const FString& url)
{
	if (!IsReadyToCreateView() && !bHasReqView)
		return;

	if (!System.IsValid())
		return;

	bHasReqView = true;

	ResizeOrRecreateTexture(info.Width, info.Height);

	RequestedInfo = info;
	RequestedURL = url;
}

void FCohtmlRenderWrapper::RecreateView(const cohtml::ViewSettings& info, const FString& url)
{
	ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(
		DestroyViewRenderer,
		FCohtmlRenderWrapper*, Wrapper, this,
		{
			auto InnerViewRenderer = Wrapper->ViewRenderer;
			if (InnerViewRenderer)
			{
				auto DrawScope = Wrapper->RenoirBackend->MakeDrawScope(RHICmdList);
				InnerViewRenderer->Destroy();
				Wrapper->ViewRenderer = nullptr;
			}
		});
	ReleaseResourcesFence.BeginFence();
	if (View)
	{
#if WITH_EDITOR
		FCohtmlDirectoryWatcher::Get().OnViewDestroyed.ExecuteIfBound(View);
#endif
		View->Destroy();
		View = nullptr;
	}
	DestroyCurrentTexture();
	CreateView(info, url);
}

FRHITexture2D* FCohtmlRenderWrapper::GetRenderTarget()
{
	if (MSAASampleCount > 1)
	{
		return MSAARenderTarget.GetReference();
	}
	else
	{
		return RHITexture;
	}
}

void FCohtmlRenderWrapper::Resize(uint32 InWidth, uint32 InHeight)
{
	auto TexturePtr = *Texture;
	if (!View || (TexturePtr->SizeX == InWidth && TexturePtr->SizeY == InHeight))
		return;

	View->Resize(InWidth, InHeight);
	ResizeOrRecreateTexture(InWidth, InHeight);

	// We have to trigger a full re-draw the next+1 frame, because
	// otherwise our rendering happens before the texture gets cleared
	// This makes sure the RT has been cleared before we draw
	// TODO: think of a better way to fix this
	NeedsRedrawFrameCounter = 3;

	verify(System.IsValid());

	ENQUEUE_COHTML_RENDERING_COMMAND_FOURPARAMETER(SetViewRendererTexture,
		FCohtmlRenderWrapper*, Wrapper, this,
		uint32, Width, InWidth,
		uint32, Height, InHeight,
		RendererPtr, SysRenderer, SystemRenderer,
		{
			auto Resource = static_cast<FTextureRenderTarget2DResource*>((*Wrapper->Texture)->Resource);
			auto InnerViewRenderer = Wrapper->ViewRenderer;
			if (!Resource)
				COHTML_UE_LOG(Error, TEXT("Null Resource when trying to resize!"));
			if (InnerViewRenderer && Resource)
			{
				Wrapper->RenoirBackend = SysRenderer->GetBackend();

				Wrapper->RHITexture = Resource->GetTextureRHI().GetReference();
				Wrapper->RecreateMSAATextureIfNeeded_RenderThread(Width, Height);
				Wrapper->DepthStencilTexture.Reset(new FCohStencilBuffer(Width, Height, Wrapper->MSAASampleCount));

				auto DrawScope = Wrapper->RenoirBackend->MakeDrawScope(RHICmdList);
				InnerViewRenderer->SetRenderTarget(Wrapper->GetRenderTarget(), Wrapper->DepthStencilTexture.Get(), Width, Height, Wrapper->MSAASampleCount);
			}
		});
}

void FCohtmlRenderWrapper::DestroyCurrentTexture()
{
	if (!Texture)
	{
		return;
	}

	auto TexturePtr = *Texture;
	if (TexturePtr)
	{
		TexturePtr->RemoveFromRoot();

		if (TexturePtr->Resource)
		{
			TexturePtr->ReleaseResource();
		}
		TexturePtr->MarkPendingKill();
		*Texture = nullptr;
	}
}

void FCohtmlRenderWrapper::ResizeOrRecreateTexture(int32 width, int32 height)
{
	if (!Texture)
	{
		return;
	}

	if (!*Texture)
	{
		// create new texture and resource
		*Texture = NewObject<UTextureRenderTarget2D>(
			(UObject*)GetTransientPackage(),
			UTextureRenderTarget2D::StaticClass(),
			NAME_None,
			RF_Transient
			);
		auto TexturePtr = *Texture;
		TexturePtr->SizeX = width;
		TexturePtr->SizeY = height;
		TexturePtr->OverrideFormat = PF_R8G8B8A8;
#if defined(COHTML_UE4_416_SUPPORT)
		TexturePtr->bHDR = false;
#else
		TexturePtr->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
#endif
		TexturePtr->bForceLinearGamma = false;
		TexturePtr->ClearColor = FLinearColor(0, 0, 0, 0);
		TexturePtr->Filter = *Filter;
		TexturePtr->AddToRoot();
		TexturePtr->UpdateResource();
	}
	else
	{
		// reuse existing texture, only recreate resource
		auto TexturePtr = *Texture;
		TexturePtr->SizeX = width;
		TexturePtr->SizeY = height;
		TexturePtr->UpdateResource();
	}
}

void FCohtmlRenderWrapper::RecreateMSAATextureIfNeeded_RenderThread(uint32 Width, uint32 Height)
{
	if (MSAASampleCount == 1)
	{
		return;
	}
	MSAARenderTarget.SafeRelease();
	MSAATexture.SafeRelease();

	FRHIResourceCreateInfo CreateInfo;
	RHICreateTargetableShaderResource2D(
		Width,
		Height,
		PF_R8G8B8A8,
		1,
		0,
		TexCreate_RenderTargetable,
		false,
		CreateInfo,
		MSAARenderTarget,
		MSAATexture,
		MSAASampleCount
		);

	// Release the texture that UTextureRenderTarget2D created and assign the MSAA one to the UTextureRenderTarget2D
	auto TexturePtr = *Texture;
	RHIUpdateTextureReference(TexturePtr->TextureReference.TextureReferenceRHI, MSAATexture.GetReference());
	RHITexture = MSAATexture.GetReference();
}

void FCohtmlRenderWrapper::Paint(FRHICommandListImmediate& CmdList)
{
	if (ViewRenderer)
	{
		check(RenoirBackend);
		auto drawScope = RenoirBackend->MakeDrawScope(CmdList);

		uint32 CurrentFrame;
		bool bQueueNotEmpty = FrameQueue.Dequeue(CurrentFrame);
		check(bQueueNotEmpty);

		ViewRenderer->Paint(CurrentFrame, true);
		ResolveMSAATextureIfNeeded_RenderThread(CmdList);

		bPainted = true;
	}
}

void FCohtmlRenderWrapper::ResolveMSAATextureIfNeeded_RenderThread(FRHICommandListImmediate& CmdList)
{
	if (MSAASampleCount == 1)
	{
		return;
	}
	// TODO: Only resolve if something was actually painted
	FResolveParams ResolveParams;
	CmdList.CopyToResolveTarget(MSAARenderTarget.GetReference(),
		MSAATexture.GetReference(),
#if defined(COHTML_UE4_419_SUPPORT)
		true,
#endif
		ResolveParams);
}

void FCohtmlRenderWrapper::CreateViewRenderer(
	cohtml::SystemRenderer* renderer,
	void* texture, void* depthStencil)
{
	auto TexturePtr = *Texture;
	cohtml::ViewRendererSettings settings;
	ViewRenderer = renderer->CreateViewRenderer(View, settings);
	ViewRenderer->SetRenderTarget(
		texture,
		depthStencil,
		TexturePtr->SizeX,
		TexturePtr->SizeY,
		MSAASampleCount);
}

bool FCohtmlRenderWrapper::HasRequestedView() const
{
	return bHasReqView;
}

void FCohtmlRenderWrapper::Paint_GameThread()
{
	ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(
		PaintCohtmlView,
		FCohtmlRenderWrapper*, Wrapper, this,
		{
			auto& ConsoleCommands = FCohtmlPlugin::Get().GetConsoleCommands();
			CONDITIONAL_SCOPE_CYCLE_COUNTER(STAT_CohtmlTotalCPU, ConsoleCommands.IsViewProfiled(Wrapper->View));
			CONDITIONAL_SCOPE_CYCLE_COUNTER(STAT_CohtmlPaint, ConsoleCommands.IsViewProfiled(Wrapper->View));
			Wrapper->Paint(RHICmdList);
		});
}

bool FCohtmlRenderWrapper::Tick(float DeltaSeconds)
{
	if (!IsReadyToCreateView())
		return false;

	if (!ACohtmlSystem::IsActorTicking())
	{
		// In the absence of a system actor, we are running in the editor
		// The first render wrapper to reach this code becomes the fallback ticker;
		// If it dies (the editor is closed / the UMG widget is removed) it will reset the fallback ticker in Destroy.
		if (ACohtmlSystem::IsFallbackTicker(this))
		{
			System->GetSystemPtr()->Advance(System->GetCurrentTimepoint());
		}
	}

	if (View)
	{
		if (NeedsRedrawFrameCounter)
		{
			if (NeedsRedrawFrameCounter == 1)
			{
				View->ContinuousRepaint(true);
			}
			--NeedsRedrawFrameCounter;
		}
		{
			auto& ConsoleCommands = FCohtmlPlugin::Get().GetConsoleCommands();
			CONDITIONAL_SCOPE_CYCLE_COUNTER(STAT_CohtmlTotalCPU, ConsoleCommands.IsViewProfiled(View));
			CONDITIONAL_SCOPE_CYCLE_COUNTER(STAT_CohtmlViewAdvance, ConsoleCommands.IsViewProfiled(View));
			FrameQueue.Enqueue(View->Advance(System->GetCurrentTimepoint()));
			View->ContinuousRepaint(false);
		}

		// We are not enqueuing Paint command now, as it will block the RenderThread to wait for
		// Layout/RecordRendering on the worker thread. Just return whether we have advanced and
		// the calling code will issue Paint command at later time to give a chance for worker thread
		// to finish
		return true;
	}
	else
	{
		if (bHasReqView && Texture && *Texture && (*Texture)->Resource)
		{
			if (!System.IsValid() || !SystemRenderer.IsValid())
				return false;

			auto textureResource = static_cast<FTextureRenderTarget2DResource*>((*Texture)->Resource);
			if (!textureResource)
			{
				COHTML_UE_LOG(Error, TEXT("Unable to get texture resource for View!"));
				return false;
			}

			RequestedInfo.Listener = ViewListener.Get();
			RequestedInfo.TextInputHandler = TextInputHandler.Get();

			View = System->CreateView(RequestedInfo);
			check(View);
			if (!RequestedURL.IsEmpty())
			{
				View->LoadURL(TCHAR_TO_UTF8(*RequestedURL));
			}
#if WITH_EDITOR
			FCohtmlDirectoryWatcher::Get().OnViewCreated.ExecuteIfBound(View, System->GetSystemPtr());
#endif

			ENQUEUE_COHTML_RENDERING_COMMAND_TWOPARAMETER(
				CreateCohtmlViewRenderer,
				FCohtmlRenderWrapper*, Wrapper, this,
				RendererPtr, SysRenderer, SystemRenderer,
				{
					auto Resource = static_cast<FTextureRenderTarget2DResource*>((*Wrapper->Texture)->Resource);

					Wrapper->RHITexture = Resource->GetTextureRHI().GetReference();
					auto Width = Resource->GetTextureRHI()->GetSizeX();
					auto Height = Resource->GetTextureRHI()->GetSizeY();
					Wrapper->RecreateMSAATextureIfNeeded_RenderThread(Width, Height);
					Wrapper->DepthStencilTexture.Reset(new FCohStencilBuffer(Width, Height, Wrapper->MSAASampleCount));

					Wrapper->CreateViewRenderer(SysRenderer->GetRenderer(), Wrapper->GetRenderTarget(), Wrapper->DepthStencilTexture.Get());

					Wrapper->RenoirBackend = SysRenderer->GetBackend();
				});
		}
		return false;
	}
}

void FCohtmlRenderWrapper::BeginDestroy()
{
	ACohtmlSystem::NotifyPossibleFallbackTickerDestroyed(this);
	ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(
		DestroyViewRenderer,
		FCohtmlRenderWrapper*, Wrapper, this,
		{
			auto InnerViewRenderer = Wrapper->ViewRenderer;
			if (InnerViewRenderer)
			{
				auto DrawScope = Wrapper->RenoirBackend->MakeDrawScope(RHICmdList);
				InnerViewRenderer->Destroy();
				Wrapper->ViewRenderer = nullptr;
			}
		});
	ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(
		DestroyRenderer,
		FCohtmlRendererHolderSharedPtr*, RendererHolder, &SystemRenderer,
		{
			RendererHolder->Reset();
		});
	ReleaseResourcesFence.BeginFence();
}

bool FCohtmlRenderWrapper::IsReadyForFinishDestroy()
{
	return ReleaseResourcesFence.IsFenceComplete();
}

void FCohtmlRenderWrapper::WaitForFinishDestroy()
{
	ReleaseResourcesFence.Wait();
}

void FCohtmlRenderWrapper::FinishDestroy()
{
	if (View)
	{
#if WITH_EDITOR
		FCohtmlDirectoryWatcher::Get().OnViewDestroyed.ExecuteIfBound(View);
#endif
		View->Destroy();
		View = nullptr;
	}
	DestroyCurrentTexture();
}

cohtml::ViewRenderer* FCohtmlRenderWrapper::GetViewRenderer() const
{
	return ViewRenderer;
}
