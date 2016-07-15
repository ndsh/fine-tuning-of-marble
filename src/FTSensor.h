/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTSensor.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTSensor_h
#define FTSensor_h
#define MAXVALUES 1800 //360*5
#define SENSOR_CYCLE 10 //Number of update() cycles to enable analogRead()
#define FILTERSAMPLES 10 //The higher, the smoother & the slower
#define DEBUG_SENSOR false

#include <Arduino.h>

class FTSensor
{
  public:
    FTSensor(int sensorPin, int ledPin, long fullRevolution);

    int sDataArray[MAXVALUES];
    long sPositionArray[MAXVALUES];

    void update();
    void toggleLED(bool state);
    void toggleDataParsing(bool state);
    int getSensorValue (long absolutePos);

  private:
  	bool sIsParsing; //If true, is parsing data to array. If false, data is not parsed, but only accessed.
  	int sFilterDataArray [FILTERSAMPLES]; //Used for filtering the data
  	int sPinLED; //Keeping the LED pin
  	int sPinSensor; //Keeping the Sensor pin
  	int sParsingIndex; //For iterating on the data arrays when in active mode
  	int sFilterIndex; //For iterating the filter array
  	int sStepRange; //For keeping the step range for retrieving sensor values according to the MAXVALUES & FULLREV
  	int sCurrentSensorValue; //For keeping track of the current sensor value
  	int sCycleCounter; //For iterating the cycle counter to enable the next analogRead()
  	long fullRev; //Keeping FULLREV value

  	int filterData(int raw); //Filtering data
  	int getDataFromAbsolutePos (long absolutePos); //Searches position array to retrieve sensor data
  	void parseDataToArray(long absolutePos);
};

#endif