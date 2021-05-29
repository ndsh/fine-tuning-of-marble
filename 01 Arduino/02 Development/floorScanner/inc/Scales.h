#define HALF_TONE_LEN 12
#define FIFTH_LEN 2
#define MINOR_LEN 7
#define MAJOR_LEN 7
#define MINOR_CHORD_LEN 3
#define MAJOR_CHORD_LEN 3
#define MINOR_CHORD_7_LEN 4
#define MAJOR_CHORD_7_LEN 4
#define MINOR_PENTATONIC_LEN 5
#define MAJOR_PENTATONIC_LEN 5
#define OCTAVE_LEN 1
#define DIMINISHED_LEN 4

const uint8_t HALF_TONE[HALF_TONE_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const uint8_t FIFTH[FIFTH_LEN] = {0, 7};
const uint8_t MINOR[MINOR_LEN] = {0, 2, 3, 5, 7, 8, 10};
const uint8_t MAJOR[MAJOR_LEN] = {0, 2, 4, 5, 7, 9, 11};
const uint8_t MINOR_CHORD[MINOR_CHORD_LEN] = {0, 3, 7};
const uint8_t MAJOR_CHORD[MAJOR_CHORD_LEN] = {0, 4, 7};
const uint8_t MINOR_CHORD_7[MINOR_CHORD_7_LEN] = {0, 3, 7, 11};
const uint8_t MAJOR_CHORD_7[MAJOR_CHORD_7_LEN] = {0, 4, 7, 11};
const uint8_t MINOR_PENTATONIC[MINOR_PENTATONIC_LEN] = {0, 3, 5, 7, 10};
const uint8_t MAJOR_PENTATONIC[MAJOR_PENTATONIC_LEN] = {0, 4, 5, 7, 11};
const uint8_t OCTAVE[OCTAVE_LEN] = {0};
const uint8_t DIMINISHED[DIMINISHED_LEN] = {0, 3, 6, 9};

#define NOTE_A1 21
#define NOTE_A2 33
#define NOTE_A3 45
#define NOTE_A4 57
#define NOTE_A5 69
#define NOTE_A6 81
#define NOTE_A7 93
#define NOTE_C1 12
#define NOTE_C2 24
#define NOTE_C3 36
#define NOTE_C4 48
#define NOTE_C5 60
#define NOTE_C6 72
#define NOTE_C7 84
