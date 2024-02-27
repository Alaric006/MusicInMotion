// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicalInstrumentCollection.h"
#include "MusicalInstrument.h"
#include "MusicInMotionSong.h"
#include "Engine/Engine.h"

// Sets default values
AMusicalInstrumentCollection::AMusicalInstrumentCollection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SongPlaying = nullptr;
}

void AMusicalInstrumentCollection::StartSong(UMusicInMotionSong* SongToStart)
{
	UE_LOG(LogTemp, Warning, TEXT("Starting Song inside Musical Instrument Collection"));
	if (!SongPlaying) {
		SongPlaying = SongToStart;
	}
	else {
		return;
	}

	//Set values for new song
	MusicLocation = 0.0f;
	Tempo = SongPlaying->Tempo;

	for (int i = 0; i < SongPlaying->SongChannels.Num(); i++) {
		MusicalInstruments[i]->InstrumentSongChannel = SongPlaying->SongChannels[i];
		MusicalInstruments[i]->SongTempo = Tempo;
	}
	for (int i = 0; i < MusicalInstruments.Num(); i++) {
		MusicalInstruments[i]->SpawnStartingNotes();
	}

}

void AMusicalInstrumentCollection::UpdateInstrumentMusicLocations()
{
	FString DebugMessage = TEXT("Current Music Location: {0}");
	DebugMessage = FString::Format(*DebugMessage, { MusicLocation });
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, DebugMessage);
	for (AMusicalInstrument* MusicalInstrument : MusicalInstruments) {
		MusicalInstrument->SetMusicLocation(this->MusicLocation);
	}
}

void AMusicalInstrumentCollection::StopSong()
{
	SongPlaying = nullptr;
}

// Called when the game starts or when spawned
void AMusicalInstrumentCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicalInstrumentCollection::Tick(float DeltaTime)
{

	if (SongPlaying) {
		Super::Tick(DeltaTime);
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, TEXT("Inside Tick"));
		MusicLocation += ((float)Tempo * (16.0f/60.0f)) * DeltaTime;
		UpdateInstrumentMusicLocations();
		if (MusicLocation > SongPlaying->SongDuration) {
			StopSong();
		}
	}
}

