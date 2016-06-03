/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTMotor.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTMotor.h"

FTMotor::FTMotor(int stepPin, int dirPin)
{
	//Configure stepper
	stepper = new AccelStepper(AccelStepper::FULL2WIRE, stepPin, dirPin);
	stepper->setMaxSpeed(MAXSPEED);
  	stepper->setSpeed(0);
  	mSpeed = 0;
  	stepper->setCurrentPosition(0);
}

void FTMotor::update() {
	//Move motor
	stepper->setSpeed(mSpeed);
	stepper->runSpeedToPosition();
}