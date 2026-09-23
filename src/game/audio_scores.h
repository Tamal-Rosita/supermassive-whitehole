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

#endif // AUDIO_SCORES_H
