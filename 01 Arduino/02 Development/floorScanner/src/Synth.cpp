/*

    ./~     Synth.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "Synth.h"

/*
	· · · · · · · · · · · · · · · · · · · · ·
		PUBLIC
	· · · · · · · · · · · · · · · · · · · · ·
*/

Synth::Synth() {
	Music.init();
	Music.enableEnvelope1();
	Music.enableEnvelope2();

	applyPreset();

	note = 0;
	noteVelocity = 127;
	startupTune();
}

void Synth::applyPreset() {
	uint8_t presetArray[] = {
		23, 0, 0, 0, 50, 1, 127, 0, 121, 3, 0, 64, 64, 127, 9, 40, 0, 2, 0, 0, 0, 64, 63, 127, 4, 0, 0, 0, 0, 0, 0, 64, 61, 127, 4, 12, 0, 1, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 127, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 127, 127, 127, 127, 0, 0, 0, 0, 0, 1, 127, 127, 0, 127
	};
	for (uint8_t i = 2; i < 128; i++) {
		Midi.controller(0, i, presetArray[i]);
	}
}

uint8_t Synth::mapDataToNote(int sensorData, uint8_t baseNote, uint8_t maxNote, const uint8_t scale[], uint8_t scaleLength) {
	uint8_t rangeOfScales = floor((maxNote - baseNote)/12);
	uint8_t rangeOfNotes = rangeOfScales * scaleLength;
	uint8_t mapNoteInRange = map(sensorData,0,1023,0,rangeOfNotes);
	uint8_t idScale = mapNoteInRange / scaleLength;
	uint8_t modScale = mapNoteInRange - scaleLength * idScale;
	return (baseNote + (idScale * 12) + scale[modScale]);
}

void Synth::updateNote(uint8_t _note) {
	note = _note;
}

//newVelocity ranges from 0 to 1 (to facilitate conversion to 8bits)
void Synth::updateVelocity(uint8_t newVelocity) {
	noteVelocity = newVelocity;
}

/*
	· · · · · · · · · · · · · · · · · · · · ·
		PRIVATE
	· · · · · · · · · · · · · · · · · · · · ·
*/

void Synth::playNote() {
	#if DEBUG_SYNTH
		Serial.printf("~Synth::playNote(): Note %i - Velocity: %i\n", note, noteVelocity);
	#endif
	if (note != lastNote) {
		Music.noteOn(note, noteVelocity);
		lastNote = note;
	}
}

void Synth::startupTune() {
	Music.noteOn(69, 127);
	delay(200);

	Music.noteOn(67, 127);
	delay(200);

	Music.noteOn(76, 127);
	delay(200);

	Music.noteOn(69, 127);
	delay(10);
	Music.noteOff(69);

	//Windows xp
	/*
	Music.noteOn(88, 127);
	delay(280);
	Music.noteOff(88);

	Music.noteOn(76, 127);
	delay(140);
	Music.noteOff(76);

	Music.noteOn(81, 127);
	delay(420);
	Music.noteOff(81);

	Music.noteOn(77, 127);
	delay(560);
	Music.noteOff(77);

	Music.noteOn(88, 127);
	delay(280);
	Music.noteOff(88);

	Music.noteOn(81, 127);
	delay(560);
	Music.noteOff(81);
	*/
}
