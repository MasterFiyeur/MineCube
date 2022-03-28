//
// Created by Arthur Blaise on 23/02/2022.
//

#include "Block.h"
#include "TexturesManager.h"
#include <utility>

Block::Block(std::string name, bool multipleFaces) {
    this->_name = std::move(name);
    this->_multipleFaces = multipleFaces;
}

void Block::draw(Vector3 position) const {
    DrawCubeTexture(TexturesManager::getTexture(_name), position, 1.0f, 1.0f, 1.0f, WHITE);
}

std::string Block::getName() const {
    return this->_name;
}

bool Block::getMultipleFaces() const {
    return this->_multipleFaces;
}
