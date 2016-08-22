/*

    ./~     FTSynth.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#ifndef FTSynth_h
#define FTSynth_h
#include <CFOSynthesizer.h>
#include <CFOMidi.h>

//Definitions
#define DEBUG_SYNTH true

class FTSynth
{
  public:
    FTSynth();
    void applyPreset();
    void mapDataToNote(int sensorData, uint8_t baseNote, uint8_t maxNote, const uint8_t scale[], uint8_t scaleLength);
    void updateVelocity(float newVelocity);
  private:
    void playInitTune();
    void playNote(uint8_t mNote);
    uint8_t mLastNote; //for keeping track of the last note played
    uint8_t mNoteVelocity; //note velocity
};

#endif
