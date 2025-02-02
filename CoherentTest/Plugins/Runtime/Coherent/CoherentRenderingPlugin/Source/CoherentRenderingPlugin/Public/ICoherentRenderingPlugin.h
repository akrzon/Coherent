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

#include <Modules/ModuleManager.h>
#include <RenoirBackend/RendererBackend.h>
#include <RenoirBackend/ClickThroughProvider.h>

; // This semicolon is a workaround for the Shipping build configuration

namespace renoir
{
	class IRenderingLibrary;
}

class FRHICommandListImmediate;

class IRenderingBackend : public renoir::RendererBackend, public renoir::ClickThroughProvider
{
protected:
	struct COHERENTRENDERINGPLUGIN_API FCohRenoirBackendCmdListScope
	{
		FCohRenoirBackendCmdListScope(IRenderingBackend* backend, FRHICommandListImmediate& list);
		~FCohRenoirBackendCmdListScope();

		IRenderingBackend* Backend;
	};
public:
	FCohRenoirBackendCmdListScope MakeDrawScope(FRHICommandListImmediate& list)
	{
		return FCohRenoirBackendCmdListScope(this, list);
	}

	DECLARE_DELEGATE_OneParam(FOnLiveViewTextureDestroyed, const FString&)
	FOnLiveViewTextureDestroyed OnLiveViewTextureDestroyed;

	DECLARE_DELEGATE_OneParam(FOnLiveViewReachedBackend, const FString&)
	FOnLiveViewReachedBackend OnLiveViewReachedBackend;
};

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules
 * within this plugin.
 */
class ICoherentRenderingPlugin : public IModuleInterface
{
public:
	virtual renoir::IRenderingLibrary* GetLibrary() = 0;

	virtual IRenderingBackend* GetBackend_RenderThread() = 0;

	virtual void ReleaseRenderingLibrary() = 0;

#if WITH_EDITOR
	virtual void RegisterSettings() = 0;
#endif

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ICoherentRenderingPlugin& Get()
	{
		return FModuleManager::GetModuleChecked< ICoherentRenderingPlugin >("CoherentRenderingPlugin");
	}

	static inline ICoherentRenderingPlugin& Load()
	{
		return FModuleManager::LoadModuleChecked< ICoherentRenderingPlugin >("CoherentRenderingPlugin");
	}


	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "CoherentRenderingPlugin" );
	}
};

