/*

    ./~     FTSynth.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "FTSynth.h"

FTSynth::FTSynth()
{
	// activate synthesizer
	Music.init();
	Music.enableEnvelope1();
	Music.enableEnvelope2();

	//Apply presets
	applyPreset();

	mNote = 0;
	mNoteVelocity = 127;
  playInitTune();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSynth::applyPreset()
{
	//Preset arrays
	uint8_t mPresetArray[] = {
		23, 0, 0, 0, 50, 1, 127, 0, 121, 3, 0, 64, 64, 127, 9, 40, 0, 2, 0, 0, 0, 64, 63, 127, 4, 0, 0, 0, 0, 0, 0, 64, 61, 127, 4, 12, 0, 1, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 127, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 127, 127, 127, 127, 0, 0, 0, 0, 0, 1, 127, 127, 0, 127
	};

	//Apply
	for (uint8_t i = 2; i < 128; i++) {
    Midi.controller(0, i, mPresetArray[i]);
  }
}

uint8_t FTSynth::mapDataToNote(int sensorData, uint8_t baseNote, uint8_t maxNote, const uint8_t scale[], uint8_t scaleLength)
{
	uint8_t rangeOfScales = floor((maxNote - baseNote)/12);
	uint8_t rangeOfNotes = rangeOfScales * scaleLength;
	uint8_t mapNoteInRange = map(sensorData,0,1023,0,rangeOfNotes);
	uint8_t idScale = mapNoteInRange / scaleLength;
	uint8_t modScale = mapNoteInRange - scaleLength * idScale;
  return (baseNote + (idScale * 12) + scale[modScale]);
}

void FTSynth::updateNote(uint8_t note)
{
	mNote = note;
}

void FTSynth::updateVelocity(uint8_t newVelocity)
{
	//newVelocity ranges from 0 to 1 (to facilitate conversion to 8bits)
	mNoteVelocity = newVelocity;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSynth::playNote()
{
	#if DEBUG_SYNTH
		Serial.printf("~FTSynth::playNote(): Note %i - Velocity: %i\n", mNote, mNoteVelocity);
	#endif
	if (mNote != mLastNote)
	{
		Music.noteOn(mNote, mNoteVelocity);
		mLastNote = mNote;
	}
}

void FTSynth::playInitTune()
{

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
