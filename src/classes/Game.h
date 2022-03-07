//
// Created by Arthur on 23/02/2022.
//

#pragma once

#include "World.h"

class Game {
private:
    Camera3D camera{};
    World world;

    void drawCursor();
    void drawDebugText(const std::pair<const Vector3, Block>* selected_block) const;
    const std::pair<const Vector3, Block>* getTargetedBlock() const;
public:
    Game();

    void start();
    [[nodiscard]] std::string getCameraDirection() const;
};

