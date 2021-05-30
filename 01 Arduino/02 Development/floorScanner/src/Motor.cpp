/*
    · · · · · · · · · · · · · · · · · · · · ·

    Motor.cpp
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#include "Motor.h"

Motor::Motor(int stepPin, int dirPin, long fullRevolution) {
	#if DEBUG_MOTOR
		Serial.println("~Motor: created");
	#endif

	stepper = new AccelStepper(AccelStepper::FULL2WIRE, stepPin, dirPin);
	stepper->setMaxSpeed(MAXSPEED);
	stepper->setSpeed(0);
	stepper->setCurrentPosition(0);

	speed = 0;
	rangeIn = 0;
	rangeOut = 0;
	maxSpeedFactor = 1;
	isConstant = false;
	counter = 0;
  	fullRev = fullRevolution;
}

void Motor::update() {
	if (!isConstant) updateSpeed();
	stepper->setSpeed(speed);
	stepper->runSpeedToPosition();
}

// Rotate the motor to times * full revolution.
// Direction = -1 counterclockwise, 1 clockwise
void Motor::rotate(float rotations, int direction) {
	lastPos = stepper->currentPosition();
	targetPos = lastPos + (fullRev * rotations * direction);
	targetDistance = getAbsoluteDistance(lastPos,targetPos);
	stepper->moveTo(targetPos);

	#if DEBUG_MOTOR
		Serial.print("~Motor::rotate()-› ");
		Serial.print(rotations);
		Serial.print("times / direction: ");
		Serial.print(direction);
		Serial.print(" / targetPos: ");
		Serial.println(targetPos);
	#endif
}

void Motor::runTo(long absolutePos, int direction, int rotations) {
	#if DEBUG_MOTOR
		Serial.print("~Motor::runTo()-› absolutePos: ");
		Serial.print(absolutePos);
		Serial.print(" direction: ");
		Serial.print(direction);
		Serial.print(" rotations: ");
		Serial.println(rotations);
	#endif

	//Direction = -1 counterclockwise, 0 the closest, 1 clockwise
	lastPos = stepper->currentPosition();
	targetPos = getNewTargetRelativePosition(absolutePos,direction,rotations);
	targetDistance = getAbsoluteDistance(lastPos,targetPos);
	stepper->moveTo(targetPos);
}

void Motor::stop() {
	lastPos = stepper->currentPosition();
	isConstant = true;
	speed = 0;
	#if DEBUG_MOTOR
		Serial.println("~Motor::stop()");
	#endif
}

// Linear constant speed of speedFactor (0 to 1) * MAXSPEED
void Motor::setConstantSpeed(float speedFactor) {
	isConstant = true;
	speed = MAXSPEED * speedFactor;
	#if DEBUG_MOTOR
		Serial.print("~Motor::setConstantSpeed()-› ");
		Serial.println(speed);
	#endif
}

// in (0 to 1), define length of ease in curve
// out (0 to 1), define length of ease out curve
// speedFactor (0 to 1) limits the MAXSPEED (height) of the motion curve
void Motor::setAccelSpeed(float in, float out, float maxSpeedLimiter) {
	isConstant = false;
	rangeIn = in;
	rangeOut = out;
	maxSpeedFactor = maxSpeedLimiter;
	#if DEBUG_MOTOR
		Serial.print("~Motor::setAccelSpeed()-› in: ");
		Serial.print(in);
		Serial.print(" out: ");
		Serial.print(out);
		Serial.print(" maxSpeedLimiter: ");
		Serial.println(maxSpeedLimiter);
	#endif
}

bool Motor::isMoving() {
	if (stepper->distanceToGo() == 0) {
		return false;
	} else {
		return true;
	}
}

// Calculates an absolute position (0 to fullRev) relative to the current relative one
long Motor::getCurrentAbsolutePosition() {

	// Main calculation
	long currentRelativePos = stepper->currentPosition();
	int currentRevolutions;
	long absolutePos;
	
	if (currentRelativePos < 0) {
		currentRevolutions = abs(floor(currentRelativePos / fullRev));
		absolutePos = currentRelativePos + (fullRev * currentRevolutions);
	} else {
		currentRevolutions = currentRelativePos / fullRev;
		absolutePos = currentRelativePos - (fullRev * currentRevolutions);
	}

	//Correction of range (from -fullRev to fullRev, to 0 to fullRev)
	if (absolutePos < 0) {
		absolutePos += fullRev;
	}

	#if DEBUG_MOTOR
		Serial.print("~Motor::getCurrentAbsolutePosition()-› currentRelativePos: ");
		Serial.print(currentRelativePos);
		Serial.print(" currentRevolutions: ");
		Serial.print(currentRevolutions);
		Serial.print(" currentAbsolutePos: ");
		Serial.println(absolutePos);
	#endif

	return absolutePos;
}

long Motor::getCurrentRelativePosition() {
	long relativePos = stepper->currentPosition();
	#if DEBUG_MOTOR
		Serial.print("~Motor::getCurrentRelativePosition()-› ");
		Serial.println(relativePos);
	#endif
	return relativePos;
}

int Motor::getTotalMovements() {
	#if DEBUG_MOTOR
		Serial.print("~Motor::getNumberOfMovements()-› ");
		Serial.println(counter);
	#endif
	return counter;
}

void Motor::updateCounter() {
	counter++;
	#if DEBUG_MOTOR
		Serial.print("~Motor::updateCounter()-› ");
		Serial.println(counter);
	#endif
}

/*
	· · · · · · · · · · · · · · · · · · · · ·
		PRIVATE
	· · · · · · · · · · · · · · · · · · · · ·
*/

