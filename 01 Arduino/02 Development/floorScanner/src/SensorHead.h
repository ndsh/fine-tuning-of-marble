/*
    · · · · · · · · · · · · · · · · · · · · ·

    SensorHead.h
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#ifndef SENSORHEAD_H
#define SENSORHEAD_H
#define MAXVALUES 1440  //360*4
#define SENSOR_CYCLE 10 //Number of update() cycles to enable analogRead()
#define FILTERSAMPLES 10 //The higher, the smoother & the slower
#define DEBUG_SENSOR false

#include <Arduino.h>

class SensorHead {
  public:
    SensorHead(int sensorPin, int ledPin, long fullRevolution);

    int dataArray[MAXVALUES];
    long positionArray[MAXVALUES];
    int currentSensorValue; //For keeping track of the current sensor value

    void update(long absolutePos);
    void toggleLED(bool state);
    void toggleLED();
    void toggleDataParsing(bool state);

  private:
  	bool isParsing; //If true, is parsing data to array. If false, data is not parsed, but only accessed.
  	int filterDataArray[FILTERSAMPLES]; //Used for filtering the data
  	int ledPin; //Keeping the LED pin
  	int sensorPin; //Keeping the Sensor pin
  	bool ledState;
  	int parsingIndex; //For iterating on the data arrays when in active mode
  	int filterIndex; //For iterating the filter array
  	int stepRange; //For keeping the step range for retrieving sensor values according to the MAXVALUES & FULLREV
  	int cycleCounter; //For iterating the cycle counter to enable the next analogRead()
  	long fullRev; //Keeping FULLREV value

  	int filterData(int raw); //Filtering data
  	int getDataFromAbsolutePos (long absolutePos); //Finds the closest position in the position array and retrieve its sensor data
    long getAbsolutePosFromData (int data); //Finds the closest data point in the data array and retrieve its absolute position
  	void parseDataToArray(long absolutePos); //Keeps the position & data in the main array.
};

#endif