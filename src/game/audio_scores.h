// =============================================================================
// audio_scores.h — PROGMEM Sound Effect & Ambient Tone Sequences
// =============================================================================
//
// Musical notes & sound effects defined as {frequency_hz, duration_ms} pairs,
// terminated with TONES_END. Stored in PROGMEM to minimize SRAM usage.
// Compatible with ArduboyTones.
//
// =============================================================================

#ifndef AUDIO_SCORES_H
#define AUDIO_SCORES_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "../hal/audio.h"

// Sound IDs for triggering game audio cues
enum SoundId : uint8_t {
    SOUND_NONE = 0,
    SOUND_ID_THEME,
    SOUND_ID_DIAMOND,
    SOUND_ID_BILLS,
    SOUND_ID_BOOST,
    SOUND_ID_FOOD,
    SOUND_ID_ABSORB,
    SOUND_ID_GAMEOVER,
    SOUND_ID_MENU,
    SOUND_ID_AMBIENT_BEAT,
};

// 1. Diamond collected: high crisp double-chime (C6 -> G6)
const uint16_t sound_diamond[] PROGMEM = {
    1046, 45,
    1568, 90,
    TONES_END
};

// 2. Dollar bills collected: cheerful 3-note ascending fanfare (A5 -> D6 -> A6)
const uint16_t sound_bills[] PROGMEM = {
    880, 40,
    1175, 50,
    1760, 110,
    TONES_END
};

// 3. Coffee boost activated: rising rapid turbo arpeggio (C5 -> E5 -> G5 -> C6)
const uint16_t sound_boost[] PROGMEM = {
    523, 35,
    659, 35,
    784, 35,
    1046, 80,
    TONES_END
};

// 4. Food collision: low descending crunch/thud (A3 -> E3 -> A2)
const uint16_t sound_food[] PROGMEM = {
    220, 50,
    165, 70,
    110, 100,
    TONES_END
};

// 5. Whitehole absorption: deep cosmic consumption rumble (C3 -> G2 -> C2)
const uint16_t sound_absorb[] PROGMEM = {
    130, 40,
    98, 60,
    65, 80,
    TONES_END
};

// 6. Game Over: dramatic melancholic descent (G4 -> F#4 -> E4 -> C4)
const uint16_t sound_gameover[] PROGMEM = {
    392, 120,
    370, 120,
    330, 140,
    262, 280,
    TONES_END
};

// 7. Menu selection / Button tap: snappy clean blip (A5, 25ms)
const uint16_t sound_menu[] PROGMEM = {
    880, 25,
    TONES_END
};

// 8. Ambient heartbeat / cosmic pulse: rhythmic low throb (D2 -> A2)
const uint16_t sound_ambient_beat[] PROGMEM = {
    73, 40,
    110, 40,
    TONES_END
};

// 9. Main Soundtrack: converted from assets/smwh_score.mid (26s monophonic loop)
const uint16_t sound_smwh_theme[] PROGMEM = {
     175, 220,  262, 268,  208,  93,    0,  57,
     233, 116,  311, 349,  196,  57,  233, 268,
     156,  68,  233, 175,  196, 127,  156,  82,
       0,  57,  196, 535,  131,  93,  196, 358,
       0,  70,  175, 209,  262, 291,  175, 139,
     262, 244,  208, 130,    0,  56,  233, 663,
     156, 195,  262, 640,  196, 220,  233, 152,
       0,  59,  262, 429,  175, 220,  208, 198,
     175, 221,  208,  57,  262, 197,  208,  59,
       0, 127,  233, 268,  196, 139,  311, 164,
     233,  45,  196, 372,  131,  57,  156, 105,
       0, 116,  156,  82,  196, 163,    0, 266,
     131, 139,  196, 395,    0,  59,  175, 198,
     262, 209,  208,  93,  175, 127,  262, 359,
       0,  59,  233, 626,  156, 244,  262, 200,
     208, 220,  262, 172,    0, 257,  233, 161,
       0,  48,  262, 429,  831, 232, 1661, 150,
     831, 686, 1661, 163,  831, 277,  415,  47,
     311,  68, 1245, 140,  415, 116,  311,  56,
    1568, 152,  311,  57,  784, 175,  311, 254,
    1865, 129,  932, 291, 1047, 220, 1568, 138,
    1047, 905,  698, 881, 1109, 395,  554, 683,
    1397, 175,  554, 431,  277,  34,  831, 1473,
     262,  34, 1568, 164,  262,  48,  311, 326,
     156, 161,    0, 150,  311,  25, 1865, 256,
     932, 359, 1047, 1245,  698, 694, 1397, 175,
       0,  45,  831, 675,
    TONES_REPEAT
};

#endif // AUDIO_SCORES_H
