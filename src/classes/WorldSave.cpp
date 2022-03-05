//
// Created by Arthur on 28/02/2022.
//

#include "WorldSave.h"

#include <fstream>
#include <ctime>
#include <iostream>

#include "World.h"
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

void WorldSave::save(World* world) {
    json data;
    data["version"] = 1;
    data["date"] = getISOCurrentTimestamp();
    data["blocks"] = json::object();
    for (const auto& kv : world->get_blocks()) {
        char pos[50];
        snprintf(pos, sizeof pos, "%.1f,%.1f,%.1f", kv.first.x, kv.first.y, kv.first.z);
        data["blocks"].emplace(pos, kv.second.getName());
    }

    // write prettified JSON to another file
    std::ofstream o(WORLD_FILE);
    o << data << std::endl;
}

World WorldSave::load() {
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

World WorldSave::load_v1(json data) {
    World world;
    for (auto& el: data["blocks"].items()) {
        Vector3 pos = stringToVector(el.key());
//        std::cout << pos.x << " " << pos.y << " " << pos.z << " : " << el.value() << std::endl;
        world.add_block(Block(el.value().get<std::string>()), pos);
    }
    return world;
}
