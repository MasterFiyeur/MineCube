//
// Created by Arthur Blaise on 23/02/2022.
//

#pragma once

#include "World.h"
#include "Player.h"

class Game {
private:
    Camera3D camera;
    World world;
    Player player;
public:
    Game();

    void start();
};

