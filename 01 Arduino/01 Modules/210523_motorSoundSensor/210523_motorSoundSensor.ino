/*
 * You can try putting a capacitor in parallel with the 2K resistor. For example, the RC time constant (R x C) of 2K and 500uF is one second. (The effective "R" is actually the parallel equivalent of the fixed resistor and LDR, so the actual time constant will be less.)

Or you can try some [u]smoothing[/u].

And, I assume the whole thing is in a light-tight box? Fluorescent lights flicker at the power line frequency.

*/
#include <spi4teensy3.h>
#include <EEPROM.h>
#include <CFO_BODYSEQ.h>
#include <AccelStepper.h>

boolean noteIsOn = false;
int n = 0;
int dir = 1;
int rootNote = 36;
int note[] = {0,12,3,19,15,9,5,24,7};

long time = 0;
long lastTime = 0;
long timeDelay = 60;

#define MOTOR_DIR_PIN 3
#define MOTOR_STEP_PIN 4
#define SENSOR_PIN A0
#define LED_PIN 5

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(AccelStepper::FULL2WIRE, 4, 3);

int counter = 0;

void setup() {
  //stepper = AccelStepper::FULL2WIRE, MOTOR_STEP_PIN, MOTOR_DIR_PIN;
  Music.init();
  Music.setWaveform(SINE);
  //Music.setDetune(1.005); 
  /*
  Music.enableEnvelope1();
  Music.setEnv1Attack(2);
  Music.setEnv1Decay(4);
  Music.setEnv1Sustain(20);
  Music.setEnv1Release(30);
  */

  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  stepper.setMaxSpeed(1000);
  stepper.setSpeed(100);  
}

void loop() {
  
  int val = analogRead(SENSOR_PIN);
  //val = random(0, 1023);
 
  
  int mapped = map(val, 0, 1023, 20, 64);
  Serial.println(mapped);
  if(val > 0) Music.noteOn(rootNote+mapped);
  //stepper.move(1);
  stepper.runSpeed();
  //stepper.runToPosition();
  delay(10);
  /*
  time = millis();
  if(time - lastTime > timeDelay) {
    if(!noteIsOn) {
      Music.noteOn(rootNote+note[n]);
      noteIsOn = true;
      n = n + dir;
      if(n > 7)
      {
        dir = -1;
      }
      else if(n < 1)
      {
        dir = 1;
      }
    } else {
      Music.noteOff();
      noteIsOn = false;
    }
    lastTime = time;
  }
  */
}
