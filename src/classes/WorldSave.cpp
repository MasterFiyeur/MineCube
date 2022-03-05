//
// Created by Arthur on 28/02/2022.
//

#include "WorldSave.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <ctime>

using json = nlohmann::json;

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
    std::ofstream o("world.json");
    o << std::setw(4) << data << std::endl;
}

World WorldSave::load() {
    return World();
}
