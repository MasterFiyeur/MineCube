//
// Created by Arthur Blaise on 23/02/2022.
//

#pragma once

#include <string>
#include "raylib.h"

class Block {
private:
    std::string _name;
    bool _multipleFaces;
public:
    Block(): Block("stone", 0) {}
    explicit Block(std::string name, bool multipleFaces = 0);
    void draw(Vector3 position) const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] bool getMultipleFaces() const;
};
