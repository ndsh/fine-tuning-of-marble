/*

    ./~     FTCom.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble
	
	./~		[?] Please refer to: https://www.pjrc.com/teensy/td_libs_MIDI.html

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
    
*/


#include "FTCom.h"

FTCom::FTCom(uint8_t onboardLedPin)
{

	MIDI.begin();

	//Set initial variables
	mPulseCount = 0;
	mStart = true; //Change to *true* in case testing/debugging without COM & the other PODs

	mOnboardLedPin = onboardLedPin;

	startSequence();
	
}

void FTCom::update() {
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTCom::turnOnLED() {
	digitalWrite(mOnboardLedPin, HIGH);
}

void FTCom::turnOffLED() {
	digitalWrite(mOnboardLedPin, LOW);
}

void FTCom::startSequence() {
	turnOnLED();
	delay(50);
	turnOffLED();
	delay(30);
	turnOnLED();
	delay(50);
	turnOffLED();
	delay(70);
	turnOnLED();
	delay(50);
	turnOffLED();
	delay(30);
}


void FTCom::write(byte flag, byte data, byte channel) {
	MIDI.sendNoteOn(flag, data, channel);
	#if DEBUG_COM
	//Serial.print("FTCom -> pulse send to: ");
	//Serial.println(i);
	#endif
}

void FTCom::write(byte flag, byte data) {
	for(int i = 0; i<7; i++) {
    	MIDI.sendNoteOn(flag, data, i);
    	#if DEBUG_COM
    	//Serial.print("FTCom -> pulse send to: ");
    	//Serial.println(i);
    	#endif
    }	
}

byte FTCom::read(byte _flag) {
	// not finished yet.
	// flag = what we are waiting/looking for
	if (MIDI.read()) {                    // Is there a MIDI message incoming ?
		#if DEBUG_COM
    	Serial.print("FTCom -> pulse received: ");
    	#endif
	    byte type = MIDI.getType();
	    byte flag = 0;
	    byte read = 0;
	    switch (type) {
	      case NoteOn:
	      	flag = MIDI.getData1();
	        read = MIDI.getData2();
	        if(flag == _flag) return read;
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
	  	return 0;
  	} else return 0;
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
	return mStart;
}
uint16_t FTCom::getPulseCount(){
	return mPulseCount;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTCom::pulse(){
	mPulseCount++;
}
