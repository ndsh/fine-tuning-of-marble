/*

    ./~     FTAct.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "FTAct.h"

FTAct::FTAct(bool pd0, bool pd1, bool pd2, bool pd3, bool pd4, bool pd5, bool pd6, uint8_t motorActionID, uint8_t sensorActionID, uint8_t synthActionID, uint16_t timeOut)
{
  mHasStarted = false;
  mHasEnded= false;
  mMotorActionID = motorActionID;
  mSensorActionID = sensorActionID;
  mSynthActionID = synthActionID;
  mTimeOut = timeOut;
  mPodPermissions[0] = pd0;
  mPodPermissions[1] = pd1;
  mPodPermissions[2] = pd2;
  mPodPermissions[3] = pd3;
  mPodPermissions[4] = pd4;
  mPodPermissions[5] = pd5;
  mPodPermissions[6] = pd6;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

bool FTAct::getPodPermission(uint8_t podID){
  return mPodPermissions[podID];
}
