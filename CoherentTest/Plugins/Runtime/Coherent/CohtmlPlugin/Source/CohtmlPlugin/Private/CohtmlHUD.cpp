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
#include "CohtmlHUD.h"

#include "CohtmlSettings.h"
#include "CohtmlSystemHolder.h"

#include "CohtmlAssetReferencer.h"

#include <Materials/MaterialInstanceDynamic.h>
#include <CanvasItem.h>
#include <Engine/Canvas.h>
#include <GameFramework/PlayerController.h>
#include <Engine/LocalPlayer.h>

#define HUD_TEXTURE_PARAM "UIHUDTexture"

UCohtmlHUD::UCohtmlHUD(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	bWantsInitializeComponent = true;
	HUDMaterialInstance = nullptr;
	HUDMaterialName = CohtmlAssetReferences::HUDMaterial();
	HUDMaterial = Cast<UMaterial>(HUDMaterialName.TryLoad());
}

void UCohtmlHUD::InitializeComponent()
{
	Super::InitializeComponent();

	bHasSetMaterial = false;

	if (!HUDMaterial)
	{
		HUDMaterial = Cast<UMaterial>(HUDMaterialName.TryLoad());
		if (!HUDMaterial)
		{
			COHTML_UE_LOG(Warning,
				TEXT("CohtmlHUDMaterial not found. You can copy it from the plugin's Resources\assets folder."));
		}
	}

	if (HUDMaterial)
	{
		HUDMaterialInstance = UMaterialInstanceDynamic::Create(HUDMaterial, this);
	}
}

void UCohtmlHUD::DrawHUD(class UCanvas* Canvas, int32 positionX, int32 positionY)
{
	if(!FCohtmlSystemHolder::IsReady())
		return;

	if (GetView() && Texture && Texture->Resource)
	{
		if (!HUDMaterialInstance)
		{
			COHTML_UE_LOG(Warning, TEXT("Missing material for HUD rendering. Nothing will be drawn!"));
			return;
		}

		if (!bHasSetMaterial)
		{
			HUDMaterialInstance->SetTextureParameterValue(HUD_TEXTURE_PARAM, Texture);
			bHasSetMaterial = true;
		}

		FCanvasTileItem Tile(FVector2D(positionX, positionY),
#if !defined(COHTML_UE4_421_SUPPORT)
			HUDMaterialInstance->GetRenderProxy(),
#else
			HUDMaterialInstance->GetRenderProxy(false),
#endif
			FVector2D(Texture->SizeX, Texture->SizeY));

		auto BlendMode = SE_BLEND_AlphaComposite;
		Tile.BlendMode = BlendMode;

		Tile.UV0.Y = 0.0f;
		Tile.UV1.Y = 1.0f;

		Canvas->DrawItem(Tile);
	}
}

void UCohtmlHUD::CreateHUDView(
	const cohtml::ViewSettings& info,
	const FString& url)
{
	UCohtmlBaseComponent::CreateView(info, url);
}

void UCohtmlHUD::Resize(int32 width, int32 height)
{
	bHasSetMaterial = false;
	Super::Resize(width, height);
}

int32 UCohtmlHUD::GetUserIndex()
{
	AHUD* OwningHUD = Cast<AHUD>(GetOwner());
	APlayerController* OwningPlayerController = OwningHUD->GetOwningPlayerController();
	if (OwningPlayerController && OwningPlayerController->IsLocalController())
	{
		ULocalPlayer* LocalPlayer = OwningPlayerController->GetLocalPlayer();
		return LocalPlayer ? LocalPlayer->GetControllerId() : 0;
	}
	return 0;
}
