/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTSensor.cpp
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "FTSensor.h"

FTSensor::FTSensor(int sensorPin, int ledPin, long fullRevolution)
{
	fullRev = fullRevolution;
  pinLED = ledPin;
  pinSensor = sensorPin;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSensor::update() {

}

void FTSensor::toggleLED(bool state)
{
	if (state)
	{
		digitalWrite(pinLED, HIGH);
	}
	else
	{
		digitalWrite(pinLED, LOW);
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int FTSensor::digitalSmooth(int rawIn, int *sensSmoothArray){ 
  int j, k, temp, top, bottom;
  long total;
  static int i;
  static int sorted[FILTERSAMPLES];
  boolean done;

  i = (i + 1) % FILTERSAMPLES;
  sensSmoothArray[i] = rawIn;

  for (j=0; j<FILTERSAMPLES; j++){
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;        
  while(done != 1){
    done = 1;
    for (j = 0; j < (FILTERSAMPLES - 1); j++){
      if (sorted[j] > sorted[j + 1]){ 
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }

  bottom = max(((FILTERSAMPLES * 15)  / 100), 1); 
  top = min((((FILTERSAMPLES * 85) / 100) + 1  ), (FILTERSAMPLES - 1)); 
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];
    k++; 
  }

  return total / k;
}



