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

#include "CohtmlBaseComponent.h"

#include "CohtmlComponent.generated.h"

UCLASS(ClassGroup = UI, hidecategories = Object, editinlinenew, meta = (BlueprintSpawnableComponent, DisplayName = "Prysm Component"), MinimalAPI)
class UCohtmlComponent : public UCohtmlBaseComponent
{
	GENERATED_UCLASS_BODY()
public:
	/** The URL to load when the View is created */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	FString URL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View", meta = (ClampMin = "0", UIMin = "0", UIMax = "4096"))
	int32 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View", meta = (ClampMin = "0", UIMin = "0", UIMax = "4096"))
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	bool ManualTexture;

	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void Resize(int32 width, int32 height) override;
	virtual int32 GetUserIndex() override;

private:
	UMaterialInstanceDynamic* FindUIMaterialInstance() const;
	UPrimitiveComponent* Primitive;

	bool bHasSetTexture;
};
