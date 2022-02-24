//
// Created by Arthur Blaise on 23/02/2022.
//

#pragma once

#include <string>


class Block {
private:
    std::string _name;
    Texture2D _texture;
    Vector3 _position;
public:
    explicit Block(std::string name, float x, float y, float z);
    ~Block();
    void draw() const;
};
