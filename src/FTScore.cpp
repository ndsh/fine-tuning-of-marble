/*

    ./~     FTScore.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#include "FTScore.h"

FTScore::FTScore()
{
  mAct = 0;
  mIsIddle = false;

  //Cheat Sheet:  permissions to play (true/false x 7 pods) , motor action id, sensor action id, synth action id, time out
  //The IDs (motor/sensor/synth) are linked to pre-programmed actions inside FTPod.

  mActs[0] = new FTAct(true,true,true,true,true,true,true,0,0,0,50);
  mActs[1] = new FTAct(true,false,false,false,false,false,false,1,0,0,50);
  //(...)
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

bool FTScore::doIPlay(uint8_t podID)
{
  return mActs[mAct]->getPodPermissionToAct(podID);
}

bool FTScore::hasStarted()
{
  return mActs[mAct]->mHasStarted;
}

bool FTScore::hasEnded()
{
  return mActs[mAct]->mHasEnded;
}

uint8_t FTScore::getMotorAction()
{
  return mActs[mAct]->mMotorActionID;
}

uint8_t FTScore::getSensorAction()
{
  return mActs[mAct]->mSensorActionID;
}

uint8_t FTScore::getSynthAction()
{
  return mActs[mAct]->mSynthActionID;
}

uint8_t FTScore::getTimeOut()
{
  return mActs[mAct]->mTimeOut;
}

uint16_t FTScore::getCurrentAct()
{
  return mActs[mAct]->mSynthActionID;
}

void FTScore::startAct()
{
  mActs[mAct]->mHasStarted = true;
}

void FTScore::endAct()
{
  mActs[mAct]->mHasEnded = true;
}

void FTScore::updateAct(uint16_t newAct)
{
  mAct = newAct;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
