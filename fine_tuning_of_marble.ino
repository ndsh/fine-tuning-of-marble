/*

    ./~     FineTuningOfMarble.ino
    ./~     Copyright (c) 2016 The Fine Tuning of Marble

    ./~     [!] https://github.com/ndsh/fine-tuning-of-marble
    
    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

*/

//Definitions

#define SCORE 0 //Score in play
#define FULLREV 230400 //9:1 25600
#define TOTALPODS 7 //Total number of PODs in play
#define DEBUG true

#define SENSOR_PIN A0
#define MOTOR_DIR_PIN 3
#define MOTOR_STEP_PIN 4
#define LED_PIN 5
#define START_PIN 6
#define ONBOARD_LED_PIN 13

//Main Include
#include "src/FTPod.h"

//Instances
FTPod* Pod;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setup() {
  //Setup Pins
  pinMode(SENSOR_PIN, INPUT); 
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_STEP_PIN, OUTPUT);
  pinMode(START_PIN, INPUT_PULLDOWN);
  pinMode(ONBOARD_LED_PIN, OUTPUT);
  delay(1000);

#if DEBUG
  Serial.println("~FTApp: INIT");
  Serial.println("~FTApp: Press the button to start");
  Serial.println();
#endif

  //Create Pod
  Pod = new FTPod(SENSOR_PIN, LED_PIN, MOTOR_DIR_PIN, MOTOR_STEP_PIN, START_PIN, ONBOARD_LED_PIN, FULLREV, TOTALPODS, SCORE);
}

void loop() {
  //Update Pod
  Pod->update();
}
