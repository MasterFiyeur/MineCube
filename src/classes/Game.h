//
// Created by Arthur on 23/02/2022.
//

#pragma once

#include "World.h"
#include "Player.h"
#include "AudioManager.h"

class Game {
private:
    Camera3D camera{};
    World world;
    Player player;
    std::time_t last_save;
    AudioManager audio;
    double last_key_space_pressed;
    void drawCursor();
    std::string getDebugText(const std::pair<const Vector3, Block*>* selected_block) const;
    std::string getHelpText() const;
    [[nodiscard]] const std::pair<const Vector3, Block*>* getTargetedBlock() const;

    [[nodiscard]] float getSkyBrightness() const;
    [[nodiscard]] Color getSkyColor() const;
	[[nodiscard]] Color getSunColor() const;

public:
    Game();

    void start();
    void save();
    [[nodiscard]] std::string getCameraDirection() const;
    [[nodiscard]] Player* getPlayer();
    [[nodiscard]] World getWorld() const;

    void blockBreak(const std::pair<const Vector3, Block*> *target);

    void blockPlace(const std::pair<const Vector3, Block*> *target);

    [[nodiscard]] float getDaytime() const;
    [[nodiscard]] int getDayHour() const;
    [[nodiscard]] int getDayMinute() const;
};

