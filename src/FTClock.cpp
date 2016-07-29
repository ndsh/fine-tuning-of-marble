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
}

void FTClock::update() {
	if (cIsOn && cIsMaster)
	{
		if(millis() >= cNext)
		{
			calcIntervals();
			cPulseCount++;
			#if DEBUG_CLOCK
			Serial.print("FTClock -> cPulseCount: ");
			Serial.println(cPulseCount);
			#endif
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

void FTClock::updatePulse(uint16_t newPulseCount) {
	cPulseCount = newPulseCount;
}

void FTClock::resetClock() {
	cPulseCount = 0;
	calcIntervals();
}

uint16_t FTClock::getCount() {
	return cPulseCount;
}

bool FTClock::isOn() {
	return cIsOn;
}

bool FTClock::isClockMaster() {
	return cIsMaster;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTClock::calcIntervals()
{
	cLast = millis();
	cNext = cLast + PULSE_INTERVAL;
}