/*

    ./~     FTScore.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/


#ifndef FTScore_h
#define FTScore_h
#include <Arduino.h>
#include "FTAct.h"

//Definitions
#define TOTAL_ACTS 100
#define DEBUG_Score false

class FTScore
{
  public:
  	FTScore();

    uint16_t mAct;
    bool mIsIddle;

    bool doIPlay(uint8_t podID);
    bool hasStarted();
    bool hasEnded();
    uint8_t getMotorAction();
    uint8_t getSensorAction();
    uint8_t getSynthAction();
    uint8_t getTimeOut();
    uint16_t getCurrentAct();

    void updateAct(uint16_t newAct);
    void startAct();
    void endAct();

  private:
    FTAct* mActs[TOTAL_ACTS];
};

#endif
