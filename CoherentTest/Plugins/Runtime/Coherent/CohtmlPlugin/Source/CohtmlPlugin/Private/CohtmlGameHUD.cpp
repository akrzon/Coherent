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
#include "CohtmlGameHUD.h"

#include "cohtml/View.h"

#include "cohtml/Binding/EventHandler.h"
#include "CohtmlFStringBinder.h"
#include "CohtmlSettings.h"

#include "Engine/Canvas.h"
#include "GenericPlatform/GenericPlatformMath.h"

ACohtmlGameHUD::ACohtmlGameHUD(
	const FObjectInitializer& PCIP)
	: Super(PCIP)
	, CohtmlHUD(nullptr)
	, bShouldChangeURL(false)
	, bViewRequested(false)
	, bCanvasNeedsUpdate(false)
	, InputPadding(0, 0)
{
	CohtmlHUDInternal = PCIP.CreateDefaultSubobject<UCohtmlHUD>(this, TEXT("CohtmlHUD"));
	Info.Width = 1;
	Info.Height = 1;
}

void ACohtmlGameHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

#if !defined(COHTML_UE4_419_SUPPORT)
	OnSafeFrameChangedHandle = FCoreDelegates::OnSafeFrameChangedEvent.AddUObject(this, &ACohtmlGameHUD::RetrieveSafeZonePad);
	OnViewportResizedHandle = FViewport::ViewportResizedEvent.AddUObject(this, &ACohtmlGameHUD::OnViewportResized);

	RetrieveSafeZonePad();
#endif
}

ACohtmlGameHUD::~ACohtmlGameHUD()
{
#if !defined(COHTML_UE4_419_SUPPORT)
	FViewport::ViewportResizedEvent.Remove(OnViewportResizedHandle);
	FCoreDelegates::OnSafeFrameChangedEvent.Remove(OnSafeFrameChangedHandle);
#endif
}

FIntPoint ACohtmlGameHUD::ComputeCanvasDrawableSize()
{
	// One would expect the drawable size to be Canvas->ClipX / ClipY but this is not the case
	// ClipSize = UnsafeSize - Padding whereas it should be ClipSize = UnsafeSize - 2 * Padding
	// so we need to subtract the padding manually
	const FIntPoint SafeToUnsafeZonePadding(Canvas->UnsafeSizeX - Canvas->SizeX, Canvas->UnsafeSizeY - Canvas->SizeY);
#if defined(COHTML_UE4_419_SUPPORT)
	return FIntPoint(Canvas->ClipX - SafeToUnsafeZonePadding.X, Canvas->ClipY - SafeToUnsafeZonePadding.Y);
#else
	// The current UE4 implementation has a slight bug that emerges only if either dimension of the game's resolution is
	// more than (DisplaySize - SafeZonePad). UE4 clamps the SafeSize to this size
	// but that's not really the correct behaviour because the safe zone should be a percentage of the current resolution
	// and not the display device capabilities.
	// To compensate, increase the size here by the respective amount that UE4 cut off
	const int32 CompensationX = FMath::Max(0, Canvas->UnsafeSizeX + Canvas->SafeZonePadX - Canvas->CachedDisplayWidth);
	int32 CompensationY = FMath::Max(0, Canvas->UnsafeSizeY + Canvas->SafeZonePadY - Canvas->CachedDisplayHeight);

#if PLATFORM_ANDROID
	// The CanvasDrawableSize on Android is smaller than it should be, so we need to add PadY.
	CompensationY += PadY;
#endif

	const FIntPoint Compensation(CompensationX * 2, CompensationY * 2);
	const FIntPoint ClipSize(Canvas->ClipX, Canvas->ClipY);
	// There's a hidden bug in here - UE4 computes the safe zone on top of the viewport resolution,
	// and NOT on the game resolution as it's supposed to. If you have a big safe zone on a big resolution
	// (how big depends on the aspect ratio, one example is safe zone < 0.715 on 4K with AR >= 21/9)
	// you'll get a big empty Y space. Since it is VERY unlikely that anyone will never have a screen with
	// safe zone of < 0.715 AND support for 4K, we can safely ignore it.
	return ClipSize - SafeToUnsafeZonePadding + Compensation;
#endif
}

