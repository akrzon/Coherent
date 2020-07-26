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

#include "GameFramework/HUD.h"

#include "cohtml/View.h"

#include "CohtmlBackwardsCompatibility.h"

#include "Layout/Margin.h"
#include "UnrealClient.h"

#include "CohtmlGameHUD.generated.h"

class UCohtmlHUD;

UCLASS(MinimalAPI, meta=(DisplayName = "Prysm GameHUD"))
class ACohtmlGameHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
public:
	COHTMLPLUGIN_API virtual void PostInitializeComponents() override;

	COHTMLPLUGIN_API virtual ~ACohtmlGameHUD();

	/** Primary draw call for the HUD */
	COHTMLPLUGIN_API virtual void DrawHUD() override;

	/** Obtains a pointer to the underlying Prysm HUD */
	COHTMLPLUGIN_API class UCohtmlHUD* GetCohtmlHUD() const;

	UFUNCTION(BlueprintCallable, Category = "Prysm", meta = (DisplayName = "Setup View"))
	COHTMLPLUGIN_API void SetupView(const FString& PageUrl, bool bEnableComplexCSSSupport = true, bool bDelayedUpdate = false);

	const FIntPoint GetInputPadding() { return InputPadding; }

protected:
	// Instead of using this pointer directly, use GetCohtmlHUD() method.
	UPROPERTY(BlueprintReadOnly, Category = "HUD", meta = (DisplayName = "Prysm HUD"))
	UCohtmlHUD* CohtmlHUD;

private:
	// After renaming the plugin BP's were broken, because their c-tor was
	// stomping the pointer of CohtmlHUD. The work around was to create another
	// pointer to CothmlHUD.
	UPROPERTY()
	UCohtmlHUD* CohtmlHUDInternal;

	FIntPoint ComputeCanvasDrawableSize();
	FIntPoint ComputeCorrectHUDSize();

	cohtml::ViewSettings Info;
	FString URL;
	// Whether we need to change the hud's page after creation
	// This should only ever be set to true if DrawHUD is called before SetupView
	bool bShouldChangeURL;
	bool bViewRequested;
	bool bCanvasNeedsUpdate;
	// Used to correctly calculate input when we have letterboxing and / or safezones enabled
	FIntPoint InputPadding;

#if !defined(COHTML_UE4_419_SUPPORT)
	// In UE 4.20 calling GetSafeZonePad every frame is a very expensive operation and we
	// need to cache the result and call it only on resize and safe zones changed events.
	// In UE 4.21 Epic are caching it internally but we still can't call it every frame as they are
	// not recalculating it when safe zone settings are changed on the game console (PS4 for example)
	void OnViewportResized(FViewport* Viewport, uint32);
	void RetrieveSafeZonePad();
	void UpdateCanvasData();

	FMargin CachedSafeZonePad;
	int32 PadY; // requred to compensate for smaller CanvasDrawableSizeY on Android

	FDelegateHandle OnViewportResizedHandle;
	FDelegateHandle OnSafeFrameChangedHandle;
#endif
};
