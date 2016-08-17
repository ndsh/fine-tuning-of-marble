/*

    ./~     FTClock.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble
	

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
    
*/

#include "FTClock.h"

FTClock::FTClock()
{
	mIsOn = false;
	mIsMaster = false;
	mPulseCount = 0;
	mLast = 0;
	mNext = 0;
	mPulse = false;
}

void FTClock::update() {
	if (mIsOn && mIsMaster)
	{
		if(millis() >= mNext)
		{
			mPulse = true;
			calcIntervals();
			mPulseCount++;
			#if DEBUG_CLOCK
				Serial.print("~FTClk::mPulseCount-› ");
				Serial.println(mPulseCount);
			#endif
		}
		else
		{
			mPulse = false;
		}
	}
}

void FTClock::startClock() {
	//Evaluate wether a delay or any other action is needed
	mIsOn = true;
	if (mIsMaster)
	{
		calcIntervals();
	}
}

void FTClock::setMaster(bool isMaster) {
	mIsMaster = isMaster;
}

void FTClock::resetClock() {
	mPulseCount = 0;
	calcIntervals();
}

uint16_t FTClock::readClock() {
	return mPulseCount;
}

bool FTClock::readPulse()
{
	return mPulse;
}

bool FTClock::isOn() {
	return mIsOn;
}

void FTClock::updatePulse() {
	mPulseCount++;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTClock::calcIntervals()
{
	mLast = millis();
	mNext = mLast + PULSE_INTERVAL;
}
