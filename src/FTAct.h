/*

    ./~     FTAct.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/


#ifndef FTAct_h
#define FTAct_h

#include <Arduino.h>

//Definitions
#define DEBUG_Act false

class FTAct
{
  public:
  	FTAct(bool pd0, bool pd1, bool pd2, bool pd3, bool pd4, bool pd5, bool pd6, uint8_t motorActionID, uint8_t sensorActionID, uint8_t synthActionID, uint16_t timeOut);

    bool mHasStarted;
    bool mHasEnded;
    bool mPodPermissions[7];
    uint8_t mMotorActionID;
    uint8_t mSensorActionID;
    uint8_t mSynthActionID;
    uint16_t mTimeOut;

    bool getPodPermissionToAct(uint8_t podID);
    void startAct();
    void endAct();

  private:

};

#endif
