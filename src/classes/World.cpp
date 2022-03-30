//
// Created by Arthur on 26/02/2022.
//

#include <utility>
#include "World.h"

World::World() {}

World::~World() {
    this->blocks.clear();
}

void World::add_block(Block block, Vector3 position) {
    this->blocks[position] = std::move(block);
}

void World::fill(const Block& block, Vector3 start, Vector3 end) {
    int xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = (int) std::min(start.x, end.x);
    xmax = (int) std::max(start.x, end.x);
    ymin = (int) std::min(start.y, end.y);
    ymax = (int) std::max(start.y, end.y);
    zmin = (int) std::min(start.z, end.z);
    zmax = (int) std::max(start.z, end.z);

    for (int x = xmin; x <= xmax; x++) {
        for (int y = ymin; y <= ymax; y++) {
            for (int z = zmin; z <= zmax; z++) {
                this->add_block(block, {(float) x, (float) y, (float) z});
            }
        }
    }
}

void World::remove_block(Vector3 position) {
    this->blocks.erase(position);
}

Block* World::get_block(Vector3 position) {
    return &this->blocks.at(position);
}

std::map<Vector3, Block> World::get_blocks() const {
    return this->blocks;
}

std::map<Vector3, Block> World::get_blocks(Vector3 start, Vector3 end) const {
    std::map<Vector3, Block> blocks_in_range;
    for (auto &block : this->blocks) {
        if (block.first.x >= start.x && block.first.x <= end.x &&
            block.first.y >= start.y && block.first.y <= end.y &&
            block.first.z >= start.z && block.first.z <= end.z) {
            blocks_in_range[block.first] = block.second;
        }
    }
    return blocks_in_range;
}

void World::draw() const {
    auto
        mit (blocks.begin()),
        mend(blocks.end());
    for(; mit!=mend; ++mit) {
        mit->second.draw(mit->first);
//        DrawBoundingBox(mit->second.getBoundingBox(mit->first), YELLOW);
    }
}

bool World::isempty() const {
    return this->blocks.empty();
}

bool operator<(const Vector3& o1, const Vector3 o2) {
    if (o1.x != o2.x) return o1.x < o2.x;
    if (o1.y != o2.y) return o1.y < o2.y;
    return o1.z < o2.z;
}

bool operator==(const Vector3& o1, const Vector3 o2) {
    return o1.x == o2.x && o1.y == o2.y && o1.z == o2.z;
}

Vector3 operator+(const Vector3& o1, const Vector3 o2) {
    return (Vector3) {o1.x + o2.x, o1.y + o2.y, o1.z + o2.z};
}

Vector3 operator-(const Vector3& o1, const Vector3 o2) {
    return (Vector3) {o1.x - o2.x, o1.y - o2.y, o1.z - o2.z};
}
