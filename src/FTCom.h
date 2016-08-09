/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTCom.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTCom_h
#define FTCom_h
#include <MacAddress.h>

//Definitions
#define DEBUG_COM true

class FTCom
{
  public:
    FTCom();
    void update();

    String macAddress;
    uint8_t cReceivedFlagCounter; //Holds the last updated counter with the number of PODs that finished their acts
    uint16_t cReceivedClock; //Holds the last received pulse number (sent by the PodZero)
    bool cReceivedStart; //Holds true in case the first value has been received (thus, starting the play)

    void retrieveMacAddress();
    String getMacAddress();
    bool hasStarted(); //For communicating the beginning of the play
    uint8_t getReceivedFlagCounter(); //Returns cReceivedFlagCounter
    uint16_t getReceivedClock(); //Returns cReceivedClock;

  private:

};

#endif
