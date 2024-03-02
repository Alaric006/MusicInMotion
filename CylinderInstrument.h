// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicalInstrument.h"
#include "MusicInMotionCharacter.h"
#include "CylinderInstrument.generated.h"

/**
 * 
 */
UCLASS()
class MUSICINMOTION_API ACylinderInstrument : public AMusicalInstrument
{
	GENERATED_BODY()
	void SetActions(AMusicInMotionCharacter* MusicInMotionCharacter) override;


protected:
	void Play1() override;
	void Play2() override;
	void Play3() override;
	void Play4() override;
};
