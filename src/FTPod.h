/*

    ./~     FTPod.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

/*
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

        the main pod.
        it knows its sub-routines and delegates between them.
        it know its own channel_id and the MAC address.

    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
*/


#ifndef FTPod_h
#define FTPod_h
#include <Arduino.h>
#include "FTClock.h"
#include "FTMotor.h"
#include "FTSensor.h"
#include "FTSynth.h"
#include "FTCom.h"
#include <MacAddress.h>

//Definitions
#define DEBUG_POD true
#define START_DELAY 100 //Number of microseconds to start the play once the button has been pressed

//Main composition timing definitions (pulse counter thresholds per act)
#define COMPOSITION 0; //Which composition is in play?
#define MAX_ACTS 10 //Holds the total number of acts
const uint16_t compositions[1][MAX_ACTS] = {
  {10,20,30,40,50,60,70,80,90,100}
};

//Scales and notes
#define HALF_TONE_LEN 12
#define FIFTH_LEN 2
#define MINOR_LEN 7
#define MAJOR_LEN 7
#define MINOR_CHORD_LEN 3
#define MAJOR_CHORD_LEN 3
#define MINOR_CHORD_7_LEN 4
#define MAJOR_CHORD_7_LEN 4
#define MINOR_PENTATONIC_LEN 5
#define MAJOR_PENTATONIC_LEN 5
#define OCTAVE_LEN 1
#define DIMINISHED_LEN 4

const uint8_t HALF_TONE[HALF_TONE_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const uint8_t FIFTH[FIFTH_LEN] = {0, 7};
const uint8_t MINOR[MINOR_LEN] = {0, 2, 3, 5, 7, 8, 10};
const uint8_t MAJOR[MAJOR_LEN] = {0, 2, 4, 5, 7, 9, 11};
const uint8_t MINOR_CHORD[MINOR_CHORD_LEN] = {0, 3, 7};
const uint8_t MAJOR_CHORD[MAJOR_CHORD_LEN] = {0, 4, 7};
const uint8_t MINOR_CHORD_7[MINOR_CHORD_7_LEN] = {0, 3, 7, 11};
const uint8_t MAJOR_CHORD_7[MAJOR_CHORD_7_LEN] = {0, 4, 7, 11};
const uint8_t MINOR_PENTATONIC[MINOR_PENTATONIC_LEN] = {0, 3, 5, 7, 10};
const uint8_t MAJOR_PENTATONIC[MAJOR_PENTATONIC_LEN] = {0, 4, 5, 7, 11};
const uint8_t OCTAVE[OCTAVE_LEN] = {0};
const uint8_t DIMINISHED[DIMINISHED_LEN] = {0, 3, 6, 9};

#define NOTE_A1 21
#define NOTE_A2 33
#define NOTE_A3 45
#define NOTE_A4 57
#define NOTE_A5 69
#define NOTE_A6 81
#define NOTE_A7 93
#define NOTE_C1 12
#define NOTE_C2 24
#define NOTE_C3 36
#define NOTE_C4 48
#define NOTE_C5 60
#define NOTE_C6 72
#define NOTE_C7 84

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
    void tune(); //The main function that controls the synthesizer.

};

#endif
