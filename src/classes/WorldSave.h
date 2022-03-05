//
// Created by Arthur on 28/02/2022.
//

#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class World;

class WorldSave {
private:
    static World load_v1(json data);
public:
    static void save(World* world);
    static World load();
};
