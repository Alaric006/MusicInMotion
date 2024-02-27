// Fill out your copyright notice in the Description page of Project Settings.


#include "CylinderInstrument.h"
#include "EnhancedInputComponent.h"
void ACylinderInstrument::SetActions(AMusicInMotionCharacter* MusicInMotionCharacter)
{
	MusicInMotionCharacter->PlayInstrumentPart1.BindUObject<ACylinderInstrument>(this, &ACylinderInstrument::Play1);
}

void ACylinderInstrument::Play1_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Inside Play1_Implementation"))
	FMusicNoteAndDistance NoteAndDistance = InstrumentSongChannel->MusicNoteChannels[0]->GetClosestNoteAtLocation(MusicLocation - InstrumentParts[0]->NoteDurationInGap);
	FString LogMessage = FString::Format(TEXT("Target Location is: {0}. Closest note distance is {1}"), { MusicLocation - InstrumentParts[0]->NoteDurationInGap, NoteAndDistance.Distance });
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
	if (NoteAndDistance.Distance < InstrumentParts[0]->GreenZoneDistance) {
		UAbstractMusicalNote* MusicNote = NoteAndDistance.MusicNote;
		MulticastPlayNote(MusicNote->MusicNoteSound, MusicNote->BaseVolumeMultiplier, MusicNote->BasePitchMultiplier);
	}
}

