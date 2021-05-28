/*
    · · · · · · · · · · · · · · · · · · · · ·

    StateMachine.cpp
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#include "StateMachine.h"

StateMachine::StateMachine(uint8_t _sensorPin, uint8_t _ledPin) {
	#if DEBUG
	  Serial.begin(57600);
	  Serial.println("~floorScanner: INIT");
	  Serial.println();
	#endif

	  Sensor = new SensorHead(_sensorPin, _ledPin);
}

void StateMachine::update() {
	switch(state) {
		case INTRO:
			Serial.println("Intro");
			state = MOVE;
		break;

		case MOVE:
			Serial.println("Move");
			state = IDLE;
		break;

		case IDLE:
			Serial.println("Idle");
			state = SENSOR;
		break;

		case SENSOR:
			Serial.println("Sensor");
			state = MOVE;
		break;
	}
}