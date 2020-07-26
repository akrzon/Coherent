// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CohtmlGameHUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class COHERENTTEST_API AMainMenuHUD : public ACohtmlGameHUD
{
	GENERATED_UCLASS_BODY()
	
public:
	UFUNCTION()
	void BindUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
	void OnQuitBtnClicked();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
	void OnStartBtnClicked();
};
