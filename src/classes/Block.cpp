//
// Created by Arthur Blaise on 23/02/2022.
//

#include "raylib.h"
#include "Block.h"
#include <utility>

Block::Block(std::string name, float x, float y, float z) {
    this->_name = std::move(name);
    this->_position = Vector3{x, y, z};

    std::string asset = "../assets/"+_name+".png";
    Image image = LoadImage(asset.c_str());
    this->_texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Block::~Block() {
    UnloadTexture(_texture);
}

void Block::draw() const {
    DrawCubeTexture(_texture, _position, 1.0f, 1.0f, 1.0f, WHITE);
}



