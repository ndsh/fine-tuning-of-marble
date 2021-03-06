/*

    ./~     FTClock.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#ifndef FTClock_h
#define FTClock_h

#include <Arduino.h>

#define DEBUG_CLOCK false

class FTClock
{
  public:
    FTClock(uint16_t pulseInterval);
    void update();
    void startClock(); //Starts the clock function
    void setMaster(bool isMaster); //If true, it does the pulse counting. If false, it is iddle, and only receives the pulse count
    void updatePulse(); //Updates pulseClock +1
    void resetClock(); //Resets to clock to pulse count 0
    bool isOn(); //Returns OFF when clock hasn't been initialized (start button pin hasn't been pressed)
    bool readPulse(); //Returns true in case there is a pulse
    uint16_t readClock(); //Returns the current pulse count

  private:
  	bool mIsOn; //Flag to set the clock on/off
  	bool mIsMaster; //Flag checked by setMaster
    bool mPulse; //Flag to signalize pulse
    uint16_t mPulseInterval; //Keeps the pulse interval
  	uint16_t mPulseCount; //Keeps track of the current pulse count
  	unsigned long mLast; //Keeps track of the last milli pulsed
  	unsigned long mNext; //Keeps track of the next milli to pulse

  	void calcIntervals(); //Used to update the milli intervals
};

#endif
