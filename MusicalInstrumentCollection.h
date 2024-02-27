// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicalInstrumentCollection.generated.h"

class AMusicalInstrument;
class UMusicInMotionSong;

UCLASS()
class MUSICINMOTION_API AMusicalInstrumentCollection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicalInstrumentCollection();

	//Tempo in BPM, 
	int Tempo = 0;

	float MusicLocation = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	UMusicInMotionSong* SongPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	TArray<AMusicalInstrument*> MusicalInstruments;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	TArray<TSubclassOf<UMusicInMotionSong>> Songs;
	
	UFUNCTION(BlueprintCallable)
	void StartSong(UMusicInMotionSong* SongToStart);

	UFUNCTION(BlueprintCallable)
	void StopSong();

	UFUNCTION(BlueprintCallable)
	void UpdateInstrumentMusicLocations();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
