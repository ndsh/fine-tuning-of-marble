/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTPod.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTPod.h"

FTPod::FTPod()
{
	//Instantiate main objects
	Com = new FTCom();
	Clock = new FTClock();
	Score = new FTScore();	
  	Motor = new FTMotor();
  	Synth = new FTSynth();
}

void FTPod::update() {
	//Update Com
	Com->update();

	//Update Score
	Score->update();

	//Update Clock
	Clock->update();

	//Update Motor
	Motor->update();

	//Update Synth
	Synth->update();
}