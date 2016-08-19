/*

    ./~     FTPod.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "FTPod.h"

FTPod::FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution, uint8_t nbOfPods)
{
	//Starting score in play:
	mComposition = COMPOSITION;
	mAct = 0;

	//Store key values
	mStart = false;
	mIsClockMaster = false;
	mStartPin = startButtonPin;
	mTotalPods = nbOfPods;
	mOnboardLedPin = onboardLedPin;
	mPodChannel = 0; //at time of creation we don't know how many pods are out there
  mFullRev = fullRevolution;

  //Retrieve POD's mac address
	retrieveMacAddress();
	getMacAddressPosition();

	//Instantiate main objects
	Com = new FTCom(onboardLedPin);
	Clock = new FTClock();
	Motor = new FTMotor(motorDirPin,motorStepPin,fullRevolution);
	Sensor = new FTSensor(sensorPin,ledPin,fullRevolution);
	Synth = new FTSynth(mComposition);

  	//let's ask if there are other pods out there
  	//1. if this is the master
  	//2. find out how many pods are out there by pinging around
  	//	2a	write()->establish data:mPodChannel to +1 pod
  	//	2b	read()->establish from -1 pod.
  	//		2ba		n+1 					--> there are several pods
  	//		2bb		mPodChannel == establish --> alone
  	//		2bc		no read() 				--> connection broken
  	//3. establish an order
  	//	2a if there is a read() on the master with a definited podNumber
  	//	2b start() !
  	//
  	//every other pod just remains silent in listening mode, until the master pings it

  	//if channel is 0 -> check if master -> if not master, make an echo
  	//if channel is 0 -> check if master -> if master, do routine written above



}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::update() {
	//Update Com
	receiveCom();
	Com->update();

	if (mStart)
	{
		//Update Clock
		setClock();
		Clock->update();

		//Update Sensor
		Sensor->update();
		parseSensor();

		//Update the composition
		updateAct();

		//Conduct the POD
		conduct();

		//Uptade motor (passive)
		Motor->update();

		//Update synth
		tune();
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::receiveCom()
{
	//Check if the first value has been received from Com to start the play
	if (!mStart)
	{
		//Check if is master
		checkMaster();
		if (Com->pulseIn() && !mIsClockMaster)
		{
			//It has started, updating iddle pods
			Clock->updatePulse();
			mStart = true;
		}
		else
		{
			//It is the clock master, start!
			mStart = true;
			#if DEBUG_POD
				Serial.println("~FTPod::receiveCom()-› Ladies and gentlemen, please take your seats...");
			#endif
			Clock->startClock();
			delay(START_DELAY);
			#if DEBUG_POD
				Serial.println("~FTPod::receiveCom()-› Start!");
			#endif
		}
	}
}

void FTPod::checkMaster()
{
	if(digitalRead(mStartPin) == HIGH)
	{
		mIsClockMaster = true;
		Clock->setMaster(true);
	}
	else
	{
		mIsClockMaster = false;
		Clock->setMaster(true); //Change to *true* in case testing/debugging without COM & the other PODs
	}
  #if DEBUG_POD
    if(mIsClockMaster) Serial.println("~FTPod: Greeting m'Ladies. The name's podZero. It's my pleasure to meet you. *tips fedora*");
	else Serial.println("~FTPod: Hey Mr Zero, I don't have a clock. Tell me the beat 'cause I can't do the counts'!");
  #endif
}

void FTPod::setClock()
{
	if (Clock->isOn())
	{
		if (!mIsClockMaster)
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

String FTPod::getMacAddress() {
	return mMacAddress;
}

void FTPod::retrieveMacAddress() {
	mMacAddress = MacAddress::get();
  	#if DEBUG_POD
	    Serial.print("~FTPod::retrieveMacAddress()-› ");
	    Serial.println(mMacAddress);
    #endif
}

void FTPod::getMacAddressPosition() {
	String MacAddresses[] = {
		#include "inc/Hardware.h"
	};
	uint8_t podChannel = 0;
	for(uint8_t i = 0; i<7; i++) {
		if(MacAddresses[i] == mMacAddress) {
			MacAddresses[i] =
			podChannel = i;
			break;
		}
	}
    mPodChannel = podChannel;
    #if DEBUG_POD
	    Serial.print("~FTPod::getMacAddressPosition()-› This Pod's Channel is: ");
	    Serial.println(mPodChannel);
    #endif
}

void FTPod::updateAct()
{
	if (mAct < MAX_ACTS)
	{
		if (Clock->readClock() >= compositions[mComposition][mAct])
		{
			mAct++;
			#if DEBUG_POD
			Serial.print("~FTPod::updateAct()-› Changed to act: ");
			Serial.println(mAct);
			#endif
		}
	}
}

void FTPod::tune()
{
	Synth->mapDataToNote(Sensor->mCurrentSensorValue, NOTE_C3, NOTE_A6, MINOR, MINOR_LEN);
}

void FTPod::conduct()
{
	switch (mComposition){

		case 0:
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			Composition 0: The Fine Tuning of Marble
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		switch (mAct){

			case 0:
				/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//COMP 0, ACT 0
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

				//Example:
				if (!Motor->isMoving())
				{
					//Following code is only for testing purposes:
					Motor->setAccelSpeed(0.14,0.14,1);
			 		Motor->runTo(mFullRev,0,0);
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
