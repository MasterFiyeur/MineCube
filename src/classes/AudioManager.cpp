//
// Created by cytech on 27/04/22.
//

#include "AudioManager.h"

AudioManager::~AudioManager() {
    UnloadSound(sounds[SOUND_BLOCK_BREAK]);
    UnloadSound(sounds[SOUND_BLOCK_PLACE]);
    UnloadMusicStream(ambient);
    CloseAudioDevice();
}

void AudioManager::init() {
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);
    this->sounds[SOUND_BLOCK_BREAK] = LoadSound("../assets/sounds/block_break.ogg");
    this->sounds[SOUND_BLOCK_PLACE] = LoadSound("../assets/sounds/block_place.ogg");
    this->ambient = LoadMusicStream("../assets/sounds/ambient.ogg");

    // launch ambient music
    PlayMusicStream(ambient);
}

void AudioManager::playSound(SoundType soundType) {
    PlaySound(sounds[soundType]);
}

void AudioManager::updateMusic() {
    UpdateMusicStream(ambient);
}
