//
// Created by Arthur on 28/02/2022.
//

#include "WorldSave.h"

#include <fstream>
#include <ctime>
#include <iostream>
#include <utility>
#include "raylib.h"

#include "World.h"
#include "Game.h"
#include "Utils.h"

#define WORLD_FILE "world.json"
#define DEFAULT_PLAYER_POSITION (Vector3) {0, 0, 0}
#define DEFAULT_PLAYER_ORIENTATION (Vector3) {0, 0, 0}
#define DEFAULT_PLAYER_FLYING false

std::string getISOCurrentTimestamp()
{
    time_t now;
    time(&now);
    char buf[sizeof "2022-01-01T01:01:01Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    return buf;
}

void WorldSave::save(Game* game) {
    json data;
    data["version"] = 3;
    data["date"] = getISOCurrentTimestamp();
    data["blocks"] = json::object();
    for (const auto& kv : game->getWorld().get_blocks()) {
        data["blocks"].emplace(Vector3toChar(kv.first), kv.second->getName());
    }

    data["player"] = {
            {"position", Vector3toChar(game->getPlayer()->getPosition())},
        {"orientation", Vector3toChar(game->getPlayer()->getOrientation())},
            {"is_flying", !game->getPlayer()->shouldApplyGravity()}
    };

    // write prettified JSON to another file
    std::ofstream o(WORLD_FILE);
    o << data << std::endl;
}

SAVE WorldSave::load() {
    // world never was created or was deleted
    if (!file_exists(WORLD_FILE)) {
        return {};
    }

    // open world file
    json data;
    std::ifstream i(WORLD_FILE);
    try {
        i >> data;
    } catch (json::parse_error& e) {
        std::cerr << "Error parsing JSON file: " << e.what() << std::endl;
        return {};
    }
    // correctly load file
    switch (data["version"].get<int>()) {
        case 1:
            return load_v1(data);
        case 2:
            return load_v2(data);
        case 3:
            return load_v3(data);
        default:
            throw std::runtime_error("Unsupported world save version");
    }
}

Vector3 stringToVector(const std::string& str) {
    std::stringstream ss(str);
    std::string x, y, z;
    std::getline(ss, x, ',');
    std::getline(ss, y, ',');
    std::getline(ss, z);
    return { std::stof(x), std::stof(y), std::stof(z) };
}

SAVE WorldSave::load_v1(json data) {
    SAVE save;
    for (auto& el: data["blocks"].items()) {
        Vector3 pos = stringToVector(el.key());
        add_block_by_name(save.world, el.value().get<std::string>(), pos);
    }
    save.playerPosition = DEFAULT_PLAYER_POSITION;
    save.playerOrientation = DEFAULT_PLAYER_ORIENTATION;
    save.playerIsFlying = DEFAULT_PLAYER_FLYING;
    return save;
}

SAVE WorldSave::load_v2(json data) {
    SAVE save;
    Vector3 pos;
    for (auto& el: data["blocks"].items()) {
        pos = stringToVector(el.key());
        add_block_by_name(save.world, el.value().get<std::string>(), pos);
    }
    save.playerPosition = stringToVector(data["player"]["position"]);
    save.playerOrientation = DEFAULT_PLAYER_ORIENTATION;
    save.playerIsFlying = DEFAULT_PLAYER_FLYING;
    return save;
}

SAVE WorldSave::load_v3(json data) {
    SAVE save;
    Vector3 pos;
    for (auto& el: data["blocks"].items()) {
        pos = stringToVector(el.key());
        add_block_by_name(save.world, el.value().get<std::string>(), pos);
    }
    save.playerPosition = stringToVector(data["player"]["position"]);
    save.playerOrientation = stringToVector(data["player"]["orientation"]);
    save.playerIsFlying = data["player"]["is_flying"].get<bool>();
    return save;
}
