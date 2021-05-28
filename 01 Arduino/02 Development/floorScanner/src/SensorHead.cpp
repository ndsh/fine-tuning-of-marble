/*
    · · · · · · · · · · · · · · · · · · · · ·

    SensorHead.h
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#include "SensorHead.h"

SensorHead::SensorHead(uint8_t _sensorPin, uint8_t _ledPin) {
	pinMode(sensorPin, INPUT);
	pinMode(ledPin, OUTPUT);
	sensorPin = _sensorPin;
	ledPin = _ledPin;
}

void SensorHead::update() {}

void SensorHead::read() {}

void SensorHead::toggleLED(bool b) {
	if(b) digitalWrite(pinLed, HIGH);
	else digitalWrite(pinLed, LOW);
}

void SensorHead::toggleDataParsing(bool b) {
	isParsing = b;
}