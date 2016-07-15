/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTSensor.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTSensor_h
#define FTSensor_h
#define FILTERSAMPLES 7 //Has to be an ODD number
#define DEBUG_Sensor false

#include <Arduino.h>

class FTSensor
{
  public:
    FTSensor(int sensorPin, int ledPin, long fullRevolution);

    void update();
    void toggleLED(bool state);
    int getSensorValue (long position);


  private:
  	bool sIsActive; //If true, is parsing data to array. If false, data is not parsed, but only accessed.

  	int digitalSmooth(int rawIn, int *sensSmoothArray);	//Data filter
  	int pinLED; //Keeping the LED pin
  	int pinSensor; //Keeping the Sensor pin
  	long fullRev; //Keeping FULLREV value

};

#endif