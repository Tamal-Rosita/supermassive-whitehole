// =============================================================================
// arduboy_audio.h — Arduboy Audio HAL Implementation
// =============================================================================
//
// Wraps ArduboyTones and Arduboy2Audio to satisfy the HalAudio contract.
// Uses lightweight timer-driven non-blocking audio compatible with ATmega32u4
// hardware and ProjectABE web emulator AudioContext.
//
// =============================================================================

#ifndef ARDUBOY_AUDIO_H
#define ARDUBOY_AUDIO_H

#include "../../hal/audio.h"
#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <stdint.h>

struct ArduboyAudio {
    ArduboyTones sound;
    Arduboy2Audio& audioRef;

    ArduboyAudio(Arduboy2Audio& audio)
        : sound(audio.enabled), audioRef(audio) {}

    void init() {
        audioRef.on();
        sound.volumeMode(VOLUME_ALWAYS_NORMAL);
    }

    void tone(uint16_t freq, uint16_t duration) {
        sound.tone(freq, duration);
    }

    void tones(const uint16_t* score) {
        sound.tones(score);
    }

    bool isPlaying() {
        return sound.playing();
    }

    void stop() {
        sound.noTone();
    }

    bool isAudioEnabled() {
        return audioRef.enabled();
    }

    void toggleAudio() {
        audioRef.toggle();
        audioRef.saveOnOff();
    }
};

#endif // ARDUBOY_AUDIO_H
