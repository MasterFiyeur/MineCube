//
// Created by Arthur Blaise on 23/02/2022.
//

#pragma once

#include <string>
#include "raylib.h"

class Block {
protected:
    std::string _name;
public:
    Block(): Block("stone") {}
    explicit Block(std::string name);
    virtual void draw(Vector3 position) const;
    [[nodiscard]] std::string getName() const;
};

class FullBlock : public Block {
    using Block::Block;
public:
    void draw(Vector3 position) const override;
};

class Grass : public Block {
    using Block::Block;
public:
    void draw(Vector3 position) const override;
};

class Flower : public Block {
    using Block::Block;
public:
    void draw(Vector3 position) const override;
};