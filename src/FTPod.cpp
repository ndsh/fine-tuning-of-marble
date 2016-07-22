/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTPod.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTPod.h"

FTPod::FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, long fullRevolution)
{
	//Instantiate main objects
	Com = new FTCom();
	Clock = new FTClock();
	Score = new FTScore();
  	Motor = new FTMotor(motorDirPin,motorStepPin,fullRevolution);
  	Sensor = new FTSensor(sensorPin,ledPin,fullRevolution);
  	Synth = new FTSynth();

  	//Store key values
  	fullRev = fullRevolution;

  	//Set initial states
  	podState = 0;
  	movCounter = 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::update() {
	//Update Com
	receiveCom();
	Com->update();

	//Update Clock
	setClock();
	Clock->update();

	//Update Score
	conductScore();
	Score->update();

	//Update Sensor
	parseSensor();
	Sensor->update();

	//Update Motor
	moveMotor();
	Motor->update();

	//Update Synth
	tuneSynth();
	Synth->update();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::receiveCom()
{
	//Receive messages from neighbour Pods.
}

void FTPod::setClock()
{
	//Set the clock according to Com received values.
}

void FTPod::conductScore()
{
	//Update the current timing of the Score according to the Clock.
	//Update the current FTPod state according to the current Score state.
}

void FTPod::parseSensor()
{
	//Control the data parsing of the sensor and LED status

	//Following code is only for testing purposes:
	Sensor->toggleLED(true);
	if (movCounter == 1)
	{
		Sensor->toggleDataParsing(true);
	}
	else
	{
		Sensor->toggleDataParsing(false);
	}
	int sensor = Sensor->getSensorValue(Motor->getCurrentAbsolutePosition());
}

void FTPod::moveMotor()
{
	//Move the motor according to the Score and Sensor values.
	if (!Motor->isMoving())
	{	
		//Following code is only for testing purposes:
		Motor->setAccelSpeed(0.14,0.14,1);
 		Motor->runTo(fullRev,0,0);
 		movCounter++;
	}
}

void FTPod::tuneSynth()
{
	//Parameterize the Synth according to the Score.
}
