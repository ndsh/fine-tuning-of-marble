/*

    ./~     FTSensor.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#ifndef FTSensor_h
#define FTSensor_h
#define MAXVALUES 1440  //360*4
#define SENSOR_CYCLE 10 //Number of update() cycles to enable analogRead()
#define FILTERSAMPLES 10 //The higher, the smoother & the slower
#define DEBUG_SENSOR false

#include <Arduino.h>

class FTSensor
{
  public:
    FTSensor(int sensorPin, int ledPin, long fullRevolution);

    int mDataArray[MAXVALUES];
    long mPositionArray[MAXVALUES];
    int mCurrentSensorValue; //For keeping track of the current sensor value

    void update(long absolutePos);
    void toggleLED(bool state);
    void toggleDataParsing(bool state);

  private:
  	bool mIsParsing; //If true, is parsing data to array. If false, data is not parsed, but only accessed.
  	int mFilterDataArray [FILTERSAMPLES]; //Used for filtering the data
  	int mPinLED; //Keeping the LED pin
  	int mPinSensor; //Keeping the Sensor pin
  	int mParsingIndex; //For iterating on the data arrays when in active mode
  	int mFilterIndex; //For iterating the filter array
  	int mStepRange; //For keeping the step range for retrieving sensor values according to the MAXVALUES & FULLREV
  	int mCycleCounter; //For iterating the cycle counter to enable the next analogRead()
  	long mFullRev; //Keeping FULLREV value

  	int filterData(int raw); //Filtering data
  	int getDataFromAbsolutePos (long absolutePos); //Finds the closest position in the position array and retrieve its sensor data
    long getAbsolutePosFromData (int data); //Finds the closest data point in the data array and retrieve its absolute position
  	void parseDataToArray(long absolutePos); //Keeps the position & data in the main array.
};

#endif
