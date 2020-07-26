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

#include <GameFramework/Actor.h>
#include <Engine/World.h>

#include "CohtmlSystem.generated.h"

class FCohtmlRendererHolder;
class FCohtmlSystemWrapper;
class UCohtmlBaseComponent;

typedef TSharedPtr<FCohtmlSystemWrapper, ESPMode::ThreadSafe> FCohtmlSystemWrapperSharedPtr;

UCLASS(MinimalAPI, meta=(DisplayName = "Prysm System"))
class ACohtmlSystem : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	virtual void BeginDestroy() override;
	virtual bool IsReadyForFinishDestroy() override;

	COHTMLPLUGIN_API FCohtmlSystemWrapperSharedPtr GetSystemObject() const;
	bool IsSystemObjectValid() const { return System.IsValid(); }
	TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe> GetSystemRendererPtr();

	void RegisterComponent(UCohtmlBaseComponent* component);
	void UnregisterComponent(UCohtmlBaseComponent* component);

	typedef TArray<TWeakObjectPtr<UCohtmlBaseComponent>> WeakCohtmlComponentsArray;
	WeakCohtmlComponentsArray::TIterator GetCohtmlComponentsIterator();

	inline static bool IsActorTicking()
	{
		return MasterSystem != nullptr && MasterSystem->HasActorBegunPlay() && !MasterSystem->GetWorld()->IsPaused();
	}
	// Since we can't always guarantee that the system is running, we need a fallback that will advance it even
	// when the game isn't running (in the editor)
	inline static void NotifyPossibleFallbackTickerDestroyed(void* Ticker)
	{
		if (FallbackTicker == Ticker)
		{
			FallbackTicker = nullptr;
		}
	}
	inline static bool IsFallbackTicker(void* Ticker)
	{
		if (FallbackTicker == nullptr)
		{
			FallbackTicker = Ticker;
		}
		return FallbackTicker == Ticker;
	}

private:
	FCohtmlSystemWrapperSharedPtr System;
	TSharedPtr<FCohtmlRendererHolder, ESPMode::ThreadSafe> Renderer;

	FRenderCommandFence ReleaseRendererFence;
	bool bHasIssuedRendererDestroyCommand;

	WeakCohtmlComponentsArray WeakCohtmlComponents;
	COHTMLPLUGIN_API static ACohtmlSystem* MasterSystem;
	static void* FallbackTicker;

	friend class CohtmlPrivateTestingHelper;
};