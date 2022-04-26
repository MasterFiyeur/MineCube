//
// Created by Arthur Blaise on 23/02/2022.
//

#include "Block.h"
#include "TexturesManager.h"
#include <utility>

Block::Block(std::string name) {
    this->_name = std::move(name);
}

void Block::draw(Vector3 position) const {
    DrawModel(TexturesManager::getModel(_name), position, 1.0f, WHITE);
//    DrawCubeTexture(TexturesManager::getTexture(_name), position, 1.0f, 1.0f, 1.0f, WHITE);
}

std::string Block::getName() const {
    return this->_name;
}

BoundingBox Block::getBoundingBox(Vector3 position) const {
    return (BoundingBox) {
            (Vector3) {
                position.x - 0.5f,
                position.y - 0.5f,
                position.z - 0.5f
            },
            (Vector3) {
                position.x + 0.5f,
                position.y + 0.5f,
                position.z + 0.5f
            }
    };
}
