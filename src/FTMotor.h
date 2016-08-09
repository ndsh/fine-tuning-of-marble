/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTMotor.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 Motor -> usage examples (use at FTPod or any parent)

 #Rotate two times, in half of constant speed, clockwise
 Motor->setConstantSpeed(0.5);
 Motor->rotate(2,1);

 #Rotate two times, with acceleration, half ramp both IN and OUT, full max speed
 Motor->setAccelSpeed(0.5,0.5,1);
 Motor->rotate(2,1);

 #Run to an absolute position, clockwise, with acceleration, half ramp both IN and OUT, full max speed, no extra revolutions
 Motor->setAccelSpeed(0.5,0.5,1);
 Motor->runTo(40000,1,0);

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTMotor_h
#define FTMotor_h

//Definitions
#define MAXSPEED 18000
#define MINSPEED 200
#define DEBUG_MOTOR false

//AccelStepper Library
#include <AccelStepper.h>

class FTMotor
{
  public:

  	FTMotor(int stepPin, int dirPin, long fullRevolution);

  	AccelStepper* mStepper = nullptr; //Main stepper instance
    float mSpeed; //Contains current motor speed
    float mRangeIn; //Contains the current length of the "IN" motion of the motor in acceleration mode.
    float mRangeOut;  //Contains the current length of the "OUT" motion of the motor in acceleration mode.
    float mMaxSpeedFactor;  //Limits the max speed of the motor in acceleration mode.
  	bool mIsConstant;  //Flag for checking wether the motor is at contant speed mode or accelerating.
    int mCounter; //Keeps track of how many movements have been completed by the motor.

    void update();
    void rotate(float times,int direction);
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
    long mLastPos; //Contains the last relative position before starting movement.
    long mTargetPos; //Contains the target position (in motion).
    long mTargetDistance; //Contains the distance to go to a certain position.
    long fullRev; //Keeping FULLREV value

  	long getNewTargetRelativePosition(long newAbsolutePos, int direction, int revolutions);
    long getAbsoluteDistance(long lastPos, long newPos);
  	void updateSpeed();
};

#endif
