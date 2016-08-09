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
	retrieveMacAddress();
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
    Serial.print("Your Teensy Mac Address is: ");
    Serial.println(macAddress);
    #endif
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
