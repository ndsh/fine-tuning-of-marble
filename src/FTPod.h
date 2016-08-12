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
#include "FTClock.h"
#include "FTMotor.h"
#include "FTSensor.h"
#include "FTSynth.h"
#include "FTCom.h"

//AO Library
#include <Scale.h>

//Definitions
#define DEBUG_POD true
#define START_DELAY 100 //Number of microseconds to start the play once the button has been pressed
#define MAX_ACTS 10 //Holds the total number of acts

//Main composition timing definitions (pulse counter thresholds per act)
const uint16_t compositions[1][MAX_ACTS] = {
  {10,20,30,40,50,60,70,80,90,100}
};

class FTPod
{
  public:

    FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, long fullRevolution, uint8_t nbOfPods);
    void update();

    uint8_t composition; //Current composition in play
    uint8_t act; //Current act in play
    long fullRev; //Keeping FULLREV value
    bool _start; //For beginning the play
    uint8_t totalPods;
    uint8_t startPin;
    bool _isClockMaster;

  private:

  	FTClock* Clock = nullptr;
  	FTMotor* Motor = nullptr;
  	FTSensor* Sensor = nullptr;
  	FTSynth* Synth = nullptr;
  	FTCom* Com = nullptr;

    void checkMaster(); //Check wether is POD Zero (the-great-master-of-clocks).
    void receiveCom(); //Receive messages from neighbour Pods.
    void setClock(); //Set the clock according to Com received values.
    void parseSensor(); //Control the data parsing of the sensor and LED status.
    void updateAct(); //Update the current act in play.
    void conduct(); //The main function that conducts the POD's action.
};

#endif
