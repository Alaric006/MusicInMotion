// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MusicalNoteChannel.generated.h"
/**
 * 
 */
class UAbstractMusicalNote;
USTRUCT(BlueprintType)
struct FMusicNoteAndDistance {
	GENERATED_BODY();
	UAbstractMusicalNote* MusicNote;
	float Distance;

};
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class MUSICINMOTION_API UMusicalNoteChannel : public UObject
{
	GENERATED_BODY()
public:
	float Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Song")
	TArray<UAbstractMusicalNote*> MusicalNotes;

	//Returns distance away from note
	UFUNCTION(BlueprintCallable)
	struct FMusicNoteAndDistance GetClosestNoteAtLocation(float TargetLocation);
};
