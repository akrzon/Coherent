// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CohtmlGameHUD.h"
#include "MyGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class COHERENTTEST_API AMyGameHUD : public ACohtmlGameHUD
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION()
		void BindUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void OnGenerateBtnClicked();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void OnDestroyBtnClicked();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void OnSliderBtnClicked(const FString& val);
};