// Calculates a relative position relative to an absolute one (0 to fullRev)
// Does further recquired calculations regarding extra locked direction or rotation
long Motor::getNewTargetRelativePosition(long newAbsolutePos, int direction, int rotations) {
	long newRelativePos = stepper->currentPosition();
	long currentAbsolutePos = getCurrentAbsolutePosition();
	long distance = newAbsolutePos - currentAbsolutePos;

	switch(direction) {
		case -1:
			if (distance < 0) {
				//Already going to -1
				newRelativePos += distance - (fullRev*rotations);
			} else {
				//Force to -1
				newRelativePos += distance - (fullRev*(rotations+1));
			}
		break;

		case 0:
			if (distance < 0) {
				//Going -1
				newRelativePos += distance - (fullRev*rotations);
			} else {
				//Going 1
				newRelativePos += distance + (fullRev*rotations);
			}
		break;

		case 1:
			if (distance < 0) {
				//Force to 1
				newRelativePos += distance + (fullRev*(rotations+1));
			} else {
				//Already going to 1
				newRelativePos += distance + (fullRev*rotations);
			}
		break;
	}

	#if DEBUG_MOTOR
		Serial.print("~Motor::getNewTargetRelativePosition()-› ");
		Serial.print("newAbsolutePos: ");
		Serial.print(newAbsolutePos);
		Serial.print(" distance: ");
		Serial.print(distance);
		Serial.print(" newRelativePos: ");
		Serial.println(newRelativePos);
	#endif

	return newRelativePos;
}

long Motor::getAbsoluteDistance(long lastPos, long newPos) {
	long distance;
	distance = newPos - lastPos;
	return distance;
}

// Calculate the current speed of the motor in acceleration using a linear ramp on the motor's speed.
void Motor::updateSpeed() {
	float newSpeed;
	float maxSpeed = MAXSPEED * maxSpeedFactor;
	long currentPos = stepper->currentPosition();
	long posIN = lastPos + (targetDistance * rangeIn * 0.5);
	long posOUT = (targetDistance + lastPos) - (targetDistance * rangeOut * 0.5);

	if (lastPos > targetPos) {
    	//Going backwards
    	if (currentPos >= posIN) {
      	//IN Ramp
      	newSpeed = map(currentPos, lastPos, posIN, MINSPEED, maxSpeed);
    	} else {
      		if (currentPos <= posOUT) {
        		//OUT Ramp
        		newSpeed = map(currentPos, posOUT, targetPos, maxSpeed, MINSPEED);
      		} else {
        		//Constant speed in between ramps
        		newSpeed = maxSpeed;
      		}
    	}
  	} else {
    	//Going forwards
    	if (currentPos <= posIN) {
      		//IN Ramp
      		newSpeed = map(currentPos, lastPos, posIN, MINSPEED, maxSpeed);
    	} else {
      		if (currentPos >= posOUT) {
        		//OUT Ramp
        		newSpeed = map(currentPos, posOUT, targetPos, maxSpeed, MINSPEED);
      		} else {
        		//Constant speed in between ramps
        		newSpeed = maxSpeed;
      		}
    	}
  	}

  	//Check if reached the destination to completely stop motor.
  	if (currentPos == targetPos) {
  		newSpeed = 0;
  	}

	speed = newSpeed;

	/*
	//The following debug messages are heavy to the Teensy. Use it only when extremely needed, and to short distances.
	#if DEBUG_MOTOR
		Serial.print("~Motor::updateSpeed()-› ");
		Serial.print("lastPos: ");
		Serial.print(lastPos);
		Serial.print(" targetPos: ");
		Serial.print(targetPos);
		Serial.print(" targetDistance: ");
		Serial.print(targetDistance);
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
