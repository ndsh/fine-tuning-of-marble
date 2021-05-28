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
    bool hasActStarted(uint16_t actID);
    bool hasActEnded(uint16_t actID);
    bool getPodPermission(uint16_t actID,uint8_t podID);
    uint8_t getMotorAction(uint16_t actID);
    uint8_t getSensorAction(uint16_t actID);
    uint8_t getSynthAction(uint16_t actID);
    uint8_t getTimeOut(uint16_t actID);
    uint16_t getCurrentAct(uint16_t actID);
    uint16_t getTotalActs();
    void startAct(uint16_t actID);
    void endAct(uint16_t actID);

  private:
    FTAct* mActs[TOTAL_ACTS];
};

#endif
