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
#include "CohtmlAssetReferencer.h"

#include "CohtmlSettings.h"

#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/GameModeBase.h"

bool UCohtmlAssetReferencer::bHasReferencedAssets = false;

UCohtmlAssetReferencer::UCohtmlAssetReferencer(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (bHasReferencedAssets)
	{
		return;
	}

	bHasReferencedAssets = true;
	TArray<FStringAssetReference> Assets;
	// We only to explicitly reference the editor and hud material.
	// Our code does not depend on the others, they are just for the client's comfort
	Assets.Add(CohtmlAssetReferences::EditorMaterial());
	Assets.Add(CohtmlAssetReferences::HUDMaterial());

	for (auto It = Assets.CreateConstIterator(); It; ++It)
	{
		auto MaterialClass = Cast<UMaterial>(It->TryLoad());
		if (MaterialClass)
		{
			// If the material is not present in the game,
			// the static constructor helper will raise an error
			static ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(
				*(It->ToString()));
		}
	}
}


namespace CohtmlAssetReferences
{

FStringAssetReference EditorMaterial()
{
	return FString("Material'/CohtmlPlugin/CohtmlEditorMaterial.CohtmlEditorMaterial'");
}

FStringAssetReference HUDMaterial()
{
	return FString("Material'/CohtmlPlugin/CohtmlHUDMaterial.CohtmlHUDMaterial'");
}

FStringAssetReference CoherentMaterial()
{
	return FString("Material'/CohtmlPlugin/CohtmlMaterial.CohtmlMaterial'");
}
FStringAssetReference CoherentMaterialLight()
{
	return FString("Material'/CohtmlPlugin/CohtmlMaterialLit.CohtmlMaterialLit'");
}
FStringAssetReference CoherentPlane()
{
	return FString("Blueprint'/CohtmlPlugin/CohtmlPlane.CohtmlPlane'");
}
FStringAssetReference CoherentGameHUDBP()
{
	return FString("Blueprint'/CohtmlPlugin/CohtmlGameHUDBP.CohtmlGameHUDBP'");
}

}