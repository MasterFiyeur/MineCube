//
// Created by cytech on 27/04/22.
//

#include "AudioManager.h"

AudioManager::~AudioManager() {
    for (auto &sound : this->sounds) {
        UnloadSound(sound.second);
    }
    UnloadMusicStream(ambient);
    CloseAudioDevice();
}

void AudioManager::init() {
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);
    this->sounds[SOUND_BLOCK_BREAK_STONE] = LoadSound("../assets/sounds/stone_break.ogg");
    this->sounds[SOUND_BLOCK_PLACE_STONE] = LoadSound("../assets/sounds/stone_place.ogg");
    this->sounds[SOUND_BLOCK_BREAK_DIRT] = LoadSound("../assets/sounds/dirt_break.ogg");
    this->sounds[SOUND_BLOCK_PLACE_DIRT] = LoadSound("../assets/sounds/dirt_place.ogg");
    this->sounds[SOUND_BLOCK_BREAK_GLASS] = LoadSound("../assets/sounds/glass_break.ogg");
    this->sounds[SOUND_BLOCK_PLACE_GLASS] = LoadSound("../assets/sounds/glass_place.ogg");
    this->sounds[SOUND_BLOCK_BREAK_GRASS] = LoadSound("../assets/sounds/grass_break.ogg");
    this->sounds[SOUND_BLOCK_PLACE_GRASS] = LoadSound("../assets/sounds/grass_place.ogg");
    this->sounds[SOUND_BLOCK_BREAK_SOUL_SOIL] = LoadSound("../assets/sounds/soulsoil_break.ogg");
    this->sounds[SOUND_BLOCK_PLACE_SOUL_SOIL] = LoadSound("../assets/sounds/soulsoil_place.ogg");
    this->ambient = LoadMusicStream("../assets/sounds/ambient.ogg");

    // launch ambient music
    SetMusicVolume(ambient, 0.7);
    PlayMusicStream(ambient);
}

void AudioManager::playSound(SoundType soundType) {
    PlaySound(sounds[soundType]);
}

SoundType AudioManager::getSoundTypeBreak(const std::string& block) {
    if (block == "dirt") {
        return SOUND_BLOCK_BREAK_DIRT;
    } else if (block == "glass") {
        return SOUND_BLOCK_BREAK_GLASS;
    } else if (block == "grass_block" || block == "sponge" || block == "white_tulip") {
        return SOUND_BLOCK_BREAK_GRASS;
    } else if (block == "soul_soil") {
        return SOUND_BLOCK_BREAK_SOUL_SOIL;
    } else {
        // default
        return SOUND_BLOCK_BREAK_STONE;
    }
}

SoundType AudioManager::getSoundTypePlace(const std::string& block) {
    if (block == "dirt") {
        return SOUND_BLOCK_PLACE_DIRT;
    } else if (block == "glass") {
        return SOUND_BLOCK_PLACE_GLASS;
    } else if (block == "grass_block" || block == "sponge" || block == "white_tulip") {
        return  SOUND_BLOCK_PLACE_GRASS;
    } else if (block == "soul_soil") {
        return SOUND_BLOCK_PLACE_SOUL_SOIL;
    } else {
        // default
        return SOUND_BLOCK_PLACE_STONE;
    }
}

void AudioManager::updateMusic() {
    UpdateMusicStream(ambient);
}

