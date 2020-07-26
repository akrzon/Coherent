
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

#include "CohtmlSettings.generated.h"

#if PLATFORM_XBOXONE
#define DEFAULT_DEVTOOLS_PORT 4601
#else
#define DEFAULT_DEVTOOLS_PORT 9444
#endif

/**
 * Auxiliary enum for log severities that's visible in the Editor.
 * It should mirror the cohtml::Logging::Severity one.
 */
UENUM(meta=(DisplayName = "Prysm Settings Severity"))
enum class ECohtmlSettingsSeverity : uint8
{
	Trace,
	Debug,
	Info,
	Warning,
	AssertFailure,
	Error,
};

UENUM(BlueprintType, meta=(DisplayName = "Prysm MSAA"))
enum class ECohtmlMSAA : uint8
{
	MSAA_1x UMETA(DisplayName="1x"),
	MSAA_2x UMETA(DisplayName="2x"),
	MSAA_4x UMETA(DisplayName="4x")
};

UENUM(BlueprintType, meta = (DisplayName = "Prysm image formats"))
enum class ECohtmlImageFormat : uint8
{
	PNG,
	TGA,
	JPEG,
	PSD,
	SVG,
	DDS,
	BMP,
	ASTC,
	PKM,
	KTX
};


USTRUCT()
struct FSingleFormatFallbacks
{
	GENERATED_BODY()

public:
	/** This specifies the base format for which we want to add fallbacks */
	UPROPERTY(EditAnywhere, Category = Settings, meta=(DisplayName= "Base format"))
	ECohtmlImageFormat BaseFormat;

	/** This array specifies the possible fallback formats of the base format
	*   and the order in which they will be tried.
	*/
	UPROPERTY(EditAnywhere, Category = Settings, meta=(DisplayName = "Permitted fallback formats"))
	TArray<ECohtmlImageFormat> PossibleFallbacks;
};

/**
 * Implements the settings for the Prysm plugin.
 */
UCLASS(config = Engine, defaultconfig, meta=(DisplayName = "Prysm Settings"))
class COHTMLPLUGIN_API UCohtmlSettings : public UObject
{
	GENERATED_UCLASS_BODY()

	/// Enables live reload for all Prysm components and widgets. When enabled
	/// the plugin will watch all files inside uiresources folder that are loaded by
	/// your UI via coui:// and reload them should any of them change. Works only in PIE.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	bool EnableLiveReload;

	/// The port on which to run Prysm's dev tools. Use the dev tools to debug, profile and inspect your UI.
	/// Changing this option requires restarting the UE4 editor / game.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	int32 DevToolsPort;

	/// Enables localization via the data-l10n-id attribute. Any HTML element
	/// with the attribute data-l10n-id="Namespace.Key" will get its text content
	/// translated according to UE4's localization settings.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	bool EnableLocalization;

	/// Whether to handle input events that have reached the HTML Body. If a click/touch
	/// input event on the HTML Body is left unhandled by the UI and no other widget handles
	/// that event, it will be handled by the engine itself.
	UPROPERTY(Config, EditAnywhere, Category = "Settings|Input", Meta = (DisplayName = "Handle Input On HTML Body"))
	bool HandleInputOnHTMLBody;

	/// Any HTML Node or it's parent nodes that have one of these CSS classes are marked
	/// as transparent input for the UI, meaning that click/touch events on such a node
	/// will be left unhandled by the UI and if no other widget handles that event, it
	/// will be handled by the engine itself.
	UPROPERTY(Config, EditAnywhere, Category = "Settings|Input", Meta = (DisplayName = "Input Transparent CSS Classes"))
	TArray<FString> InputTransparentCssClasses;

	/// Sets how many pixels one mousewheel tick is worth when scrolling.
	/// Defaults to 40.
	UPROPERTY(Config, EditAnywhere, Category = Settings, Meta = (DisplayName = "Wheel scroll scale"))
	float ScrollDelta;

	/// Allows warnings in the Editor
	/// to be printed on-screen
	UPROPERTY(Config, EditAnywhere, Category = "Settings|Logging")
	bool ShowWarningsOnScreen;

	/// Sets the log severity of Prysm.
	/// Changing this option requires restarting the UE4 editor / game.
	UPROPERTY(Config, EditAnywhere, Category = "Settings|Logging")
	ECohtmlSettingsSeverity LogSeverity;

	/// Whether to respect the title safe zone when drawing the HUD
	/// using ACohtmlGameHUD.
	/// Setting it to false will cause your HUD to take all the space
	/// on your screen bounded by the game's aspect ratio
	/// instead of only the zone deemed safe by the platform.
	UPROPERTY(Config, EditAnywhere, Category = "Settings|HUD")
	bool bRespectTitleSafeZone;

	/// Whether to respect the letterboxing area when drawing the HUD
	/// using ACohtmlGameHUD.
	/// Setting it to false will cause your HUD to render even on the
	/// black bars caused by letterboxing.
	UPROPERTY(Config, EditAnywhere, Category = "Settings|HUD")
	bool bRespectLetterboxing;

	/// Set to true to keep the UI running even while the game is paused.
	UPROPERTY(Config, EditAnywhere, Category = "Settings|Miscellaneous")
	bool TickWhileGameIsPaused;

	/// Sets the number of samples Prysm uses to apply MSAA
	/// to components and widgets.
	UPROPERTY(Config)
	ECohtmlMSAA MSAA;

	/// Defines an array where every item specifies a base image format and its suggested fallbacks.
	/// Any time Prysm encounters an image from the base format, it will *INSTEAD*
	/// request an image with the first available fallback format, doing so
	/// until it finds an image or until it exhausts the full list or formats.
	/// You will NOT receive a request for the original image (with the base format).
	/// The request will instead contain the URL of the first specified fallback.
	/// You can provide your custom fallback formats dynamically by binding the
	/// ICohtmlPlugin::OnGetFallbackFormats delegate. This is especially useful for
	/// per-platform project fallback control. If you want to inject your own fallback
	/// URLs dynamically you can bind the ICohtmlPlugin::OnURLRequest delegate.
	/// Examples of the overrides can be found in CoherentSample.cpp and the official documentation.
	UPROPERTY(Config, EditAnywhere, Category = Settings, Meta = (DisplayName = "Fallback formats"))
	TArray<FSingleFormatFallbacks> FallbacksForAllFormats;
};
