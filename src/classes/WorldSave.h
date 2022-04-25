//
// Created by Arthur on 28/02/2022.
//

#pragma once

#include "raylib.h"
#include "World.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Game;

struct SAVE {
    World world;
    Vector3 playerPosition;
    Vector3 playerOrientation;
    bool playerIsFlying;
};

class WorldSave {
private:
    static SAVE load_v1(json data);
    static SAVE load_v2(json data);
    static SAVE load_v3(json data);
public:
    static void save(Game* game);
    static SAVE load();
};
