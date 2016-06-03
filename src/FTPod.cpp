/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTPod.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTPod.h"

FTPod::FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin)
{
	//Instantiate main objects
	Com = new FTCom();
	Clock = new FTClock();
	Score = new FTScore();
  	Motor = new FTMotor(motorDirPin,motorStepPin);
  	Sensor = new FTSensor(sensorPin,ledPin);
  	Synth = new FTSynth();
}

void FTPod::update() {
	//Update Com
	Com->update();

	//Update Sensor
	Sensor->update();

	//Update Clock
	Clock->update();

	//Update Score
	Score->update();

	//Update Motor
	Motor->update();

	//Update Synth
	Synth->update();
}