// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicalNoteChannel.h"
#include "AbstractMusicalNote.h"


FMusicNoteAndDistance UMusicalNoteChannel::GetClosestNoteAtLocation(float TargetLocation)
{
	//Test if the first note is the closest
	if (TargetLocation < MusicalNotes[0]->Duration / 2.0f) {
		if (TargetLocation < 0) {
			return{ MusicalNotes[0], -TargetLocation };
		}
		return { MusicalNotes[0], TargetLocation };
	}

	UAbstractMusicalNote* NoteBeforeCurrentLocation = MusicalNotes[0];
	UAbstractMusicalNote* NoteAtCurrentLocation = MusicalNotes[1];

	float CurrentLocation = 0.0f;
	for (int i = 1; i < MusicalNotes.Num(); i++) {
		NoteBeforeCurrentLocation = MusicalNotes[i-1];
		NoteAtCurrentLocation = MusicalNotes[i];
		CurrentLocation += NoteBeforeCurrentLocation->Duration;
		if (CurrentLocation > TargetLocation) {
			if (CurrentLocation - TargetLocation < TargetLocation - (CurrentLocation - NoteBeforeCurrentLocation->Duration)) {
				return { NoteAtCurrentLocation, CurrentLocation - TargetLocation };
			}
			return { NoteBeforeCurrentLocation, TargetLocation - (CurrentLocation - NoteBeforeCurrentLocation->Duration) };
		}
	}
	return { MusicalNotes[MusicalNotes.Num() - 1], TargetLocation - CurrentLocation } ;
}
