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
	mLedState = LOW;
	mPreviousMillis = 0;
	mInterval = 1000;
	mStart = false; //Change to *true* in case testing/debugging without COM & the other PODs

	mOnboardLedPin = onboardLedPin;

	startSequence();

}

void FTCom::update() {
	
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTCom::turnOnLED() {
	mLedState = HIGH;
	digitalWrite(mOnboardLedPin, mLedState);
}

void FTCom::turnOffLED() {
	mLedState = LOW;
	digitalWrite(mOnboardLedPin, mLedState);
}

void FTCom::toggleLED() {
	unsigned long mCurrentMillis = millis();
	if (mCurrentMillis - mPreviousMillis >= mInterval) {
		mPreviousMillis = mCurrentMillis;
		if (mLedState == LOW) mLedState = HIGH;
		else mLedState = LOW;
		digitalWrite(mOnboardLedPin, mLedState);
	}
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
		Serial.print("~FTCom::write()-› \t");
		Serial.print(flag);
		Serial.print("\t");
		Serial.print(data);
		Serial.print("\t");
		Serial.println(channel);
	#endif
}

void FTCom::write(byte flag, byte data) {
	for(int i = 0; i<7; i++) {
    	MIDI.sendNoteOn(flag, data, i);
    	#if DEBUG_COM
    		Serial.print("~FTCom::write()-› \t");
    		Serial.print(flag);
    		Serial.print("\t");
    		Serial.println(data);
    	#endif
    }
}

byte FTCom::read(byte _flag) {
	// not finished yet.
	// flag = what we are waiting/looking for
	if (MIDI.read()) {                    // Is there a MIDI message incoming ?
		#if DEBUG_COM
			Serial.print("~FTCom::read()-› ");
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
		    	Serial.print(flag);
		    	Serial.print("\t");
		    	Serial.println(read);
	    	#endif
	      break;
	  	}
	  	return 0;
  	} else return 0;
}

bool FTCom::pulseIn() {
	if (MIDI.read()) {                    // Is there a MIDI message incoming ?
	    byte type = MIDI.getType();
	    byte flag = 0;
	    byte pulseValue = 0;
	    switch (type) {
	      case ControlChange:
	      	flag = MIDI.getData1();
	        pulseValue = MIDI.getData2();
	      	#if DEBUG_COM_PULSE
	      	if(pulseValue == 1) {
		      	Serial.print("~FTCom::pulseIn()-› ");
		    	Serial.print(flag);
		    	Serial.print("\t");
		    	Serial.println(pulseValue);
	    	}
	    	#endif
	      break;
	  	}
	  	return pulseValue;
  	} else return 0;
}

void FTCom::pulseOut(bool pulse) {
	#if DEBUG_COM_PULSE
		Serial.print("~FTCom::pulseOut()-› \t");
	#endif
    for(int i = 1; i<=7; i++) {
    	// sendNoteOn: flag 0  / pulse = either 0 or 1 (no / yes) / all channels
    	MIDI.sendControlChange(0, pulse, i);
    	#if DEBUG_COM_PULSE
    	Serial.print(i);
    	Serial.print("\t");
    	#endif
    }
    #if DEBUG_COM_PULSE
    	Serial.println();
	#endif
}

bool FTCom::hasStarted(){
	return mStart;
}

bool FTCom::podsDone(){
	//Write code here, checking wether all pods are indicating that they have concluded their tasks
	bool flag = false;
	return flag;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
