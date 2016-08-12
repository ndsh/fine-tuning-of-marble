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
#define DEBUG_CLOCK true

class FTClock
{
  public:
    FTClock();
    void update();
    void startClock(); //Starts the clock function
    void setMaster(bool isMaster); //If true, it does the pulse counting. If false, it is iddle, and only receives the pulse count
    void updatePulse(); //Updates pulseClock +1
    void resetClock(); //Resets to clock to pulse count 0
    bool isOn(); //Returns OFF when clock hasn't been initialized (start button pin hasn't been pressed)
    bool readPulse(); //Returns true in case there is a pulse
    uint16_t readClock(); //Returns the current pulse count

  private:
  	bool cIsOn; //Flag to set the clock on/off
  	bool cIsMaster; //Flag checked by setMaster
    bool cPulse; //Flag to signalize pulse
  	uint16_t cPulseCount; //Keeps track of the current pulse count
  	unsigned long cLast; //Keeps track of the last milli pulsed
  	unsigned long cNext; //Keeps track of the next milli to pulse
  	void calcIntervals(); //Used to update the milli intervals
};

#endif
