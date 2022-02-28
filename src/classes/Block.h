//
// Created by Arthur Blaise on 23/02/2022.
//

#pragma once

#include <string>
#include "raylib.h"

class Block {
private:
    std::string _name;
public:
    Block(): Block("stone") {}
    explicit Block(std::string name);
    void draw(Vector3 position) const;
    [[nodiscard]] std::string getName() const;
};
