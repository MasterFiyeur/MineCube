//
// Created by Arthur Blaise on 23/02/2022.
//

#pragma once

#include <string>
#include "raylib.h"

class B {
protected:
    std::string _name;
public:
    virtual void draw(Vector3 position) const = 0;
    [[nodiscard]] virtual std::string getName() const {return _name;};
    [[nodiscard]] virtual BoundingBox getBoundingBox(Vector3 position) const = 0;
};

class Block: public B {
protected:
    std::string _name;
public:
    Block(): Block("stone") {}
    explicit Block(std::string name);
    void draw(Vector3 position) const override;
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] BoundingBox getBoundingBox(Vector3 position) const override;
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
    [[nodiscard]] BoundingBox getBoundingBox(Vector3 position) const override;
};