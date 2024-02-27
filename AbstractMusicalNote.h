// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbstractMusicalNote.generated.h"

/**
 * 
 */

class USoundBase;

UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class MUSICINMOTION_API UAbstractMusicalNote : public UObject
{
	GENERATED_BODY()
	
public:
	//64 for whole note, 32 for half, 16 for quarter, etc
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note")
	float Duration = 16;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note")
	USoundBase* MusicNoteSound;

	//If IsRest = true, will play PlaySound at normal volume not matter when during the rest it is played
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note")
	bool IsRest = false;;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note|Volume")
	float BaseVolumeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note|Volume")
	float MinVolumeMultiplierDeviation = 0.05;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note|Volume")
	float MaxVolumeMultiplierDeviation = 0.2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note|Pitch")
	float BasePitchMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note|Pitch")
	float MinPitchMultiplierDeviation = 0.005;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music Note|Pitch")
	float MaxPitchMultiplierDeviation = 0.02;


};
