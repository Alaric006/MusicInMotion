// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicalNoteChannel.h"
#include "MusicalInstrumentPartBase.h"
#include "AbstractMusicalNote.h"
#include "InstrumentSongChannel.h"
#include "MusicalInstrument.generated.h"
class UCapsuleComponent;
class UInputMappingContext;
class UEnhancedInputComponent;
class AMusicInMotionCharacter;
class USceneComponent;
class USoundBase;
class UAbstractMusicalNote;
class UInstrumentSongChannel;
class AMusicalInstrumentCollection;
struct FMusicNoteAndDistance;
UCLASS()
class MUSICINMOTION_API AMusicalInstrument : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicalInstrument();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	TSoftObjectPtr<AActor> MusicPlayLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	TArray<class AMusicalInstrumentPartBase*> InstrumentParts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	UCapsuleComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	TSoftObjectPtr<UInputMappingContext> MusicInstrumentInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	TSoftObjectPtr<AMusicalInstrumentCollection> OwningCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	UInstrumentSongChannel* InstrumentSongChannel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	int SongTempo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	float MusicLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	TArray<int> CurrentMusicNoteIndices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	TArray<float> CurrentMusicNoteLocationOffsets;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayNote(USoundBase* PlaySound, float volumeModifier = 1.0f, float pitchModifier = 1.0f);

	UFUNCTION()
	void SetMusicLocation(float NewMusicLocation);

	UFUNCTION()
	void SpawnStartingNotes();

	UFUNCTION()
	virtual void SetActions(AMusicInMotionCharacter* MusicInMotionCharacter);

	UFUNCTION()
	void ResetActions(AMusicInMotionCharacter* MusicInMotionCharacter);

	virtual void Play1();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
