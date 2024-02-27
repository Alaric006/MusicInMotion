// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MUSICINMOTION_API AMenuHUD : public AHUD
{
	GENERATED_BODY()


public: 
	void RemoveMenu();
protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SMenuWidgetContainer> MenuWidgetContainer;

	virtual void BeginPlay() override;

	void ShowMenu();

};
