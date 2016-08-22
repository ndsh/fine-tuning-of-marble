/*

    ./~     FTPod.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#ifndef FTPod_h
#define FTPod_h
#include <Arduino.h>
#include "FTClock.h"
#include "FTMotor.h"
#include "FTScore.h"
#include "FTSensor.h"
#include "FTSynth.h"
#include "FTCom.h"
#include <MacAddress.h>
#include "inc/Scales.h"

//Definitions
#define START_DELAY 100 //Number of microseconds to start the play once the button has been pressed
#define DEBUG_POD true

class FTPod
{
  public:

    FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution, uint8_t totalPods, uint8_t score);
    void update();

    long mFullRev; //Keeping FULLREV value
    bool mStart; //For beginning the play
    bool mIsClockMaster;
    uint8_t mTotalPods;
    uint8_t mStartPin;
    uint8_t mOnboardLedPin;
    uint8_t mPodChannel;
    uint8_t mScore;
    String mMacAddress;

  private:

  	FTClock* Clock = nullptr;
  	FTMotor* Motor = nullptr;
    FTScore* Score = nullptr;
  	FTSensor* Sensor = nullptr;
  	FTSynth* Synth = nullptr;
  	FTCom* Com = nullptr;

    void checkMaster(); //Check wether is POD Zero (the-great-master-of-clocks).
    void receiveCom(); //Receive messages from neighbour Pods.
    void setClock(); //Set the clock according to Com received values.
    void parseSensor(); //Control the data parsing of the sensor and LED status.
    void retrieveMacAddress();//Retrieve own MAC directly from hardware
    String getMacAddress();//Getter for mMacAddress
    void getMacAddressPosition();//Will read all MACs from MacAdresses.inc
    void conduct(); //The main function that conducts the POD's action.
    void tune(); //The main function that controls the synthesizer.

};

#endif
