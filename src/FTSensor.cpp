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
  #if DEBUG_SENSOR
    Serial.print("FTSensor -> getSensorValue: ");
    Serial.println(absolutePos);
  #endif
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
  #if DEBUG_SENSOR
      Serial.print("FTSensor -> toggleDataParsing: ");
      Serial.println(state);
  #endif
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSensor::parseDataToArray(long absolutePos)
{
  if (absolutePos > sStepRange * (sParsingIndex+1))
  {
    sParsingIndex++;
  }
  sPositionArray[sParsingIndex] = absolutePos;
  sDataArray[sParsingIndex] = sCurrentSensorValue;
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

int FTSensor::getDataFromAbsolutePos(long absolutePos)
{
  for (int i = 0; i < MAXVALUES; i++)
  {
    if (absolutePos-sStepRange < sPositionArray[i]  || sPositionArray[i] < absolutePos+sStepRange)
    {
      #if DEBUG_SENSOR
        Serial.print("FTSensor -> getDataFromAbsolutePos: ");
        Serial.println(sDataArray[i]);
      #endif
      sCurrentSensorValue = sDataArray[i];
      return sCurrentSensorValue;
    }
  }
  #if DEBUG_SENSOR
    Serial.print("FTSensor -> getDataFromAbsolutePos: ");
    Serial.print(" not found! Returning last retrieved value: ");
    Serial.println(sCurrentSensorValue);
  #endif
  return sCurrentSensorValue;
}

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
