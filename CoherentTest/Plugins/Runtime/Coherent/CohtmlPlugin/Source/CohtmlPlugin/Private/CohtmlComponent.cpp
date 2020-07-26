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
#include "CohtmlComponent.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Components/PrimitiveComponent.h"

#define UI_TEXTURE_NAME TEXT("UITexture")

UCohtmlComponent::UCohtmlComponent(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	URL = TEXT("coui://uiresources/hb_hud/");
	Width = 1024;
	Height = 1024;
	ManualTexture = false;
}

void UCohtmlComponent::InitializeComponent()
{
	Super::InitializeComponent();

	bHasSetTexture = false;

	auto Owner = GetOwner();
	TArray<UPrimitiveComponent*> primitives;
	Owner->GetComponents<UPrimitiveComponent>(primitives);

	if (!primitives.Num())
	{
		return;
	}
	Primitive = primitives[0];
}

int32 UCohtmlComponent::GetUserIndex()
{
	// TODO: Return the proper index here after deciding how concurrent
	// in-world text input between multiple players should behave.
	return 0;
}

void UCohtmlComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!HasRequestedView())
	{
		if (!ManualTexture)
		{
			auto MaterialInstance = FindUIMaterialInstance();
			if (!MaterialInstance)
				return;
			UTexture* Tex = nullptr;
			if (!MaterialInstance->GetTextureParameterValue(UI_TEXTURE_NAME, Tex))
				return;
		}
		cohtml::ViewSettings info;
		info.Width = Width;
		info.Height = Height;

		CreateView(info, *URL);
	}
	else
	{
		if (!bHasSetTexture && !ManualTexture)
		{
			auto MaterialInstance = FindUIMaterialInstance();
			if (!MaterialInstance)
				return;
			UTexture* Tex = nullptr;
			if (!MaterialInstance->GetTextureParameterValue(UI_TEXTURE_NAME, Tex))
				return;

			MaterialInstance->SetTextureParameterValue(UI_TEXTURE_NAME, Texture);

			bHasSetTexture = true;
		}
	}
}

UMaterialInstanceDynamic* UCohtmlComponent::FindUIMaterialInstance() const
{
	if (!Primitive)
	{
		return nullptr;
	}
	auto MaterialsCount = Primitive->GetNumMaterials();
	if (MaterialsCount < 1)
		return nullptr;

	auto BaseMaterial = Primitive->GetMaterial(0);
	auto MaterialInstance = Cast<UMaterialInstanceDynamic>(BaseMaterial);

	if (!MaterialInstance)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, Primitive);
		Primitive->SetMaterial(0, MaterialInstance);
	}

	return MaterialInstance;
}

void UCohtmlComponent::Resize(int32 width, int32 height)
{
	bHasSetTexture = false;
	Super::Resize(width, height);
}
