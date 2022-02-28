//
// Created by cytech on 27/02/2022.
//

#pragma once

#include <unordered_map>
#include <set>
#include <string>
#include "raylib.h"

class TexturesManager {
private:
    TexturesManager();
    std::unordered_map<std::string, Texture2D> textures;
    std::set<std::string> unknownTextures;
    Texture2D defaultTexture{};
    void loadTexture(const std::string& name);
public:
    TexturesManager(const TexturesManager&) = delete;

    static auto& instance(){
        static TexturesManager manager;
        return manager;
    }
    static Texture2D getTexture(std::string name);
};
