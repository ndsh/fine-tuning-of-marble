/*

    ./~     FTSensor.cpp
    ./~     Copyright (c) 2016 The Fine Tuning of Marble
  

    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
    
*/

#include "FTSensor.h"

FTSensor::FTSensor(int sensorPin, int ledPin, long fullRevolution)
{
  mFullRev = fullRevolution;
	mStepRange = fullRevolution / MAXVALUES;
  mPinLED = ledPin;
  mPinSensor = sensorPin;
  mIsParsing = false;
  mParsingIndex = 0;
  mFilterIndex = 0;
  mCycleCounter = 0;
  mCurrentSensorValue = analogRead(mPinSensor);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Public
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void FTSensor::update() {
  if (mIsParsing)
  {
    if (mCycleCounter < SENSOR_CYCLE)
    {
       mCycleCounter++;
    }
    else
    {
      //Cycle done, read new sensor data and filter
      mCurrentSensorValue = filterData(analogRead(mPinSensor));
      mCycleCounter = 0;
    }
  }
}

int FTSensor::getSensorValue (long absolutePos)
{
  if (mIsParsing)
  {
    if (mParsingIndex < MAXVALUES && absolutePos <= mFullRev)
    {
      //parse data to array
      parseDataToArray(absolutePos);
      return mCurrentSensorValue;
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
		digitalWrite(mPinLED, HIGH);
	}
	else
	{
		digitalWrite(mPinLED, LOW);
	}
}

void FTSensor::toggleDataParsing(bool state)
{
  mIsParsing = state;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Private
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  int FTSensor::filterData(int raw){     

  //Assign to filter array
  mFilterDataArray[mFilterIndex] = raw;
  if (mFilterIndex < FILTERSAMPLES-1)
  {
    mFilterIndex++;
  }
  else
  {
    mFilterIndex = 0;
  }

  //Calculate average
  int sum = 0;
  for (int i = 0; i < FILTERSAMPLES; i++)
  {
    sum += mFilterDataArray[i];
  }

  int average = sum/FILTERSAMPLES;

  return average;
}

void FTSensor::parseDataToArray(long absolutePos)
{
  if (absolutePos > mStepRange * (mParsingIndex+1))
  {
    mParsingIndex++;
    #if DEBUG_SENSOR
      Serial.print("~FTSns::parseDataToArray()-› ");
      Serial.print("mParsingIndex: ");
      Serial.print(mParsingIndex);
      Serial.print(" absolutePos: ");
      Serial.print(absolutePos);
      Serial.print(" mCurrentSensorValue: ");
      Serial.println(mCurrentSensorValue);
    #endif
  }

  mPositionArray[mParsingIndex] = absolutePos;
  mDataArray[mParsingIndex] = mCurrentSensorValue;
  
}

int FTSensor::getDataFromAbsolutePos(long absolutePos)
{
  //Find the closest position using the Step Range as reference
  int idx = floor(absolutePos/mStepRange);

  /*  
  //Find the real closest position
  long d = abs(mPositionArray[0] - absolutePos);
  int idx = 0;
  for(int c = 1; c < MAXVALUES; c++){
      long cd = abs(mPositionArray[c] - absolutePos);
      if(cd < d){
          idx = c;
          d = cd;
      }
  }
  */

  /*
  //Following debug lines are heavy on Teensy. Use it only when needed.
  #if DEBUG_SENSOR
    Serial.print("~FTSns::getDataFromAbsolutePos()-› ");
    Serial.print(absolutePos);
    Serial.print(" -> closestPosition: ");
    Serial.print(mPositionArray[idx]);
    Serial.print(" -> returning Data: ");
    Serial.println(mDataArray[idx]);
  #endif
  */
  return mDataArray[idx];
}
