/*
    · · · · · · · · · · · · · · · · · · · · ·

    StateMachine.cpp
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#include "StateMachine.h"

StateMachine::StateMachine(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution) {
	#if DEBUG_STATEMACHINE
	  Serial.println("~StateMachine: Setup");
	#endif

	motor = new Motor(motorDirPin, motorStepPin, fullRevolution);
	sensor = new SensorHead(sensorPin, ledPin, fullRevolution);
	synth = new Synth();

	state = MOVE;

	timestamp = 0;
	interval = 6000;
}

void StateMachine::update() {
	#if DEBUG_STATEMACHINE
		Serial.print("~StateMachine: state=");
		Serial.println(state);
	#endif
	switch(state) {
		case INTRO:
			Serial.println("Intro");
			state = FTMTEST;
		break;

		case FTMTEST:
			if(millis() - timestamp > interval) {
				timestamp = millis();
				state = MOVE;
			}
			sensor->update(motor->getCurrentAbsolutePosition());			
			motor->update();
			synth->playNote();
		break;

		case MOVE:
			Serial.println("~StateMachine: MOVE");

			motor->setConstantSpeed(0.5);
      		motor->rotate(1,1);

      		//Motor->setAccelSpeed(0.5,0.5,1);
			//Motor->rotate(1,1);
			motor->update();

			
			if(millis() - timestamp > interval) {
				timestamp = millis();
				state = SENSOR;
			}
		break;

		case IDLE:
			Serial.println("Idle");

			if(millis() - timestamp > interval) {
				timestamp = millis();
				state = SENSOR;
				Serial.println("Switch to next state= SENSOR");
			}
			
		break;

		case SENSOR:
			Serial.println("Sensor");
			//sensor->read();
			sensor->toggleLED();
			//state = FTMTEST;
			if(millis() - timestamp > interval) {
				timestamp = millis();
				state = FTMTEST;
			}
		break;
	}
	Serial.println("· · · · · · · · · · · · · · · · · · · · ·");
	Serial.println();
}