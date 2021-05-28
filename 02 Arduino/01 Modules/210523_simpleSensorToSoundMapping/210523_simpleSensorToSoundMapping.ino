#include <spi4teensy3.h>
#include <EEPROM.h>
#include <CFO_BODYSEQ.h>

boolean noteIsOn = false;
int n = 0;
int dir = 1;
int rootNote = 36;
int note[] = {0,12,3,19,15,9,5,24,7};

long time = 0;
long lastTime = 0;
long timeDelay = 60;

#define SENSOR_PIN A0
#define LED_PIN 5

void setup() {
  Music.init();
  Music.setWaveform(SAW);
  Music.setDetune(0.005);  
  Music.enableEnvelope1();
  Music.setEnv1Attack(8);
  Music.setEnv1Decay(90);
  Music.setEnv1Sustain(48);
  Music.setEnv1Release(64);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  int val = analogRead(SENSOR_PIN);
  int mapped = map(val, 0, 1023, 0, 64);
  Music.noteOn(rootNote+mapped);
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
