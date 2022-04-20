//
// Created by Arthur on 28/02/2022.
//

#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Game;
class World;
class Vector3;

class WorldSave {
private:
    static std::pair<World, Vector3> load_v1(json data);
    static std::pair<World, Vector3> load_v2(json data);
public:
    static void save(Game* game);
    static std::pair<World, Vector3> load();
};
