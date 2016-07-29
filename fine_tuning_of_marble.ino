/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FineTuningOfMarble.ino
 Copyright (c) 2016 The Fine Tuning of Marble
 https://github.com/ndsh/fine-tuning-of-marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

//Definitions

#define FULLREV 230400 //9:1 25600
#define SENSOR_PIN A0
#define MOTOR_DIR_PIN 3
#define MOTOR_STEP_PIN 4
#define LED_PIN 5
#define PODZERO_PIN 6
#define INIT_DELAY 1000
#define DEBUG false

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
  pinMode(PODZERO_PIN, INPUT_PULLDOWN);

  //Create Pod
  Pod = new FTPod(SENSOR_PIN,LED_PIN,MOTOR_DIR_PIN,MOTOR_STEP_PIN,FULLREV);
  
  //Init Delay
  delay(INIT_DELAY);
  #if DEBUG
    Serial.println("INIT")
  #endif
}

void loop() {
  Serial.println(digitalRead(PODZERO_PIN));
  //Update Pod
  Pod->update();
}


