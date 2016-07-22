/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTMotor.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTMotor.h"

FTMotor::FTMotor(int stepPin, int dirPin, long fullRevolution)
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
	mTargetPos = mLastPos + (fullRev * rotations * direction);
	mTargetDistance = getAbsoluteDistance(mLastPos,mTargetPos);
	mStepper->moveTo(mTargetPos);

	#if DEBUG_MOTOR
		Serial.print("FTMotor -> rotate: ");
		Serial.print(rotations);
		Serial.print("times / direction: ");
		Serial.print(direction);
		Serial.print(" / mTargetPos: ")
		Serial.println(mTargetPos);
	#endif
}

void FTMotor::runTo(long absolutePos, int direction, int rotations)
{
	//Direction = -1 counterclockwise, 0 the closest, 1 clockwise
	mLastPos = mStepper->currentPosition();
	mTargetPos = getNewTargetRelativePosition(absolutePos,direction,rotations);
	mTargetDistance = getAbsoluteDistance(mLastPos,mTargetPos);
	mStepper->moveTo(mTargetPos);

	#if DEBUG_MOTOR
		Serial.print("FTMotor -> runTo: ");
		Serial.print("mLastPos: ");
		Serial.print(mLastPos);
		Serial.print(" mTargetPos: ");
		Serial.print(mTargetPos);
		Serial.print(" mTargetDistance: ");
		Serial.println(mTargetDistance);
	#endif
}

void FTMotor::stop()
{
	mLastPos = mStepper->currentPosition();
	mIsConstant = true;
	mSpeed = 0;
	#if DEBUG_MOTOR
		Serial.println("FTMotor -> stop() ");
	#endif
}

void FTMotor::setConstantSpeed(float speedFactor)
{
	//Linear constant speed of speedFactor (0 to 1) * MAXSPEED
	mIsConstant = true;
	mSpeed = MAXSPEED * speedFactor;
	#if DEBUG_MOTOR
		Serial.println("FTMotor -> setConstantSpeed: ");
		Serial.println(mSpeed);
	#endif
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
	#if DEBUG_MOTOR
		Serial.println("FTMotor -> setAccelSpeed() ");
	#endif
}

bool FTMotor::isMoving()
{
	if (mStepper->distanceToGo() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

long FTMotor::getCurrentAbsolutePosition()
{
	//Calculates an absolute position (0 to fullRev) relative to the current relative one
	long currentRelativePos = mStepper->currentPosition();
	int currentRevolutions = (int) currentRelativePos / fullRev;
	long absolutePos = abs(currentRelativePos - (fullRev * currentRevolutions));

	#if DEBUG_MOTOR
		Serial.print("FTMotor -> getCurrentAbsolutePosition: ");
		Serial.println(absolutePos);
	#endif

	return absolutePos;
}

long FTMotor::getCurrentRelativePosition()
{
	#if DEBUG_MOTOR
		Serial.print("FTMotor -> getCurrentRelativePosition: ");
		Serial.println(relativePos);
	#endif
	return mStepper->currentPosition();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

long FTMotor::getNewTargetRelativePosition(long newAbsolutePos, int direction, int rotations)
{
	//Calculates a relative position relative to an absolute one (0 to fullRev)
	//Does further recquired calculations regarding extra rotations and direction to move
	long currentRelativePos = mStepper->currentPosition();
	int currentRevolutions = (int) currentRelativePos / fullRev;
	long newRelativePos = (currentRevolutions * fullRev) + newAbsolutePos;

	switch (direction){
		case -1:
		//CCW
		if (currentRelativePos < 0)
		{
			newRelativePos -= (fullRev*2);
		}
		else
		{
			newRelativePos -= (fullRev);
		}
		newRelativePos -= (fullRev * rotations);
		break;

		case 0:
		newRelativePos += fullRev * rotations;
		break;

		case 1:
		//CW
		newRelativePos += fullRev;
		newRelativePos += (fullRev * rotations);
		break;
	}

	return newRelativePos;
}

long FTMotor::getAbsoluteDistance(long lastPos, long newPos)
{
	long distance;
	distance = newPos - lastPos;
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

	if (mLastPos > mTargetPos)
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
        		newSpeed = map(currentPos, posOUT, mTargetPos, mMaxSpeed, MINSPEED);
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
        		newSpeed = map(currentPos, posOUT, mTargetPos, mMaxSpeed, MINSPEED);
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

	/*
	#if DEBUG_MOTOR
		Serial.print("FTMotor -> updatedSpeed: ");
		Serial.print("mLastPos: ");
		Serial.print(mLastPos);
		Serial.print(" mTargetPos: ");
		Serial.print(mTargetPos);
		Serial.print(" mTargetDistance: ");
		Serial.print(mTargetDistance);
		Serial.print("currentPos: ");
		Serial.print(currentPos);
		Serial.print(" posIN: ");
		Serial.print(posIN);
		Serial.print(" posOUT: ");
		Serial.print(posOUT);
		Serial.print(" newSpeed: ");
		Serial.println(newSpeed);
	#endif
	*/
}


