//
// Created by Arthur on 26/02/2022.
//

#include <utility>
#include "World.h"
#include "Utils.h"

World::World() {}

World::~World() {
    this->blocks.clear();
}

bool World::shouldBeDrawn(Vector3 pos, Player *player) const {
    Vector3 playerPos = player->getPosition();

    Vector3 dir = pos - playerPos;
    if (norm(dir) > RENDER_DISTANCE) {
        return false;
    }
    Vector3 playerDir = player->getDirection();
//    Vector3 playerUp = player->getUp();
    Vector3 ndir = normalize(dir);

    // remove half-circle behind the player
    float angle = acos(dotProduct(ndir, playerDir));
    if (angle > (M_PI / 2)) {
        return false;
    }

//    Vector3 cross = crossProduct(ndir, playerDir);
//    float dot = dotProduct(cross, playerUp);
//    std::cout << pos << " " << cross << "  " << dot << std::endl;
//    if (dot < 0) {
//        return false;
//    }

    return true;
}

void World::add_block(Block *block, Vector3 position) {
    this->blocks[position] = block;
}

void World::fill(Block *block, Vector3 start, Vector3 end) {
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
    return this->blocks.at(position);
}

std::map<Vector3, Block*> World::get_blocks() const {
    return this->blocks;
}

std::map<Vector3, Block*> World::get_blocks(Vector3 start, Vector3 end) const {
    std::map<Vector3, Block*> blocks_in_range;
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
        mit->second->draw(mit->first);
    }
}

void World::draw(Player *player) const {
    auto
            mit (blocks.begin()),
            mend(blocks.end());
    for(; mit!=mend; ++mit) {
        if (shouldBeDrawn(mit->first, player)) {
            mit->second->draw(mit->first);
        }
    }
}

bool World::isempty() const {
    return this->blocks.empty();
}

CHUNK World::get_chunk_coo(Vector3 position) const {
    int x = position.x >= 0 ? (int) position.x / 10 : (int) position.x / 10 - 1;
    int z = position.z >= 0 ? (int) position.z / 10 : (int) position.z / 10 - 1;
    return {x, z};
}
