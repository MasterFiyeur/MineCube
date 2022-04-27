//
// Created by cytech on 27/04/22.
//

#pragma once

#include <map>
#include "raylib.h"

enum SoundType {
    SOUND_BLOCK_BREAK,
    SOUND_BLOCK_PLACE
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
     * Update music buffer with new stream data
     */
    void updateMusic();
};
