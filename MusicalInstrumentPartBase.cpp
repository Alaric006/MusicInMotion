// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicalInstrumentPartBase.h"
#include "MusicSpawnPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "MusicNote.h"

// Sets default values
AMusicalInstrumentPartBase::AMusicalInstrumentPartBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetVisibility(true);

	MusicNotesSpawnPoint = CreateDefaultSubobject<UMusicSpawnPoint>(TEXT("Music Notes Spawn Point"));
	MusicNotesSpawnPoint->SetupAttachment(RootComponent);
	MusicNotesSpawnPoint->SetRelativeLocation(FVector(0, 0, 0), false, nullptr, ETeleportType::None);
	MusicPlayPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Music Play Point"));
	MusicPlayPoint->SetupAttachment(RootComponent);
	DistanceInBetweenSpawnAndPlay = 0.0f;
	MusicNoteScalingFactor = 1.0f;
	SpawnOffset = FVector(0.0f, 0.0f, 0.0f);

	MusicNoteSpawningClass = AMusicNote::StaticClass();
	MusicNotesDirection = FVector(0.0f, 0.0f, -1.0f);


}

void AMusicalInstrumentPartBase::SpawnNote(int Tempo, int NoteDuration)
{
	FVector SpawnLocation = MusicNotesSpawnPoint->GetRelativeLocation() + this->GetActorLocation() + SpawnOffset;
	FRotator SpawnRotation = MusicNotesSpawnPoint->GetComponentRotation();
	
	float MusicNoteTravelSpeed = DistanceInBetweenSpawnAndPlay / (NoteDurationInGap / (Tempo * (16.0f/60.0f)));
	float ScaleMultiplier = (NoteDuration / (NoteDurationInGap / 4.0f)) * (DistanceInBetweenSpawnAndPlay / 100.0f) * MusicNoteScalingFactor;


	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, FString::Format(TEXT("Spawning note with speed {0}, scale multiplier {4} at location {1} {2} {3}"), { MusicNoteTravelSpeed, SpawnLocation.X,SpawnLocation.Y, SpawnLocation.Z, ScaleMultiplier }));

	AMusicNote* SpawnedMusicNote = Cast<AMusicNote>(GetWorld()->SpawnActor(MusicNoteSpawningClass, &SpawnLocation, &SpawnRotation));
	SpawnedMusicNote->Initialize(MusicNoteTravelSpeed, MusicNotesDirection);
	SpawnedMusicNote->SetActorScale3D(FVector(1.0f, 1.0f, ScaleMultiplier));
}

void AMusicalInstrumentPartBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Inside Post Edit Change Property"));
	DistanceInBetweenSpawnAndPlay = MusicNotesSpawnPoint->GetRelativeLocation().Z - MusicPlayPoint->GetRelativeLocation().Z;
}


// Called when the game starts or when spawned
void AMusicalInstrumentPartBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicalInstrumentPartBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

