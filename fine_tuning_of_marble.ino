/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FineTuningOfMarble.ino
 Copyright (c) 2016 The Fine Tuning of Marble
 https://github.com/ndsh/fine-tuning-of-marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

//Definitions

#define SENSOR_PIN A0
#define MOTOR_DIR_PIN 3
#define MOTOR_STEP_PIN 4
#define LED_PIN 5
#define INIT_DELAY 100

//Main Include
#include "src/FTPod.h"

//Instances
FTPod* Pod;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setup() {
  //Setup Pins
  pinMode(SENSOR_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_STEP_PIN, OUTPUT);

  //Create Pod
  Pod = new FTPod(SENSOR_PIN,LED_PIN,MOTOR_DIR_PIN,MOTOR_STEP_PIN);
  
  //Init Delay
  delay(INIT_DELAY);
}

void loop() {
  //Update Pod
  Pod->update();
}

