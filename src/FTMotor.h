/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTMotor.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTMotor_h
#define FTMotor_h

//Definitions
#define MAXSPEED 18000
#define MINSPEED 100
#define FULLREV 25600

//AccelStepper Library
#include <AccelStepper.h>

class FTMotor
{
  public:

  	FTMotor(int stepPin, int dirPin);

  	AccelStepper* stepper = nullptr;
    int mSpeed;
  	int mCurveIn;
  	int mCurveOut;
  	int mMaxSpeedFactor;
  	bool mIsConstant;

    void update();
    void rotate(float times,int direction);
    void moveTo(long absolutePos, int direction);
    void stop();
    void setConstantSpeed(float speedFactor);
    void setSpeedCurve(float in, float out, float maxSpeedLimiter);

  private:

  	long getRelativePos(long absolutePos, int direction);
  	int getCurrentSpeed();

};

#endif