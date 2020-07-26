// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameHUD.h"
#include "CohtmlHUD.h"

#include "cohtml/View.h"
#include "cohtml/Binding/EventHandler.h"

AMyGameHUD::AMyGameHUD(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	GetCohtmlHUD()->ReadyForBindings.AddDynamic(this, &AMyGameHUD::BindUI);
}

void AMyGameHUD::BindUI()
{
	cohtml::View* View = GetCohtmlHUD()->GetView();
	check(View);

	View->RegisterForEvent("OnGenerateBtnClicked", cohtml::MakeHandler(this, &AMyGameHUD::OnGenerateBtnClicked));
	View->RegisterForEvent("OnDestroyBtnClicked", cohtml::MakeHandler(this, &AMyGameHUD::OnDestroyBtnClicked));
	View->RegisterForEvent("OnSliderBtnClicked", cohtml::MakeHandler(this, &AMyGameHUD::OnSliderBtnClicked));
}