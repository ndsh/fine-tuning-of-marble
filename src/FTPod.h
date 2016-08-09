/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTPod.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTPod_h
#define FTPod_h

//Main includes
#include <Arduino.h>
#include "FTScore.h"
#include "FTClock.h"
#include "FTMotor.h"
#include "FTSensor.h"
#include "FTSynth.h"
#include "FTCom.h"

//AO Library
#include <Scale.h>

//Definitions
#define DEBUG_POD false

class FTPod
{
  public:

    FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, long fullRevolution);

    void update();
    bool _isPodZero = false; //Flag to the sign who is the Pod that dictates the time.
    int podState; //Contains the main state number of the POD. Each state action is defined by the Score.
    int movCounter; //Keeps track of the number of movements started by the motor.
    long fullRev; //Keeping FULLREV value
    int mID;

  private:

  	FTScore* Score = nullptr;
  	FTClock* Clock = nullptr;
  	FTMotor* Motor = nullptr;
  	FTSensor* Sensor = nullptr;
  	FTSynth* Synth = nullptr;
  	FTCom* Com = nullptr;
    uint8_t startPin;

    void receiveCom();
    void setClock();
    void conductScore();
    void parseSensor();
    void moveMotor();
    void tuneSynth();
};

#endif
