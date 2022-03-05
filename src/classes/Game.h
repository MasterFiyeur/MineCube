//
// Created by Arthur on 23/02/2022.
//

#pragma once

#include "World.h"

class Game {
private:
    Camera3D camera{};
    World world;
public:
    Game();

    void start();
};

