/*

    ./~     Synth.h
    ./~     Copyright (c) 2016 The Fine Tuning of Marble


    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*/

#ifndef SYNTH_H
#define SYNTH_H

#include "CFOSynthesizer.h"
#include "CFOMidi.h"

#define DEBUG_SYNTH false

class Synth {
    public:
        Synth();
        void applyPreset();
        uint8_t mapDataToNote(int sensorData, uint8_t baseNote, uint8_t maxNote, const uint8_t scale[], uint8_t scaleLength);
        void updateNote(uint8_t note);
        void updateVelocity(uint8_t newVelocity);
        void playNote();

    private:
        void startupTune();
        uint8_t note; //current note that will be played when playNote() is called
        uint8_t lastNote; //for keeping track of the last note played
        uint8_t noteVelocity; //note velocity
};

#endif
