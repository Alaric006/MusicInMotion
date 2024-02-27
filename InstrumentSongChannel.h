// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InstrumentSongChannel.generated.h"

/**
 * 
 */
class UMusicalNoteChannel;


UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class MUSICINMOTION_API UInstrumentSongChannel : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	float Location = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Music")
	TArray<UMusicalNoteChannel*> MusicNoteChannels;


};
