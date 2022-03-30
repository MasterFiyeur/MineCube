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

std::string getISOCurrentTimestamp()
{
    time_t now;
    time(&now);
    char buf[sizeof "2022-01-01T01:01:01Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    return buf;
}

void WorldSave::save(Game* game) {
    char pos[50];
    json data;
    data["version"] = 2;
    data["date"] = getISOCurrentTimestamp();
    data["blocks"] = json::object();
    for (const auto& kv : game->getWorld().get_blocks()) {
        snprintf(pos, sizeof pos, "%.1f,%.1f,%.1f", kv.first.x, kv.first.y, kv.first.z);
        data["blocks"].emplace(pos, kv.second.getName());
    }
    Vector3 position = game->getPlayer().getPosition();
    snprintf(pos, sizeof pos, "%.1f,%.1f,%.1f", position.x, position.y, position.z);
    data["player"] = {
            {"position", pos}
    };

    // write prettified JSON to another file
    std::ofstream o(WORLD_FILE);
    o << data << std::endl;
}

std::pair<World, Vector3> WorldSave::load() {
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

std::pair<World, Vector3> WorldSave::load_v1(json data) {
    World world;
    for (auto& el: data["blocks"].items()) {
        Vector3 pos = stringToVector(el.key());
        world.add_block(Block(el.value().get<std::string>()), pos);
    }
    return std::pair<World, Vector3>(world, {0, 2, 0});
}

std::pair<World, Vector3> WorldSave::load_v2(json data) {
    World world;
    Vector3 pos;
    for (auto& el: data["blocks"].items()) {
        pos = stringToVector(el.key());
        world.add_block(Block(el.value().get<std::string>()), pos);
    }
    pos = stringToVector(data["player"]["position"]);
    return std::pair<World, Vector3>(world, pos);
}

