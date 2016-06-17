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

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 Motor -> usage examples
 
 #Rotate two times, in half of constant speed, clockwise
 Motor->setConstantSpeed(0.5);
 Motor->rotate(2,1);

 #Rotate two times, with acceleration, half ramp both IN and OUT, full max speed
 Motor->setAccelSpeed(0.5,0.5,1);
 Motor->rotate(2,1);

 #Run to an absolute position, clockwise, with acceleration, half ramp both IN and OUT, full max speed
 Motor->setAccelSpeed(0.5,0.5,1);
 Motor->runTo(40000,1);

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/



