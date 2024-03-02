// Fill out your copyright notice in the Description page of Project Settings.


#include "CylinderInstrument.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
void ACylinderInstrument::SetActions(AMusicInMotionCharacter* MusicInMotionCharacter)
{
	MusicInMotionCharacter->PlayInstrumentPart1.BindUObject<ACylinderInstrument>(this, &ACylinderInstrument::Play1);
	MusicInMotionCharacter->PlayInstrumentPart2.BindUObject<ACylinderInstrument>(this, &ACylinderInstrument::Play2);
	MusicInMotionCharacter->PlayInstrumentPart3.BindUObject<ACylinderInstrument>(this, &ACylinderInstrument::Play3);
	MusicInMotionCharacter->PlayInstrumentPart4.BindUObject<ACylinderInstrument>(this, &ACylinderInstrument::Play4);
}

void ACylinderInstrument::Play1() {
	FMusicNoteAndDistance NoteAndDistance = InstrumentSongChannel->MusicNoteChannels[0]->GetClosestNoteAtLocation(MusicLocation - InstrumentParts[0]->NoteDurationInGap);

	if (NoteAndDistance.Distance < InstrumentParts[0]->GreenZoneDistance && !NoteAndDistance.MusicNote->IsRest) {
		UAbstractMusicalNote* MusicNote = NoteAndDistance.MusicNote;
		MulticastPlayNote(MusicNote->MusicNoteSound, MusicNote->BaseVolumeMultiplier, MusicNote->BasePitchMultiplier);
		InstrumentParts[0]->OnNotePlayed(NoteAndDistance.MusicNote);
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FailedPlaySound, InstrumentParts[0]->GetActorLocation(), FailedPlaySoundVolumeModifier, 1.0f);
}

void ACylinderInstrument::Play2()
{
	UE_LOG(LogTemp, Warning, TEXT("Inside Play2")); 
	FMusicNoteAndDistance NoteAndDistance = InstrumentSongChannel->MusicNoteChannels[1]->GetClosestNoteAtLocation(MusicLocation - InstrumentParts[1]->NoteDurationInGap);
	if (NoteAndDistance.Distance < InstrumentParts[1]->GreenZoneDistance && !NoteAndDistance.MusicNote->IsRest) {
		UAbstractMusicalNote* MusicNote = NoteAndDistance.MusicNote;
		MulticastPlayNote(MusicNote->MusicNoteSound, MusicNote->BaseVolumeMultiplier, MusicNote->BasePitchMultiplier);
		InstrumentParts[1]->OnNotePlayed(NoteAndDistance.MusicNote);
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FailedPlaySound, InstrumentParts[0]->GetActorLocation(), FailedPlaySoundVolumeModifier, 1.0f);
}

void ACylinderInstrument::Play3()
{
	FMusicNoteAndDistance NoteAndDistance = InstrumentSongChannel->MusicNoteChannels[2]->GetClosestNoteAtLocation(MusicLocation - InstrumentParts[2]->NoteDurationInGap);
	if (NoteAndDistance.Distance < InstrumentParts[2]->GreenZoneDistance && !NoteAndDistance.MusicNote->IsRest) {
		UAbstractMusicalNote* MusicNote = NoteAndDistance.MusicNote;
		MulticastPlayNote(MusicNote->MusicNoteSound, MusicNote->BaseVolumeMultiplier, MusicNote->BasePitchMultiplier);
		InstrumentParts[2]->OnNotePlayed(NoteAndDistance.MusicNote);
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FailedPlaySound, InstrumentParts[0]->GetActorLocation(), FailedPlaySoundVolumeModifier, 1.0f);
}

void ACylinderInstrument::Play4()
{
	FMusicNoteAndDistance NoteAndDistance = InstrumentSongChannel->MusicNoteChannels[3]->GetClosestNoteAtLocation(MusicLocation - InstrumentParts[3]->NoteDurationInGap);
	if (NoteAndDistance.Distance < InstrumentParts[3]->GreenZoneDistance && !NoteAndDistance.MusicNote->IsRest) {
		UAbstractMusicalNote* MusicNote = NoteAndDistance.MusicNote;
		MulticastPlayNote(MusicNote->MusicNoteSound, MusicNote->BaseVolumeMultiplier, MusicNote->BasePitchMultiplier);
		InstrumentParts[3]->OnNotePlayed(NoteAndDistance.MusicNote);
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FailedPlaySound, InstrumentParts[0]->GetActorLocation(), FailedPlaySoundVolumeModifier, 1.0f);
}

