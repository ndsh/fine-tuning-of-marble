/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTSensor.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTSensor_h
#define FTSensor_h

class FTSensor
{
  public:
    FTSensor(int sensorPin, int ledPin);
    void update();
  private:

};

#endif