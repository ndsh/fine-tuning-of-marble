/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTPod.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTPod.h"

FTPod::FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution, uint8_t nbOfPods)
{
	//Starting score in play:
	composition = 0;
	act = 0;

	//Instantiate main objects
	Com = new FTCom(onboardLedPin);
	Clock = new FTClock();
  Motor = new FTMotor(motorDirPin,motorStepPin,fullRevolution);
  Sensor = new FTSensor(sensorPin,ledPin,fullRevolution);
  Synth = new FTSynth();

  //Store key values
	_start = false;
	_isClockMaster = false;
	startPin = startButtonPin;
	totalPods = nbOfPods;
	onboardLedPin = onboardLedPin;
  fullRev = fullRevolution;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::update() {
	//Update Com
	receiveCom();
	Com->update();

	if (_start)
	{
		//Update Clock
		setClock();
		Clock->update();

		//Update Sensor
		parseSensor();
		Sensor->update();

		//Update the composition
		updateAct();

		//Conduct the POD
		conduct();

		//Passive update of the actuators
		Motor->update();
		Synth->update();
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::receiveCom()
{
	//Check if the first value has been received from Com to start the play
	if (!_start)
	{
		//Check if is master
		checkMaster();
		if (Com->pulseIn() && !_isClockMaster)
		{
			//It has started, updating iddle pods
			Clock->updatePulse();
			_start = true;
		}
		else
		{
			//It is the clock master, start!
			_start = true;
			#if DEBUG_POD
			Serial.println("FTPod -> receiveCom() -> Ladies and gentleman, please take your seats...");
			#endif
			Clock->startClock();
			delay(START_DELAY);
			#if DEBUG_POD
			Serial.println("FTPod -> receiveCom() -> Start!");
			#endif
		}
	}
}

void FTPod::checkMaster()
{
	if(digitalRead(startPin) == HIGH)
	{
		_isClockMaster = true;
		Clock->setMaster(true);
	}
	else
	{
		_isClockMaster = false;
		Clock->setMaster(true); //Change to *true* in case testing/debugging without COM & the other PODs
	}
  #if DEBUG_POD
    if(_isClockMaster) Serial.println("FTPod -> Greeting m'Ladies. The name's podZero. It's my pleasure to meet you. ;)");
		if(!_isClockMaster) Serial.println("FTPod -> Hey Mr Zero, I don't have a clock. Tell me the beat 'cause I can't do the counts'!");
  #endif
}

void FTPod::setClock()
{
	if (Clock->isOn())
	{
		if (!_isClockMaster)
		{
			//Get last clock value from COM and set
			if (Com->pulseIn()) Clock->updatePulse();
		}
		else
		{
			//Read pulse and send it to COM
			Com->pulseOut(Clock->readPulse());
		}
	}
}

void FTPod::parseSensor()
{
	//Following code is only for testing purposes:
	Sensor->toggleLED(true);
	if (Motor->getTotalMovements() == 1)
	{
		Sensor->toggleDataParsing(true);
	}
	else
	{
		Sensor->toggleDataParsing(false);
	}
	int sensor = Sensor->getSensorValue(Motor->getCurrentAbsolutePosition());
}

void FTPod::updateAct()
{
	if (act < MAX_ACTS)
	{
		if (Clock->readClock() >= compositions[composition][act])
		{
			act++;
			#if DEBUG_POD
			Serial.print("FTPod -> updateAct() -> Changed to act: ");
			Serial.println(act);
			#endif
		}
	}
}

void FTPod::conduct()
{
	switch (composition){

		case 0:
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			Composition 0: The Fine Tuning of Marble
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		switch (act){

			case 0:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 0
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

				//Example:
				if (!Motor->isMoving())
				{
					//Following code is only for testing purposes:
					Motor->setAccelSpeed(0.14,0.14,1);
			 		Motor->runTo(fullRev,0,0);
			 		Motor->updateCounter();
				}
			break;

			case 1:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 1
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 2:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 2
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 3:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 3
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 4:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 4
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 5:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 5
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 6:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 6
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 7:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 7
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 8:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 8
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;

			case 9:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 9
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



			break;
		}

		break;
	}
}
