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
/* include all other classes here */
#include "MacAddress.h"
#include "SensorHead.h"
#include "Motor.h"
#include "../inc/Scales.h"

class StateMachine {
	public:
		StateMachine(uint8_t _sensorPin, uint8_t _ledPin);
		void update();
		void setState();
		void getState();


	private:
		SensorHead* Sensor = nullptr;
		#define INTRO 0
		#define MOVE 1
		#define IDLE 2
		#define SENSOR 3
		int state = INTRO;
};

#endif