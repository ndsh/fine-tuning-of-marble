/*
    · · · · · · · · · · · · · · · · · · · · ·

    Motor.h
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

    
/*
    · · · · · · · · · · · · · · · · · · · · ·

      Motor - usage examples

      # Rotate two times, in half of constant speed, clockwise
      · Motor->setConstantSpeed(0.5);
      · Motor->rotate(2,1);

      # Rotate two times, with acceleration, half ramp both IN and OUT, full max speed
      · Motor->setAccelSpeed(0.5,0.5,1);
      · Motor->rotate(2,1);

      # Run to an absolute position, clockwise, with acceleration, half ramp both IN and OUT,
        full max speed, no extra revolutions
      · Motor->setAccelSpeed(0.5,0.5,1);
      · Motor->runTo(40000,1,0);

    · · · · · · · · · · · · · · · · · · · · ·
*/


#ifndef MOTOR_H
#define MOTOR_H

#define MAXSPEED 18000
#define MINSPEED 200
#define DEBUG_MOTOR false

#include <AccelStepper.h>

class Motor {
  public:
  	Motor(int stepPin, int dirPin, long fullRevolution);

  	AccelStepper* stepper = nullptr; //Main stepper instance
    float speed; //Contains current motor speed
    float rangeIn; //Contains the current length of the "IN" motion of the motor in acceleration mode.
    float rangeOut;  //Contains the current length of the "OUT" motion of the motor in acceleration mode.
    float maxSpeedFactor;  //Limits the max speed of the motor in acceleration mode.
  	bool isConstant;  //Flag for checking wether the motor is at contant speed mode or accelerating.
    int counter; //Keeps track of how many movements have been completed by the motor.

    void update();
    void rotate(float times, int direction);
    void runTo(long relativePos, int direction, int rotations);
    void stop();
    void setConstantSpeed(float speedFactor);
    void setAccelSpeed(float in, float out, float maxSpeedLimiter);
    void updateCounter();
    bool isMoving();
    long getCurrentAbsolutePosition();
    long getCurrentRelativePosition();
    int getTotalMovements();

  private:
    long lastPos; //Contains the last relative position before starting movement.
    long targetPos; //Contains the target position (in motion).
    long targetDistance; //Contains the distance to go to a certain position.
    long fullRev; //Keeping FULLREV value

  	long getNewTargetRelativePosition(long _newAbsolutePos, int _direction, int _revolutions);
    long getAbsoluteDistance(long _lastPos, long _newPos);
  	void updateSpeed();
};

#endif
