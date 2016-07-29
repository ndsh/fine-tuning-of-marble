/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTClock.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTClock_h
#define FTClock_h

#include <Arduino.h>

#define PULSE_INTERVAL 200 //In milliseconds
#define DEBUG_CLOCK false

class FTClock
{
  public:
    FTClock();
    void update();
    void startClock(); //Starts the clock function
    void setMaster(bool isMaster); //If true, it does the pulse counting. If false, it is iddle, and only receives the pulse count
    void updatePulse(uint16_t newPulseCount); //Updates the current pulse count
    void resetClock(); //Resets to clock to pulse count 0
    uint16_t getCount(); //Returns the current pulse count
    bool isOn(); //Returns OFF when clock hasn't been initialized (start button pin hasn't been pressed)
    bool isClockMaster(); //Returns wether is clock master or not

  private:
  	bool cIsOn; //Flag to set the clock on/off
  	bool cIsMaster; //Flag checked by setMaster
  	uint16_t cPulseCount; //Keeps track of the current pulse count
  	unsigned long cLast; //Keeps track of the last milli pulsed
  	unsigned long cNext; //Keeps track of the next milli to pulse
  	void calcIntervals(); //Used to update the milli intervals
};

#endif