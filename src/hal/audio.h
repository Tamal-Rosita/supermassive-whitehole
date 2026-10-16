// =============================================================================
// audio.h — Audio HAL Interface Contract
// =============================================================================
//
// PURPOSE:
//   Defines the audio abstraction layer for sound effects, musical cues,
//   and mute state control. Game logic files use HalAudio without depending
//   on hardware-specific tone libraries or AVR timer registers.
//
// ARDUBOY HARDWARE:
//   ATmega32u4 piezo speaker connected to pins PC6 (pin 5) and PC7 (pin 13).
//   Driven via hardware timers using the ArduboyTones non-blocking library.
//   Mute state is stored in EEPROM and queried via Arduboy2Audio.
//
// HOW IT WORKS:
//   1. Tones are defined as frequency/duration pairs in PROGMEM.
//   2. HalAudio provides non-blocking playback so 60 FPS gameplay is never interrupted.
//   3. When porting to Raylib or SDL2, implement audio.h using raylib PlaySound()
//      or SDL_mixer.
//
// =============================================================================

#ifndef HAL_AUDIO_H
#define HAL_AUDIO_H

#include <stdint.h>

// Sentinel values for PROGMEM tone arrays (compatible with ArduboyTones)
#ifndef TONES_END
#define TONES_END 0x8000
#endif
#ifndef TONES_REPEAT
#define TONES_REPEAT 0x8001
#endif

// =============================================================================
// Audio — API Contract
// =============================================================================
// Any platform audio struct MUST implement these methods:
//
//   void init();
//     Initialize audio hardware / buffers.
//
//   void tone(uint16_t freq, uint16_t duration);
//     Play a single frequency (Hz) for duration (milliseconds). Non-blocking.
//
//   void tones(const uint16_t* score);
//     Play a PROGMEM sequence of {freq, duration} pairs ending with TONES_END.
//
//   bool isPlaying();
//     Returns true if a tone/score is currently playing.
//
//   void stop();
//     Immediately silence any ongoing sound.
//
//   bool isAudioEnabled();
//     Returns whether sound output is currently unmuted.
//
//   void toggleAudio();
//     Toggle mute state and persist to storage if supported.
//
// =============================================================================

#endif // HAL_AUDIO_H
