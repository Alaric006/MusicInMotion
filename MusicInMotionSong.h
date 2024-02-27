// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MusicInMotionSong.generated.h"

/**
 * 
 */
class UInstrumentSongChannel;
UCLASS(Blueprintable, BlueprintType)
class MUSICINMOTION_API UMusicInMotionSong : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Song")
	FText SongName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Song")
	int Tempo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Song")
	int SongDuration; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Song")
	TArray<UInstrumentSongChannel*> SongChannels;
	
};
