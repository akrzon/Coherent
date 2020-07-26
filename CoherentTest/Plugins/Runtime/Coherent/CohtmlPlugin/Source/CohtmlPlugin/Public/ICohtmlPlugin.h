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

#include <Modules/ModuleManager.h>
; // This semicolon is a workaround for the Shipping build configuration

namespace cohtml
{
class ILocalizationManager;
class View;
class IInputProxy;
class ITextTransformationManager;
}
class FCohtmlVirtualKeyboardEntry;
struct FURLWithFallbacks;
struct FOverridableFallbackFormat;


/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules
 * within this plugin.
 */
class ICohtmlPlugin : public IModuleInterface
{
public:
	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ICohtmlPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<ICohtmlPlugin>("CohtmlPlugin");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("CohtmlPlugin");
	}

	/**
	* A delegate that is fired on the FIRST request for each resource.
	* Will not be called a second time when the fallback resource is requested.
	* Will not be called twice if we have two Views sharing the resource.
	*
	* @param A populated and modifiable structure, containing the URL and all fallbacks
	*/
	DECLARE_DELEGATE_OneParam(FOnURLRequest, FURLWithFallbacks&);

	/**
	* Override this to change the fallback paths for image resources.
	* By changing the contents of the referenced parameter you can inject your own fallback paths,
	* add/remove fallbacks dynamically, etc. You can even change the URL that is currently being loaded.
	* The StartupModule method of your GameModule class is a convenient place to bind your function.
	*/
	COHTMLPLUGIN_API static FOnURLRequest OnURLRequest;

	/**
	* A delegate which you can use for control over the image fallback formats
	*
	* @param A populated and modifiable array, which contains all of the image
	* fallback formats from the Editor settings. Can be empty.
	*/
	DECLARE_DELEGATE_OneParam(FOnGetFallbackFormats, TArray<FOverridableFallbackFormat>&);

	/**
	* Use this to inject your own Fallback Formats. Useful for anything that the similar
	* editor option lacks, such as having different fallbacks for different platforms or deciding
	* dynamically which fallbacks you want to use during startup. Will get called once during the
	* initialization of the Cohtml system
	* The StartupModule method of your GameModule class is a convenient place to bind your function.
	*/
	COHTMLPLUGIN_API static FOnGetFallbackFormats OnGetFallbackFormats;

	/**
	* A delegate that is fired to receive your custom ILocalizationManager implementation.
	*
	* @return A pointer to your LocalizationManager object.
	*/
	DECLARE_DELEGATE_RetVal(cohtml::ILocalizationManager*, FOnGetLocalizationManager);

	/**
	* Use this to override the default Localization Manager. Bind this
	* delegate to a function that returns a pointer to your own implementation.
	* The binding must be done before the CohtmlSystem initialization and the implementation must
	* adhere to the restrictions outlined in the ILocalizationManager interface header.
	* The StartupModule method of your GameModule class is a convenient place to bind your function.
	*/
	COHTMLPLUGIN_API static FOnGetLocalizationManager OnGetLocalizationManager;

	/**
	* A delegate that is fired when a virtual keyboard should be shown on the screen.
	* This gives control over whether to show virtual keyboard for given platform,
	* the options given to the VirtualKeyboardEntry, and the actual implementation
	* of the function showing the virtual keyboard.
	*/
	DECLARE_DELEGATE_FourParams(FOnShowVirtualKeyboard, TSharedPtr<FCohtmlVirtualKeyboardEntry>& /*OutCohtmlVirtualKeyboardEntry*/,
		int32 /*UserIndex*/, cohtml::View* /*OwningView*/, cohtml::IInputProxy* /*InputProxy*/);

	/**
	* Use this to override the default ShowVirtualKeyboard behavior. Bind this delegate to a function
	* that creates new TSharedPtr of FCohtmlVirtualKeyboardEntry or inherited class (should be stored
	* inside the supplied reference of the same type) and showing the virtual keyboard using that
	* virtual keyboard entry.
	* To disable virtual keyboard for specific platform, just leave the implementation of the bound
	* function empty for the given platform.
	* The binding must be done before the CohtmlSystem initialization.
	* The StartupModule method of your GameModule class is a convenient place to bind your function.
	*/
	COHTMLPLUGIN_API static FOnShowVirtualKeyboard OnShowVirtualKeyboard;

	/**
	* A delegate that is fired to receive your custom ITextTransformationManager implementation.
	*
	* @return A pointer to your TextTransformationManager object.
	*/
	DECLARE_DELEGATE_RetVal(cohtml::ITextTransformationManager*, FOnGetTextTransformationManager);

	/**
	* Use this to override the default Text Transformation Manager. Bind a function that returns a
	* pointer to your own implementation. The binding must be done before the CohtmlSystem initialization
	* and the implementation must adhere to the restrictions outlined in the ITextTransformationManager
	* interface header. The StartupModule method of your GameModule class is a convenient place to bind
	* your function.
	*/
	COHTMLPLUGIN_API static FOnGetTextTransformationManager OnGetTextTransformationManager;
};
