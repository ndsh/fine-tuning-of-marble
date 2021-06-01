/*
    · · · · · · · · · · · · · · · · · · · · ·

    Synth.h
    https://github.com/ndsh/floorScanners

    Copyright (c) 2016 - 2021

    · · · · · · · · · · · · · · · · · · · · ·
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
        uint8_t note;
        uint8_t lastNote;
        uint8_t noteVelocity;
};

#endif