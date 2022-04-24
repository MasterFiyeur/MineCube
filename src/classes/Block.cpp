//
// Created by Arthur Blaise on 23/02/2022.
//

#include "Block.h"
#include "TexturesManager.h"
#include <utility>

Block::Block(std::string name) {
    this->_name = std::move(name);
}

std::string Block::getName() const {
    return this->_name;
}

void Block::draw(Vector3 position) const {

}

void FullBlock::draw(Vector3 position) const {
    DrawCubeTexture(TexturesManager::getTexture(_name), position, 1.0f, 1.0f, 1.0f, WHITE);
}

void Grass::draw(Vector3 position) const {
    Vector3 position1 = position;
    position1.y = position1.y + 0.5;
    DrawCubeTexture(TexturesManager::getTexture("grass_block_top"), position1, 1.0f, 0, 1.0f, WHITE);

    Vector3 position2 = position;
    position2.x = position.x - 0.5;
    DrawCubeTexture(TexturesManager::getTexture("grass_block_side"), position2, 0, -1.0f, 1.0f, WHITE);

    Vector3 position3 = position;
    position3.x = position.x + 0.5;
    DrawCubeTexture(TexturesManager::getTexture("grass_block_side"), position3, 0, -1.0f, 1.0f, WHITE);

    Vector3 position4 = position;
    position4.z = position.z + 0.5;
    DrawCubeTexture(TexturesManager::getTexture("grass_block_side"), position4, 1.0f, -1.0f, 0, WHITE);

    Vector3 position5 = position;
    position5.z = position.z - 0.5;
    DrawCubeTexture(TexturesManager::getTexture("grass_block_side"), position5, 1.0f, -1.0f,0, WHITE);

    Vector3 position6 = position;
    position6.y = position6.y - 0.5;
    DrawCubeTexture(TexturesManager::getTexture("dirt"), position6, 1.0f, 0, 1.0f, WHITE);

}


void Flower::draw(Vector3 position) const {
    DrawCubeTexture(TexturesManager::getTexture("white_tulip"), position, 0, -1.0f, 1.0f, WHITE);
    DrawCubeTexture(TexturesManager::getTexture("white_tulip"), position, 1.0f, -1.0f,0, WHITE);
}
