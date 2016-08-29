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

    FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution, uint8_t totalPods, uint8_t score, uint16_t pulseInterval);
    void update();

  private:

  	FTClock* Clock = nullptr;
  	FTMotor* Motor = nullptr;
    FTScore* Score = nullptr;
  	FTSensor* Sensor = nullptr;
  	FTSynth* Synth = nullptr;
  	FTCom* Com = nullptr;

    long mFullRev;
    bool mStart;
    bool mIsClockMaster;
    uint8_t mTotalPods;
    uint8_t mStartPin;
    uint8_t mOnboardLedPin;
    uint8_t mPodChannel;
    uint8_t mScore;
    uint16_t mAct;
    uint16_t mTimeoutCounter;
    String mMacAddress;

    void checkMaster(); //Check wether is POD Zero (the-great-master-of-clocks).
    void checkStart(); //Checks for the button pressed or com start value to begin.
    void setClock(); //Set the clock according to Com received values.
    void retrieveMacAddress();//Retrieve own MAC directly from hardware
    String getMacAddress();//Getter for mMacAddress
    void getMacAddressPosition();//Will read all MACs from MacAdresses.inc
    void sendCom(); //Send messages to neighbouring Pods.
    void conduct(); //The main function that conducts the POD's actions according to the Score.
    void configureSensor(uint16_t actionID); //Contains the different possible actions for the Sensor.
    void moveMotor(uint16_t actionID); //Contains the different possible actions for the Motor.
    void tuneSynth(uint16_t actionID); //Contains the different possible actions for the Motor.
};

#endif
