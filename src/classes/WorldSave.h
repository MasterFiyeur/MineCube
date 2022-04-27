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

static void add_block_by_name(World& world, const std::string& name, const Vector3& pos) {
    if (name == "grass_block") {
        world.add_block(new Grass(), pos);
    } else if (name == "white_tulip") {
        world.add_block(new Flower(name), pos);
    } else {
        world.add_block(new FullBlock(name), pos);
    }
}
