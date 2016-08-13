/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTCom.cpp
 Copyright (c) 2016 The Fine Tuning of Marble

 Please refer to: https://www.pjrc.com/teensy/td_libs_MIDI.html
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTCom.h"
#include "MIDI.h"

FTCom::FTCom(uint8_t onboardLedPin)
{

	MIDI.begin();

	//Retrieve POD's mac address
	retrieveMacAddress();

	//Set initial variables
	cPulseCount = 0;
	cStart = true; //Change to *true* in case testing/debugging without COM & the other PODs

	onboardLedPin = onboardLedPin;
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

bool FTCom::pulseIn() {
	if (MIDI.read()) {                    // Is there a MIDI message incoming ?
		#if DEBUG_COM
    	Serial.print("FTCom -> pulse received: ");
    	#endif
	    byte type = MIDI.getType();
	    byte pulseValue = 0;
	    switch (type) {
	      case ControlChange:
	        pulseValue = MIDI.getData2();
	      	#if DEBUG_COM
	      	/*
	    	Serial.print(note);
	    	Serial.print("\t");
	    	Serial.print(velocity);
	    	Serial.print("\t");
	    	Serial.println(channel);
	    	*/
	    	#endif
	      break;
	  	}
	  	return pulseValue;
  	} else return 0;
}

void FTCom::pulseOut(bool pulse) {
	// is master?
    for(int i = 0; i<7; i++) {
    	// sendNoteOn: flag 0  / pulse = either 0 or 1 (no / yes) / all channels
    	MIDI.sendControlChange(0, pulse, i);
    	#if DEBUG_COM
    	//Serial.print("FTCom -> pulse send to: ");
    	//Serial.println(i);
    	#endif
    }
}

bool FTCom::hasStarted(){
	return cStart;
}
uint16_t FTCom::getPulseCount(){
	return cPulseCount;
}

void FTCom::turnOnLED() {
	digitalWrite(onboardLedPin, HIGH);
}

void FTCom::turnOffLED() {
	digitalWrite(onboardLedPin, LOW);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTCom::pulse(){
	cPulseCount++;
}
