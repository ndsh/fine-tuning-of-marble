/*
    · · · · · · · · · · · · · · · · · · · · ·

    SensorHead.cpp
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
*/

#include "SensorHead.h"

SensorHead::SensorHead(int _sensorPin, int _ledPin, long fullRevolution) {
	fullRev = fullRevolution;
	stepRange = fullRevolution / MAXVALUES;
	ledPin = _ledPin;
	sensorPin = _sensorPin;
	isParsing = false;
	parsingIndex = 0;
	filterIndex = 0;
	cycleCounter = 0;
	currentSensorValue = analogRead(sensorPin);
	ledState = HIGH;
	toggleLED(ledState);
}

void SensorHead::update(long absolutePos) {
  if (cycleCounter < SENSOR_CYCLE) {
     cycleCounter++;
  } else {
    cycleCounter = 0;
    if (isParsing && parsingIndex < MAXVALUES) {
      currentSensorValue = filterData(analogRead(sensorPin));
      parseDataToArray(absolutePos);
    } else {
      currentSensorValue = getDataFromAbsolutePos(absolutePos);
    }
  }
}

void SensorHead::toggleLED() {
	ledState = !ledState;
	digitalWrite(ledPin, ledState);
}

void SensorHead::toggleLED(bool state) {
	if (state) {
		digitalWrite(ledPin, HIGH);
	} else {
		digitalWrite(ledPin, LOW);
	}
}

void SensorHead::toggleDataParsing(bool state) {
  isParsing = state;
}

/*
	· · · · · · · · · · · · · · · · · · · · ·
		PRIVATE
	· · · · · · · · · · · · · · · · · · · · ·
*/

int SensorHead::filterData(int raw) {
  //Assign to filter array
  filterDataArray[filterIndex] = raw;
  if (filterIndex < FILTERSAMPLES-1) {
    filterIndex++;
  } else {
    filterIndex = 0;
  }

  //Calculate average
  int sum = 0;
  for (int i = 0; i < FILTERSAMPLES; i++) {
    sum += filterDataArray[i];
  }
  int average = sum/FILTERSAMPLES;

  return average;
}

void SensorHead::parseDataToArray(long absolutePos) {
  if (absolutePos > stepRange * (parsingIndex+1)) {
    parsingIndex++;
    #if DEBUG_SENSOR
      Serial.print("~FTSns::parseDataToArray()-› ");
      Serial.print("parsingIndex: ");
      Serial.print(parsingIndex);
      Serial.print(" absolutePos: ");
      Serial.print(absolutePos);
      Serial.print(" currentSensorValue: ");
      Serial.println(currentSensorValue);
    #endif
  }

  positionArray[parsingIndex] = absolutePos;
  dataArray[parsingIndex] = currentSensorValue;

}

int SensorHead::getDataFromAbsolutePos(long absolutePos) {
  //Find the closest position using the Step Range as reference
  int idx = floor(absolutePos/stepRange);

  /*
  //Find the real closest position
  long d = abs(positionArray[0] - absolutePos);
  int idx = 0;
  for(int c = 1; c < MAXVALUES; c++){
      long cd = abs(positionArray[c] - absolutePos);
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
    Serial.print(positionArray[idx]);
    Serial.print(" -> returning Data: ");
    Serial.println(dataArray[idx]);
  #endif
  */
  return dataArray[idx];
}

long SensorHead::getAbsolutePosFromData(int data) {
  //Find the closest data point in the array and retrieve its position
  int d = abs(dataArray[0] - data);
  int idx = 0;
  for(int c = 1; c < MAXVALUES; c++) {
      int cd = abs(dataArray[c] - data);
      if(cd < d) {
          idx = c;
          d = cd;
      }
  }

  return positionArray[idx];
}