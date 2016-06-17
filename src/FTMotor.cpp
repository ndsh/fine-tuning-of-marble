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
	mStepper = new AccelStepper(AccelStepper::FULL2WIRE, stepPin, dirPin);
	mStepper->setMaxSpeed(MAXSPEED);
  	mStepper->setSpeed(0);
  	mStepper->setCurrentPosition(0);

  	//Set initial states
  	mSpeed = 0;
  	mRangeIn = 0;
  	mRangeOut = 0;
  	mMaxSpeedFactor = 1;
  	mIsConstant = false;
}

void FTMotor::update() {
	//Update speed
	if (!mIsConstant) updateSpeed();
	mStepper->setSpeed(mSpeed);
	//Move motor
	mStepper->runSpeedToPosition();
}

 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTMotor::rotate(float rotations,int direction)
{
	//Rotate the motor to times * full revolution.
	//Direction = -1 counterclockwise, 1 clockwise
	mLastPos = mStepper->currentPosition();
	mTargetPos = mLastPos + (FULLREV * rotations * direction);
	mTargetDistance = getAbsoluteDistance(mLastPos,mTargetPos);
	mStepper->moveTo(mTargetPos);
}

void FTMotor::runTo(long absolutePos, int direction)
{
	//Direction = -1 counterclockwise, 0 the closest, 1 clockwise
	mLastPos = mStepper->currentPosition();
	mTargetPos = getNewRelativePosition(absolutePos,direction);
	mTargetDistance = getAbsoluteDistance(mLastPos,mTargetPos);
	mStepper->moveTo(mTargetPos);
}

void FTMotor::stop()
{
	mLastPos = mStepper->currentPosition();
	mIsConstant = true;
	mSpeed = 0;
}

void FTMotor::setConstantSpeed(float speedFactor)
{
	//Linear constant speed of speedFactor (0 to 1) * MAXSPEED
	mIsConstant = true;
	mSpeed = MAXSPEED * speedFactor;
}

void FTMotor::setAccelSpeed(float in, float out, float maxSpeedLimiter)
{
	//in (0 to 1), define length of ease in curve
	//out (0 to 1), define length of ease out curve
	//speedFactor (0 to 1) limits the MAXSPEED (height) of the motion curve
	mIsConstant = false;
	mRangeIn = in;
	mRangeOut = out;
	mMaxSpeedFactor = maxSpeedLimiter;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

long FTMotor::getNewRelativePosition(long newAbsolutePos, int direction)
{
	//Calculates a relative position to an absolute one (0 to FULLREV)
	long newRelativePos = 0;
	long currentRelativePos = mStepper->currentPosition();
	long currentAbsolutePos	= currentRelativePos % FULLREV;
	int currentRevolutions = currentRelativePos / FULLREV;

	newRelativePos = (currentRevolutions * FULLREV) + newAbsolutePos;

	switch (direction){
		case -1:
		//CCW
		if (newRelativePos > currentAbsolutePos)
		{
			//FIX FOLLOWING:
			newRelativePos -= FULLREV;
		}
		break;

		case 1:
		//CW
		if (newRelativePos < currentAbsolutePos)
		{
			newRelativePos += FULLREV;
		}
		break;
	}

	return newRelativePos;
}

long FTMotor::getAbsoluteDistance(long lastPos, long newPos)
{
	long distance;
	if (lastPos > newPos)
	{
		distance = lastPos - newPos;
	}
	else
	{
		distance = newPos - lastPos;
	}
	return distance;
}

void FTMotor::updateSpeed()
{
	//Calculate the current speed of the motor in acceleration using a linear ramp on the motor's speed.
	float newSpeed;
	float mMaxSpeed = MAXSPEED * mMaxSpeedFactor;
	long currentPos = mStepper->currentPosition();
	long posIN = mLastPos + (mTargetDistance * mRangeIn * 0.5);
	long posOUT = (mTargetDistance + mLastPos) - (mTargetDistance * mRangeOut * 0.5);

	if (mLastPos > mTargetDistance)
  	{
    	//Going backwards
    	if (currentPos >= posIN)
    	{
      	//IN Ramp
      	newSpeed = map(currentPos, mLastPos, posIN, MINSPEED, mMaxSpeed);
    	}
    	else
    	{
      		if (currentPos <= posOUT)
      		{
        		//OUT Ramp
        		newSpeed = map(currentPos, posOUT, mTargetDistance, mMaxSpeed, MINSPEED);
      		}
      		else
      		{
        		//Constant speed in between ramps
        		newSpeed = mMaxSpeed;
      		}
    	}
  	}
  	else
  	{
    	//Going forwards
    	if (currentPos <= posIN)
    	{
      		//IN Ramp
      		newSpeed = map(currentPos, mLastPos, posIN, MINSPEED, mMaxSpeed);
    	}
    	else
    	{
      		if (currentPos >= posOUT)
      		{
        		//OUT Ramp
        		newSpeed = map(currentPos, posOUT, mTargetDistance, mMaxSpeed, MINSPEED);
      		}
      		else
      		{
        		//Constant speed in between ramps
        		newSpeed = mMaxSpeed;
      		}
    	}
  	}

  	//Check if reached the destination to completely stop motor.
  	if (currentPos == mTargetPos)
  	{
  		newSpeed = 0;
  	}

	mSpeed = newSpeed;
}





