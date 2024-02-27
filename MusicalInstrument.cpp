// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicalInstrument.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/SceneComponent.h"
#include "MusicInMotionCharacter.h"
#include "MusicalInstrumentPartBase.h"
#include "AbstractMusicalNote.h"
#include "InstrumentSongChannel.h"
#include "MusicalInstrumentCollection.h"
#include "MusicalNoteChannel.h"
#include "AbstractMusicalNote.h"

// Sets default values
AMusicalInstrument::AMusicalInstrument()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMusicalInstrument::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AMusicalInstrument::EndOverlap);
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

}

void AMusicalInstrument::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begun"));
	ACharacter* InitiatingCharacter = Cast<ACharacter>(OtherActor);
	AMusicInMotionCharacter* MusicInMotionCharacter = Cast<AMusicInMotionCharacter>(InitiatingCharacter);
	if (InitiatingCharacter && MusicInMotionCharacter) {
		APlayerController* InitiatingCharacterController = Cast<APlayerController>(InitiatingCharacter->GetController());
		if (InitiatingCharacterController) {
			ULocalPlayer* InitiatingLocalPlayer = InitiatingCharacterController->GetLocalPlayer();
			if (InitiatingLocalPlayer) {
				UEnhancedInputLocalPlayerSubsystem* InputSystem = InitiatingLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
				if (!MusicInstrumentInputMappingContext.IsNull()) {
					InputSystem->AddMappingContext(MusicInstrumentInputMappingContext.LoadSynchronous(), 1);
					UE_LOG(LogTemp, Warning, TEXT("Bound Input Context"));
					SetActions(MusicInMotionCharacter);
				}
			}
		}
	}
	OwningCollection.Get()->StartSong(Cast<UMusicInMotionSong>(OwningCollection.Get()->Songs[0]->GetDefaultObject()));
}

void AMusicalInstrument::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Ended"));
	AMusicInMotionCharacter* MusicInMotionCharacter = Cast<AMusicInMotionCharacter>(OtherActor);
	ResetActions(MusicInMotionCharacter);
}

void AMusicalInstrument::MulticastPlayNote_Implementation(USoundBase* PlaySound, float volumeModifier, float pitchModifier)
{
		if (AActor* MusicPlayActor = MusicPlayLocation.Get()) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PlaySound, MusicPlayActor->GetActorLocation(), volumeModifier, pitchModifier);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Music Play Location Actor does not exist!"))
		}
}


void AMusicalInstrument::SetMusicLocation(float NewMusicLocation)
{
	AMusicalInstrument::MusicLocation = NewMusicLocation;
	FString DebugMessage = TEXT("Current Music Location: {0}");
	DebugMessage = FString::Format(*DebugMessage, { MusicLocation });
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, DebugMessage);
	for (int i = 0; i < InstrumentParts.Num(); i++) {
		int InstrumentPartCurrentMusicNoteDuration = InstrumentSongChannel->MusicNoteChannels[i]->MusicalNotes[CurrentMusicNoteIndices[i]]->Duration;
		if (NewMusicLocation > CurrentMusicNoteLocationOffsets[i]) {
			UE_LOG(LogTemp, Warning, TEXT("Current music note duration is: %f"), InstrumentPartCurrentMusicNoteDuration);
			UE_LOG(LogTemp, Warning, TEXT("Current music note location offset is %f"), CurrentMusicNoteLocationOffsets[i]);
			CurrentMusicNoteLocationOffsets[i] += (float) InstrumentPartCurrentMusicNoteDuration;
			CurrentMusicNoteIndices[i] += 1;
			if (!InstrumentSongChannel->MusicNoteChannels[i]->MusicalNotes[CurrentMusicNoteIndices[i]]->IsRest) {
				InstrumentPartCurrentMusicNoteDuration = InstrumentSongChannel->MusicNoteChannels[i]->MusicalNotes[CurrentMusicNoteIndices[i]]->Duration;
				InstrumentParts[i]->SpawnNote(SongTempo, InstrumentPartCurrentMusicNoteDuration);
			}
		}
	}
}

void AMusicalInstrument::SpawnStartingNotes()
{
	for (int i = 0; i < InstrumentSongChannel->MusicNoteChannels.Num(); i++) {
		CurrentMusicNoteIndices[i] = 0;
		CurrentMusicNoteLocationOffsets[i] = (int) InstrumentSongChannel->MusicNoteChannels[i]->MusicalNotes[0]->Duration;
		InstrumentParts[i]->SpawnNote(SongTempo, CurrentMusicNoteLocationOffsets[i]);
	}
}


void AMusicalInstrument::SetActions(AMusicInMotionCharacter* MusicInMotionCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Running AMusicalInstrument Bind Action, this function should not be running!"));
}

void AMusicalInstrument::ResetActions(AMusicInMotionCharacter* MusicInMotionCharacter)
{
	MusicInMotionCharacter->PlayInstrumentPart1.Unbind();
	MusicInMotionCharacter->PlayInstrumentPart2.Unbind();
	MusicInMotionCharacter->PlayInstrumentPart3.Unbind();
	MusicInMotionCharacter->PlayInstrumentPart4.Unbind();
}

void AMusicalInstrument::Play1(){
}

void AMusicalInstrument::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CurrentMusicNoteIndices.Init(0, InstrumentParts.Num());
	CurrentMusicNoteLocationOffsets.Init(0, InstrumentParts.Num());
}


// Called when the game starts or when spawned
void AMusicalInstrument::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicalInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

