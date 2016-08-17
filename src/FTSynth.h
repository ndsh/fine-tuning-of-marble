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
    void update();
    //applyPreset()
    //getPreset()
  private:
    void playInitTune();
};

#endif
