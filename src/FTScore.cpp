/*

    ./~     FTScore.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "FTScore.h"

FTScore::FTScore()
{
  //act[n]            (pod0   pod1    pod2    pod3    pod4    pod5    pod6    motorAction   sensorAction  synthAction   timeOutInPulses)
  mActs[0] = new FTAct(true,  true,   true,   true,   true,   true,   true,   0,            0,            0,            50             );
  mActs[1] = new FTAct(true,  false,  false,  false,  false,  false,  false,  1,            0,            0,            50             );
  //(...)
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

bool FTScore::getPodPermission(uint16_t actID,uint8_t podID)
{
  return mActs[actID]->getPodPermission(podID);
}

bool FTScore::hasActStarted(uint16_t actID)
{
  return mActs[actID]->mHasStarted;
}

bool FTScore::hasActEnded(uint16_t actID)
{
  return mActs[actID]->mHasEnded;
}

uint8_t FTScore::getMotorAction(uint16_t actID)
{
  return mActs[actID]->mMotorActionID;
}

uint8_t FTScore::getSensorAction(uint16_t actID)
{
  return mActs[actID]->mSensorActionID;
}

uint8_t FTScore::getSynthAction(uint16_t actID)
{
  return mActs[actID]->mSynthActionID;
}

uint8_t FTScore::getTimeOut(uint16_t actID)
{
  return mActs[actID]->mTimeOut;
}

void FTScore::startAct(uint16_t actID)
{
  mActs[actID]->mHasStarted = true;
}

void FTScore::endAct(uint16_t actID)
{
  mActs[actID]->mHasEnded = true;
}
