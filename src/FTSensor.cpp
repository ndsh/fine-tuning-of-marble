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
	sStepRange = fullRevolution / MAXVALUES;
  sPinLED = ledPin;
  sPinSensor = sensorPin;
  sIsParsing = false;
  sParsingIndex = 0;
  sFilterIndex = 0;
  sCycleCounter = 0;
  sCurrentSensorValue = analogRead(sPinSensor);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSensor::update() {
  if (sIsParsing)
  {
    if (sCycleCounter < SENSOR_CYCLE)
    {
       sCycleCounter++;
    }
    else
    {
      //Cycle done, read new sensor data and filter
      sCurrentSensorValue = filterData(analogRead(sPinSensor));
      sCycleCounter = 0;
    }
  }
}

int FTSensor::getSensorValue (long absolutePos)
{
  if (sIsParsing)
  {
    if (sParsingIndex < MAXVALUES && absolutePos <= fullRev)
    {
      //parse data to array
      parseDataToArray(absolutePos);
      return sCurrentSensorValue;
    }
    else
    {
      //already above the limit, get from array
      toggleDataParsing(false);
      return getDataFromAbsolutePos(absolutePos);
    }
  }
  else{
    //get data from array
    return getDataFromAbsolutePos(absolutePos);
  }
}

void FTSensor::toggleLED(bool state)
{
	if (state)
	{
		digitalWrite(sPinLED, HIGH);
	}
	else
	{
		digitalWrite(sPinLED, LOW);
	}
}

void FTSensor::toggleDataParsing(bool state)
{
  sIsParsing = state;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  int FTSensor::filterData(int raw){     

  //Assign to filter array
  sFilterDataArray[sFilterIndex] = raw;
  if (sFilterIndex < FILTERSAMPLES-1)
  {
    sFilterIndex++;
  }
  else
  {
    sFilterIndex = 0;
  }

  //Calculate average
  int sum = 0;
  for (int i = 0; i < FILTERSAMPLES; i++)
  {
    sum += sFilterDataArray[i];
  }

  int average = sum/FILTERSAMPLES;

  return average;
}

void FTSensor::parseDataToArray(long absolutePos)
{
  if (absolutePos > sStepRange * (sParsingIndex+1))
  {
    sParsingIndex++;
    #if DEBUG_SENSOR
      Serial.print("FTSensor -> parseDataToArray: ");
      Serial.print("sParsingIndex: ");
      Serial.print(sParsingIndex);
      Serial.print(" absolutePos: ");
      Serial.print(absolutePos);
      Serial.print(" sCurrentSensorValue: ");
      Serial.println(sCurrentSensorValue);
    #endif
  }

  sPositionArray[sParsingIndex] = absolutePos;
  sDataArray[sParsingIndex] = sCurrentSensorValue;
  
}

int FTSensor::getDataFromAbsolutePos(long absolutePos)
{
  //Find the closest position using the Step Range as reference
  int idx = floor(absolutePos/sStepRange);

  /*  
  //Find the real closest position
  long d = abs(sPositionArray[0] - absolutePos);
  int idx = 0;
  for(int c = 1; c < MAXVALUES; c++){
      long cd = abs(sPositionArray[c] - absolutePos);
      if(cd < d){
          idx = c;
          d = cd;
      }
  }
  */

  /*
  //Following debug lines are heavy on Teensy. Use it only when needed.
  #if DEBUG_SENSOR
    Serial.print("FTSensor -> getDataFromAbsolutePos: ");
    Serial.print(absolutePos);
    Serial.print(" -> closestPosition: ");
    Serial.print(sPositionArray[idx]);
    Serial.print(" -> returning Data: ");
    Serial.println(sDataArray[idx]);
  #endif
  */
  return sDataArray[idx];
}
