// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(MenuWidget.ToSharedRef());
		
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidget.IsValid() && MenuWidget) {
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidget.ToSharedRef());

		if (PlayerOwner) {
			if (PlayerOwner) {
				PlayerOwner->bShowMouseCursor;
				PlayerOwner->SetInputMode(FInputModeGameOnly());
			}
		}
	}
}
