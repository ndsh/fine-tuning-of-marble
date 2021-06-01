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
      · motor->setConstantSpeed(0.5);
      · motor->rotate(2,1);

      # Rotate two times, with acceleration, half ramp both IN and OUT, full max speed
      · motor->setAccelSpeed(0.5,0.5,1);
      · motor->rotate(2,1);

      # Run to an absolute position, clockwise, with acceleration, half ramp both IN and OUT,
        full max speed, no extra revolutions
      · motor->setAccelSpeed(0.5,0.5,1);
      · motor->runTo(40000,1,0);

      · · · · · · · · · · · · · · · · · · · · ·
*/

/*
    thoughts on how many steps or data should be capture in a loop
    full step         = 200 steps * 1,8°     = 360°
    half microsteps   = 400 steps * 0,9°     = 360°
    1/4 microsteps    = 800 steps * 0,45°    = 360°
    1/8 microsteps    = 1600 steps * 0,225°  = 360°
    1/16 microsteps   = 3200 steps * 0,1125° = 360°
    1/32 microsteps   = 6400 * 0,05° = 360°  = 360°

*/


#ifndef MOTOR_H
#define MOTOR_H

#define MAXSPEED 1800 // 18000 previous
#define MINSPEED 200
#define DEBUG_MOTOR true

#include <AccelStepper.h>

class Motor {
  public:
  	Motor(int stepPin, int dirPin, long fullRevolution);

  	AccelStepper* stepper = nullptr;
    float speed; //Contains current motor speed
    float rangeIn; //Contains the current length of the "IN" motion of the motor in acceleration mode.
    float rangeOut;  //Contains the current length of the "OUT" motion of the motor in acceleration mode.
    float maxSpeedFactor;  //Limits the max speed of the motor in acceleration mode.
  	bool isConstant;  //Flag for checking wether the motor is at contant speed mode or accelerating.
    int counter; //Keeps track of how many movements have been completed by the motor.

    void update();
    void rotate(float times, int direction);
    void rotateDegrees();
    void home();
    void runTo(long relativePos, int direction, int rotations);
    void stop();
    void setConstantSpeed(float speedFactor);
    void setAccelSpeed(float in, float out, float maxSpeedLimiter);
    void updateCounter();
    bool isMoving();
    long getCurrentAbsolutePosition();
    long getCurrentRelativePosition();
    int getTotalMovements();
    void setMicrostepping(uint8_t m0, uint8_t m1, uint8_t m2);

  private:
    long lastPos; //Contains the last relative position before starting movement.
    long targetPos; //Contains the target position (in motion).
    long targetDistance; //Contains the distance to go to a certain position.
    long fullRev; //Keeping FULLREV value

    uint8_t stepPin;
    uint8_t dirPin;
    uint8_t m0pin;
    uint8_t m1pin;
    uint8_t m2pin;
    uint8_t enablePin;

  	long getNewTargetRelativePosition(long _newAbsolutePos, int _direction, int _revolutions);
    long getAbsoluteDistance(long _lastPos, long _newPos);
  	void updateSpeed();
};

#endif