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
#include <CFOSynthesizer.h>
#include <CFOMidi.h>
#include <Scale.h>
#include <MacAddress.h>

//Definitions
#define DEBUG_POD false

class FTPod
{
  public:

    FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, long fullRevolution);

    void update();

    long fullRev; //Keeping FULLREV value

  private:

  	FTScore* Score = nullptr;
  	FTClock* Clock = nullptr;
  	FTMotor* Motor = nullptr;
  	FTSensor* Sensor = nullptr;
  	FTSynth* Synth = nullptr;
  	FTCom* Com = nullptr;

    void receiveCom();
    void setClock();
    void conductScore();
    void moveMotor();
    void tuneSynth();
};

#endif