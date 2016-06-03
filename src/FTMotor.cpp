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
  	stepper->setCurrentPosition(0);

  	//Set initial states
  	mSpeed = 0;
  	mCurveIn = 0;
  	mCurveOut = 0;
  	mMaxSpeedFactor = 1;
  	mIsConstant = false;
}

void FTMotor::update() {
	//Update speed
	stepper->setSpeed(getCurrentSpeed());
	//Move motor
	stepper->runSpeedToPosition();
}

 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTMotor::rotate(float times,int direction)
{
	//Rotate the motor to times * full revolution.
	long relativePos = getRelativePos(FULLREV*times,direction);
	stepper->moveTo(relativePos);
}

void FTMotor::moveTo(long absolutePos, int direction)
{
	//Converts an absolute position (0 to FULLREV)
	//lockDirection = -1 counterclockwise, 0 the closest, 1 clockwise
	long relativePos = getRelativePos(absolutePos,constrain(direction,-1,1));

	//Moves the motor to the relative position
	stepper->moveTo(relativePos);
}

void FTMotor::stop()
{
	mIsConstant = true;
	mSpeed = 0;
}

void FTMotor::setConstantSpeed(float speedFactor)
{
	//Linear constant speed of speedFactor (-1 to 1) * MAXSPEED
	//Positive = CLOCKWISE, Negative = COUNTER CLOCKWISE
	mIsConstant = true;
	mSpeed = MAXSPEED * constrain(speedFactor,-1,1);
}

void FTMotor::setSpeedCurve(float in, float out, float maxSpeedLimiter)
{
	//in (0 to 1), define length of ease in curve
	//out (0 to 1), define length of ease out curve
	//speedFactor (0 to 1) limits the MAXSPEED (height) of the motion curve
	mCurveIn = constrain(in,0,1);
	mCurveOut = constrain(out,0,1);
	mMaxSpeedFactor = constrain(maxSpeedLimiter,0,1);
	mIsConstant = false;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

long FTMotor::getRelativePos(long absolutePos, int direction)
{
	//Calculates a relative position to an absolute one (0 to FULLREV)
	long pos = 0;
	//!!!!! IN DEVELOPMENT
	return pos;
}

int FTMotor::getCurrentSpeed()
{
	if (!mIsConstant)
	{
		//Calculate the current speed in acceleration
		//!!!!! IN DEVELOPMENT
	}
	return mSpeed;
}



