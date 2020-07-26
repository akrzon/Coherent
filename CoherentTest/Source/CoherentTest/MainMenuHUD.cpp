// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "CohtmlHUD.h"

#include "cohtml/View.h"
#include "cohtml/Binding/EventHandler.h"

AMainMenuHUD::AMainMenuHUD(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	GetCohtmlHUD()->ReadyForBindings.AddDynamic(this, &AMainMenuHUD::BindUI);
}

void AMainMenuHUD::BindUI()
{
	cohtml::View* View = GetCohtmlHUD()->GetView();
	check(View);

	View->RegisterForEvent("OnQuitBtnClicked", cohtml::MakeHandler(this, &AMainMenuHUD::OnQuitBtnClicked));
	View->RegisterForEvent("OnStartBtnClicked", cohtml::MakeHandler(this, &AMainMenuHUD::OnStartBtnClicked));
}