/*

    ./~     FTPod.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble
    
    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

*/

/*  
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

        the main pod.
        it knows it's sub-routines and delegates between them.
        it know it's own channel_id and the MAC address.

    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
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
#include <MacAddress.h>

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

    FTPod(uint8_t sensorPin, uint8_t ledPin, uint8_t motorDirPin, uint8_t motorStepPin, uint8_t startButtonPin, uint8_t onboardLedPin, long fullRevolution, uint8_t nbOfPods);
    void update();

    uint8_t mComposition; //Current composition in play
    uint8_t mAct; //Current act in play
    long mFullRev; //Keeping FULLREV value
    bool mStart; //For beginning the play
    uint8_t mTotalPods;
    uint8_t mStartPin;
    uint8_t mOnboardLedPin;
    bool mIsClockMaster;
    uint8_t mPodChannel;
    String mMacAddress;

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
    void retrieveMacAddress();//Retrieve own MAC directly from hardware
    String getMacAddress();//Getter for mMacAddress
    void getMacAddressPosition();//Will read all MACs from MacAdresses.inc
    void updateAct(); //Update the current act in play.
    void conduct(); //The main function that conducts the POD's action.

};

#endif
