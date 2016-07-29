/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTPod.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTPod.h"

FTPod::FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, long fullRevolution)
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
  	startPin = startButtonPin;

  	//Set initial states
  	podState = 0;
  	movCounter = 0;
  	
	retrieveMacAddress();


	// activate synthesizer
	Music.init();

	Music.enableEnvelope1();
    Music.enableEnvelope2();
    //TODO evaluate if delay is needed (when Midi initialization is removed from synth).
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

String FTPod::getMacAddress() {
	return macAddress;
}

void FTPod::retrieveMacAddress() {
	macAddress = MacAddress::get();
  	#if DEBUG_POD
    Serial.print("Your Teensy Mac Address is: ");
    Serial.println(macAddress);
    #endif
    
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::receiveCom()
{
	//Receive messages from neighbour Pods.
	//Ps: don't forget to do the Clock->updatePulse(uint16_t) and Clock->setMaster(false) properly in case it receives a pulse through midi ;)
}

void FTPod::setClock()
{
	//Set the clock according to Com received values.
	if (Clock->isOn())
	{
		if (!Clock->isClockMaster())
		{
			//Get last clock value from COM and set
			Clock->updatePulse(0); //<----- change this line later
		}
	}
	else
	{
		if (digitalRead(startPin))
		{
			Clock->setMaster(true);
			Clock->startClock();
		}
	}
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
