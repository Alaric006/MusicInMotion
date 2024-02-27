

// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicNote.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AMusicNote::AMusicNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetVisibility(true);

	TopOfNote = CreateDefaultSubobject<USceneComponent>(TEXT("Top of Note"));
	BottomOfNote = CreateDefaultSubobject<USceneComponent>(TEXT("Bottom of Note"));
	
	SetRootComponent(BottomOfNote);
	Mesh->SetupAttachment(GetRootComponent());

	MusicDirection = FVector(0.0f, 0.0f, 0.0f);
	MusicSpeed = 0.0f;

}

void AMusicNote::Initialize(float speed, FVector Direction)
{
	AMusicNote::MusicDirection = Direction;
	AMusicNote::MusicSpeed = speed;
}

// Called when the game starts or when spawned
void AMusicNote::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset((MusicDirection) * MusicSpeed * DeltaTime, false);

}

