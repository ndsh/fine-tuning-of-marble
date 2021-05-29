/*
    · · · · · · · · · · · · · · · · · · · · ·

    StateMachine.cpp
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#include "StateMachine.h"

StateMachine::StateMachine(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution) {
	#if DEBUG
	  Serial.begin(57600);
	  Serial.println("~floorScanner: INIT");
	  Serial.println();
	#endif

	//motor = new Motor(motorDirPin, motorStepPin, fullRevolution);
	//sensor = new SensorHead(sensorPin, ledPin);
	synth = new Synth();

	//Sensor = new FTSensor(sensorPin,ledPin,fullRevolution);
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