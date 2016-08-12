/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTCom.cpp
 Copyright (c) 2016 The Fine Tuning of Marble

 Please refer to: https://www.pjrc.com/teensy/td_libs_MIDI.html
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTCom.h"

FTCom::FTCom()
{
	//Retrieve POD's mac address
	retrieveMacAddress();

	//Set initial variables
	cPulseCount = 0;
	cStart = false; //Change to *true* in case testing/debugging without COM & the other PODs
}

void FTCom::update() {

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

String FTCom::getMacAddress() {
	return macAddress;
}

void FTCom::retrieveMacAddress() {
	macAddress = MacAddress::get();
  	#if DEBUG_COM
    Serial.print("FTCom -> retrieveMacAddress -> ");
    Serial.println(macAddress);
    #endif
}

bool FTCom::hasStarted(){
	return cStart;
}
uint16_t FTCom::getPulseCount(){
	return cPulseCount;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTCom::pulse(){
	cPulseCount++;
}
