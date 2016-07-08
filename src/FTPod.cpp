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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

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
	
	//Example random movement:
	if (!Motor->isMoving())
	{
      	Motor->setAccelSpeed(0.14,0.14,1);
 		Motor->runTo(random(25600),random(-1,1),0);
	}

	Motor->update();

	//Update Synth
	Synth->update();
}
