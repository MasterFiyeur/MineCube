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
    void drawCursor();
    void drawDebugText(const std::pair<const Vector3, Block>* selected_block) const;
    [[nodiscard]] const std::pair<const Vector3, Block>* getTargetedBlock() const;

public:
    Game();

    void start();
    void save();
    [[nodiscard]] std::string getCameraDirection() const;
    [[nodiscard]] Player* getPlayer();
    [[nodiscard]] World getWorld() const;
};

