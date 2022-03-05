//
// Created by Arthur on 26/02/2022.
//

#pragma once

#include <map>
#include <ctime>
#include "Block.h"
#include "raylib.h"

class World {
private:
    std::map<Vector3, Block> blocks;
    std::time_t last_save;

public:
    World();
    ~World();
    void add_block(Block block, Vector3 position);
    void fill(const Block& block, Vector3 start, Vector3 end);
    void remove_block(Vector3 position);
    Block* get_block(Vector3 position);
    std::map<Vector3, Block> get_blocks();
    bool isempty();
    void draw() const;
    void save();
};

bool operator<(const Vector3& o1, Vector3 o2);
bool operator==(const Vector3& o1, Vector3 o2);