//
// Created by Arthur on 23/02/2022.
//

#pragma once

#include "World.h"
#include "Player.h"

class Game {
private:
    Camera3D camera{};
    World world;
    Player player;
    std::time_t last_save;
    double last_key_space_pressed;
    void drawCursor();
    std::string getDebugText(const std::pair<const Vector3, B*>* selected_block) const;
    [[nodiscard]] const std::pair<const Vector3, B*>* getTargetedBlock() const;

public:
    Game();

    void start();
    void save();
    [[nodiscard]] std::string getCameraDirection() const;
    [[nodiscard]] Player* getPlayer();
    [[nodiscard]] World getWorld() const;

    void blockBreak(const std::pair<const Vector3, Block> *target);

    void blockPlace(const std::pair<const Vector3, Block> *target);
};