FIntPoint ACohtmlGameHUD::ComputeCorrectHUDSize()
{
	const auto Settings = GetDefault<UCohtmlSettings>();
	const FIntPoint ViewportSize = GEngine && GEngine->GameViewport ? GEngine->GameViewport->Viewport->GetSizeXY() : FIntPoint(Canvas->ClipX, Canvas->ClipY);

#if !defined(COHTML_UE4_419_SUPPORT)
	const int32 SafeZonePadX = FGenericPlatformMath::CeilToInt(CachedSafeZonePad.Left + CachedSafeZonePad.Right);
	const int32 SafeZonePadY = FGenericPlatformMath::CeilToInt(CachedSafeZonePad.Top + CachedSafeZonePad.Bottom);
#endif

	const int32 LetterBoxPadX = ViewportSize.X - Canvas->UnsafeSizeX;
	const int32 LetterBoxPadY = ViewportSize.Y - Canvas->UnsafeSizeY;

#if !defined(COHTML_UE4_419_SUPPORT)
	const int32 PadX = FMath::Max(LetterBoxPadX, SafeZonePadX);
	// PadY is a member so we can calculate it once per draw but also use it in ComputeCanvasDrawableSize
	PadY = FMath::Max(LetterBoxPadY, SafeZonePadY);
#endif

	// The interactions between the safe zone and letterboxing are quite complex
	// Split the implementation in 4 cases to simplify
	if (Settings->bRespectTitleSafeZone && Settings->bRespectLetterboxing)
	{
		// Respect both
#if defined(COHTML_UE4_419_SUPPORT)
		const FIntPoint SafeToUnsafeZonePadding(Canvas->UnsafeSizeX - Canvas->SizeX, Canvas->UnsafeSizeY - Canvas->SizeY);

		InputPadding.X = SafeToUnsafeZonePadding.X;
		InputPadding.Y = SafeToUnsafeZonePadding.Y;

		return ComputeCanvasDrawableSize();
#else
		InputPadding.X = FMath::Max(0.0f, CachedSafeZonePad.Left - LetterBoxPadX / 2);
		InputPadding.Y = FMath::Max(0.0f, CachedSafeZonePad.Top - LetterBoxPadY / 2);

		return FIntPoint(ViewportSize.X - PadX, ViewportSize.Y - PadY);
#endif
	}
	else if (!Settings->bRespectTitleSafeZone && Settings->bRespectLetterboxing)
	{
		// Ignore safe zone, respect letterboxing
		InputPadding.X = 0;
		InputPadding.Y = 0;

		return FIntPoint(Canvas->UnsafeSizeX, Canvas->UnsafeSizeY);
	}
	else if (Settings->bRespectTitleSafeZone && !Settings->bRespectLetterboxing)
	{
		// Respect safe zone, ignore letterboxing
#if defined(COHTML_UE4_419_SUPPORT)
		InputPadding.X = FMath::Max(0, Canvas->SafeZonePadX) - LetterBoxPadX / 2;
		InputPadding.Y = FMath::Max(0, Canvas->SafeZonePadY) - LetterBoxPadY / 2;

		return FIntPoint(ViewportSize.X - 2 * Canvas->SafeZonePadX, ViewportSize.Y - 2 * Canvas->SafeZonePadY);
#else
		InputPadding.X = FMath::Max(0.0f, CachedSafeZonePad.Left) - LetterBoxPadX / 2;
		InputPadding.Y = FMath::Max(0.0f, CachedSafeZonePad.Top) - LetterBoxPadY / 2;

		return FIntPoint(ViewportSize.X - SafeZonePadX, ViewportSize.Y - SafeZonePadY);
#endif
	}
	else
	{
		// Ignore safe zone, ignore letterboxing
		InputPadding.X = -LetterBoxPadX / 2;
		InputPadding.Y = -LetterBoxPadY / 2;
		return ViewportSize;
	}
}

void ACohtmlGameHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CohtmlHUD)
	{
		if (bCanvasNeedsUpdate)
		{
			UpdateCanvasData();
		}

		auto View = CohtmlHUD->GetView();
		if (!View && !CohtmlHUD->HasRequestedView() && CohtmlHUD->IsReadyToCreateView())
		{
			CohtmlHUD->CreateHUDView(Info, URL);
			bViewRequested = true;
		}
		FIntPoint ProperViewSize = ComputeCorrectHUDSize();
		FIntPoint CanvasDrawableSize = ComputeCanvasDrawableSize();
		FIntPoint ProperOffset = (CanvasDrawableSize - ProperViewSize) / 2;

		if (View)
		{
			// check that the size matches
			auto TexturePtr = CohtmlHUD->Texture;
			if (TexturePtr->SizeX != ProperViewSize.X
				|| TexturePtr->SizeY != ProperViewSize.Y)
			{
				CohtmlHUD->Resize(ProperViewSize.X, ProperViewSize.Y);
			}
			if (bShouldChangeURL)
			{
				View->LoadURL(TCHAR_TO_UTF8(*URL));
				bShouldChangeURL = false;
			}
		}
		CohtmlHUD->DrawHUD(Canvas, ProperOffset.X, ProperOffset.Y);
	}
}

UCohtmlHUD* ACohtmlGameHUD::GetCohtmlHUD() const
{
	return CohtmlHUDInternal;
}

void ACohtmlGameHUD::SetupView(const FString& PageUrl, bool bEnableComplexCSSSupport, bool bDelayedUpdate)
{
	CohtmlHUD = CohtmlHUDInternal;
	if (URL != PageUrl)
	{
		URL = PageUrl;
		bShouldChangeURL = bViewRequested;
	}
	CohtmlHUD->bEnableComplexCSSSupport = bEnableComplexCSSSupport;
	CohtmlHUD->EnableDelayedUpdate(bDelayedUpdate);
}

#if !defined(COHTML_UE4_419_SUPPORT)
void ACohtmlGameHUD::OnViewportResized(FViewport* Viewport, uint32)
{
	RetrieveSafeZonePad();
}

void ACohtmlGameHUD::RetrieveSafeZonePad()
{
	bool bIsViewportValid = GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport;
	if (!bIsViewportValid && !Canvas)
	{
		return;
	}

	// This calls the OS API to obtain display information which can be quite slow and should be used only when
	// necessary (i.e. on FViewport::ViewportResizedEvent and FCoreDelegates::OnSafeFrameChangedEvent)
#if !defined(COHTML_UE4_420_SUPPORT)
	// From UE 4.21 Epic are caching this value, so we need to trigger a rebuild of the CachedDisplayMetrics or
	// we will get old data.
	FDisplayMetrics DisplayMetrics;
	FSlateApplication::Get().GetDisplayMetrics(DisplayMetrics);
#endif
	if (Canvas)
	{
		UpdateCanvasData();
	}
	else
	{
		bCanvasNeedsUpdate = true;
	}

	const FIntPoint ViewportSize = bIsViewportValid ? GEngine->GameViewport->Viewport->GetSizeXY() : FIntPoint(Canvas->UnsafeSizeX, Canvas->UnsafeSizeY);
	FSlateApplication::Get().GetSafeZoneSize(CachedSafeZonePad, FIntPoint(ViewportSize.X, ViewportSize.Y));
}

void ACohtmlGameHUD::UpdateCanvasData()
{
	Canvas->Update();
	Canvas->UpdateSafeZoneData();
	bCanvasNeedsUpdate = false;
}
#endif
