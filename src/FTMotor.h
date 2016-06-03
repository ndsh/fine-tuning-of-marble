/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTMotor.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTMotor_h
#define FTMotor_h

//Definitions
#define MAXSPEED 20000
#define MINSPEED 100
#define FULLREVOLUTION 25600

//AccelStepper Library
#include <AccelStepper.h>

class FTMotor
{
  public:
    FTMotor(int stepPin, int dirPin);
    void update();
    AccelStepper* stepper = nullptr;
  private:
  	int mSpeed;
};

#endif