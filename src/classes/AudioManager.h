//
// Created by cytech on 27/04/22.
//

#pragma once

#include <map>
#include "raylib.h"
#include <string>

enum SoundType {
    SOUND_BLOCK_BREAK_STONE,
    SOUND_BLOCK_PLACE_STONE,
    SOUND_BLOCK_BREAK_DIRT,
    SOUND_BLOCK_PLACE_DIRT,
    SOUND_BLOCK_BREAK_GLASS,
    SOUND_BLOCK_PLACE_GLASS,
    SOUND_BLOCK_BREAK_GRASS,
    SOUND_BLOCK_PLACE_GRASS,
    SOUND_BLOCK_BREAK_SOUL_SOIL,
    SOUND_BLOCK_PLACE_SOUL_SOIL,
};

class AudioManager {
private:
    std::map<SoundType, Sound> sounds;
    Music ambient;

public:
    AudioManager() = default;
    ~AudioManager();

    /**
     * Load sounds and music, and start ambient music
     */
    void init();

    /**
     * Play a sound once
     * @param soundType The sound to play
     */
    void playSound(SoundType soundType);

    /**
     * Find which sound should be played for a block break
     * @param block The block being broken
     * @return The corresponding sound
     */
    static SoundType getSoundTypeBreak(const std::string& block);

    /**
     * Find which sound should be played for a block placing
     * @param block The block being placed
     * @return The corresponding sound
     */
    static SoundType getSoundTypePlace(const std::string& block);

    /**
     * Update music buffer with new stream data
     */
    void updateMusic();
};
