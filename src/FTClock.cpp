/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTClock.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTClock.h"

FTClock::FTClock()
{
	cIsOn = false;
	cIsMaster = false;
	cPulseCount = 0;
	cLast = 0;
	cNext = 0;
	cPulse = false;
}

void FTClock::update() {
	if (cIsOn && cIsMaster)
	{
		if(millis() >= cNext)
		{
			cPulse = true;
			calcIntervals();
			cPulseCount++;
			#if DEBUG_CLOCK
			Serial.print("FTClock -> cPulseCount: ");
			Serial.println(cPulseCount);
			#endif
		}
		else
		{
			cPulse = false;
		}
	}
}

void FTClock::startClock() {
	//Evaluate wether a delay or any other action is needed
	cIsOn = true;
	if (cIsMaster)
	{
		calcIntervals();
	}
}

void FTClock::setMaster(bool isMaster) {
	cIsMaster = isMaster;
}

void FTClock::resetClock() {
	cPulseCount = 0;
	calcIntervals();
}

uint16_t FTClock::readClock() {
	return cPulseCount;
}

bool FTClock::readPulse()
{
	return cPulse;
}

bool FTClock::isOn() {
	return cIsOn;
}

void FTClock::updatePulse() {
	cPulseCount++;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTClock::calcIntervals()
{
	cLast = millis();
	cNext = cLast + PULSE_INTERVAL;
}
