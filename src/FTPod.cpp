/*

    ./~     FTPod.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "FTPod.h"

FTPod::FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution, uint8_t totalPods, uint8_t score, uint16_t pulseInterval)
{
	//Store key values
	mScore = score;
	mStart = false;
	mAct = 0;
	mIsClockMaster = false;
	mStartPin = startButtonPin;
	mOnboardLedPin = onboardLedPin;
	mFullRev = fullRevolution;
	mTotalPods = totalPods;
	mPodChannel = 0;
	mTimeoutCounter = 0;

  //Retrieve POD's mac address
	retrieveMacAddress();
	getMacAddressPosition();

	//Instantiate main objects
	Com = new FTCom(onboardLedPin);
	Clock = new FTClock(pulseInterval);
	Motor = new FTMotor(motorDirPin,motorStepPin,fullRevolution);
	Sensor = new FTSensor(sensorPin,ledPin,fullRevolution);
	Synth = new FTSynth();
	Score = new FTScore();

	#if DEBUG_POD
	Serial.printf("~FTPod: Pod %i started. Waiting for start...\n",mPodChannel);
	#endif
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::update() {
	//Update Com
	Com->update();

	if (mStart)
	{
		//Update Clock
		setClock();
		Clock->update();

		//Update Sensor
		Sensor->update(Motor->getCurrentAbsolutePosition());

		//Conduct the POD according to Score
		if (Clock->readPulse())
		{
			conduct();
			sendCom();
		}

		//Passive Updates
		Motor->update();
		Synth->playNote();
	}
	else
	{
		checkStart();
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTPod::checkStart()
{
		//Check if is master
		checkMaster();
		if (Com->pulseIn() && !mIsClockMaster)
		{
			//It has started, updating iddle pods
			Clock->updatePulse();
			mStart = true;
		}
		if (mIsClockMaster)
		{
			//It is the clock master, start!
			mStart = true;
			#if DEBUG_POD
				Serial.println("~FTPod::checkComStart()-› Ladies and gentlemen, please take your seats...");
			#endif
			Clock->startClock();
			delay(START_DELAY);
			#if DEBUG_POD
				Serial.println("~FTPod::checkComStart()-› Start!");
			#endif
		}
}

void FTPod::checkMaster()
{
	if(digitalRead(mStartPin) == true)
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
    if(mIsClockMaster) Serial.println("~FTPod: Greeting m'Ladies. The name's Master. Clock Master. It's my pleasure to meet you. *tips fedora*");
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
	for(uint8_t i = 0; i < mTotalPods; i++) {
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

void FTPod::conduct()
{
	//Update act
	mTimeoutCounter++;
	if (Com->podsDone())
	{
		mAct++;
		#if DEBUG_POD
		Serial.printf("~FTPod::conduct(): Changed to act %i\n", mAct);
		#endif
	}
	else{
		if (mTimeoutCounter > Score->getTimeOut(mAct))
		{
			mAct++;
			#if DEBUG_POD
			Serial.printf("~FTPod::conduct(): Timeout! Changing to act %i\n", mAct);
			#endif
		}
	}

	//Update actions
	if (mAct < Score->getTotalActs())
	{
		if (Score->getPodPermission(mAct,mPodChannel))
		{
			if (!(Score->hasActStarted(mAct)))
			{
				//Only once, at beginning of the act:
				#if DEBUG_POD
				Serial.printf("~FTPod::conduct(): Starting act %i\n", mAct);
				#endif
				mTimeoutCounter = 0;
				Score->startAct(mAct);
				configureSensor(Score->getSensorAction(mAct));
				moveMotor(Score->getMotorAction(mAct));
			}
		}
		//Always tune synth:
		tuneSynth(Score->getSynthAction(mAct));
	}
	else
	{
		#if DEBUG_POD
		Serial.printf("~FTPod::conduct(): Performance is finished! Applause, yo! 8)", mAct);
		#endif
	}
}

void FTPod::configureSensor(uint16_t actionID)
{
	#if DEBUG_POD
	Serial.printf("~FTPod::conduct(): Act %i -> configureSensor: ID %i\n", mAct,actionID);
	#endif
	switch(actionID)
	{
		case 0:
		//Parsing data from the ground (first round)
		Sensor->toggleLED(true);
		Sensor->toggleDataParsing(true);
		break;

		case 1:
		//LED ON, data parsing off (gets from array)
		Sensor->toggleLED(true);
		Sensor->toggleDataParsing(false);
		break;

		case 2:
		//LED off, parsing off.
		Sensor->toggleLED(false);
		Sensor->toggleDataParsing(false);
		break;
	}
}

void FTPod::moveMotor(uint16_t actionID)
{
	#if DEBUG_POD
	Serial.printf("~FTPod::conduct(): Act %i -> moveMotor: ID %i\n", mAct,actionID);
	#endif
	switch(actionID)
	{
		case 0:
		//Full revolution with acceleration
		Motor->setAccelSpeed(0.5,0.5,1);
		Motor->rotate(1,1);
		break;

		case 1:
		//Accelerated motion to position relative to a sensor value, full speed, free direction
		Motor->setAccelSpeed(0.5,0.5,1);
		Motor->runTo(115200,1,0);
		break;
	}
}

void FTPod::tuneSynth(uint16_t actionID)
{
	#if DEBUG_POD
	//Serial.printf("~FTPod::conduct(): Act %i -> tuneSynth: ID %i\n", mAct,actionID);
	#endif
	switch(actionID)
	{
		case 0:
		//Velocity max, update note example
		Synth->updateVelocity(127);
		Synth->updateNote(Synth->mapDataToNote(Sensor->mCurrentSensorValue, NOTE_C3, NOTE_A6, MINOR, MINOR_LEN));
		break;

		case 1:
		//Velocity max to enabled POD, silenced for disable PODs
		if (Score->getPodPermission(mAct,mPodChannel))
		{
			Synth->updateVelocity(127);
		}
		else
		{
			Synth->updateVelocity(0);
		}
		Synth->updateNote(Synth->mapDataToNote(Sensor->mCurrentSensorValue, NOTE_C3, NOTE_A6, MINOR, MINOR_LEN));
		break;

		case 2:
		//Totally silenced
		Synth->updateVelocity(0);
		break;
	}
}

void FTPod::sendCom()
{
	//Update the messages in Com with the states of Score, and complementary necessary messages

}
