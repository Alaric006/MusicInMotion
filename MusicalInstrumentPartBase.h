// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicalInstrumentPartBase.generated.h"

class UMusicSpawnPoint;
class UStaticMeshComponent;
class USceneComponent;
class AMusicNote;

UCLASS()
class MUSICINMOTION_API AMusicalInstrumentPartBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicalInstrumentPartBase();

	//Ammount of Note duration inbetween play and spawn points
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float NoteDurationInGap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float MusicNoteScalingFactor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	FVector SpawnOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	float DistanceInBetweenSpawnAndPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float GreenZoneDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	UMusicSpawnPoint* MusicNotesSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USceneComponent* MusicPlayPoint;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FVector MusicNotesDirection;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music");
	TSubclassOf<AMusicNote> MusicNoteSpawningClass;

	UFUNCTION(Blueprintcallable)
	void SpawnNote(int Tempo, int NoteDuration);

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
