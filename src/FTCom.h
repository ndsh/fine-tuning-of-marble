/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTCom.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTCom_h
#define FTCom_h
#include <MacAddress.h>
#include "MIDI.h"

//Definitions
#define DEBUG_COM true

class FTCom
{
  public:
    FTCom();
    void update();

    //void write(params);
    //uint16_t read(params);
    bool pulseIn();
    void pulseOut(bool pulse);
    bool hasStarted(); //For communicating the beginning of the play
    uint16_t getPulseCount(); //Returns cPulseCount, a counter of received pulses

  private:
    String macAddress;
    uint16_t cPulseCount; //Holds the last received pulse number (sent by the PodZero)
    bool cStart; //Holds true in case the first value has been received (thus, starting the play)

    void retrieveMacAddress();
    void pulse(); //Call this everytime a pulse is received
    String getMacAddress();
};

#endif
