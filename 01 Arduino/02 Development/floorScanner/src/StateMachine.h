/*
    · · · · · · · · · · · · · · · · · · · · ·

    StateMachine.h
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>
#include "MacAddress.h"
#include "Motor.h"
#include "SensorHead.h"
#include "Synth.h"
#include "inc/Scales.h"

#define INTRO 		0
#define MOVE 		1
#define IDLE 		2
#define SENSOR 		3
#define SYNTH 		4
#define FTMTEST 	5

#define DEBUG_STATEMACHINE false


// uint8_t totalPods, uint8_t score, uint16_t pulseInterval
class StateMachine {
	public:
		StateMachine(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution);
		void update();
		void setState(int state);
		int getState();
		void stateName();

	private:
		Motor* motor = nullptr;
		SensorHead* sensor = nullptr;
		Synth* synth = nullptr;
		int state;
		unsigned long timestamp;
		unsigned long interval;
};

#endif