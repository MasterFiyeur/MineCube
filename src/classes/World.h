//
// Created by Arthur on 26/02/2022.
//

#pragma once

#include <map>
#include <ctime>
#include "Block.h"
#include "raylib.h"
#include "Player.h"


class World {
private:
    std::map<Vector3, Block> blocks;
public:
    World();
    ~World();
    void add_block(Block block, Vector3 position);
    void fill(const Block& block, Vector3 start, Vector3 end);
    void remove_block(Vector3 position);
    Block* get_block(Vector3 position);
    [[nodiscard]] std::map<Vector3, Block> get_blocks() const;
    [[nodiscard]] std::map<Vector3, Block> get_blocks(Vector3 start, Vector3 end) const;
    [[nodiscard]] bool isempty() const;
    void draw() const;
};
