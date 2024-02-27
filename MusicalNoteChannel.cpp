// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicalNoteChannel.h"
#include "AbstractMusicalNote.h"


FMusicNoteAndDistance UMusicalNoteChannel::GetClosestNoteAtLocation(float Location)
{
	//Check to see if location is closest to first note
	if ((MusicalNotes[0]->Duration / 2.0f) > Location) {
		return { MusicalNotes[0], Location };
	}
	float CurrentLocation = 0.0f;
	UAbstractMusicalNote* PreviousNote = MusicalNotes[0];
	UAbstractMusicalNote* CurrentNote;
	for (int i = 0; i < MusicalNotes.Num(); i++) {
		CurrentLocation += MusicalNotes[i]->Duration;
		if (CurrentLocation > Location) {
			CurrentNote = MusicalNotes[i];
			break;
		}
		PreviousNote = MusicalNotes[i];
	}
	if ((CurrentLocation - Location) < Location - (CurrentLocation - CurrentNote->Duration)) {
		return { CurrentNote, CurrentLocation - Location };
	}
	return { PreviousNote, Location - (CurrentLocation - CurrentNote->Duration) };
}
