/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTSynth.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTSynth.h"

FTSynth::FTSynth()
{
	// activate synthesizer
	Music.init();

	Music.enableEnvelope1();
  Music.enableEnvelope2();
  playInitTune();
}

void FTSynth::update() {

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSynth::playInitTune()
{
	//To do: evaluate if delay is needed (when Midi initialization is removed from synth).
	delay(1000);

	// play a tune maybe?
	Music.noteOn(69, 127);
	delay(200);
	Music.noteOff(69);

	Music.noteOn(67, 127);
	delay(200);
	Music.noteOff(67);

	Music.noteOn(76, 127);
	delay(200);
	Music.noteOff(76);
}
