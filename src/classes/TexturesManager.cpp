//
// Created by cytech on 27/02/2022.
//

#include <iostream>
#include <sys/stat.h>

#include "TexturesManager.h"

TexturesManager::TexturesManager() {
    loadTexture("missing_texture");
    this->defaultTexture = this->textures["missing_texture"];
}

void TexturesManager::loadTexture(const std::string& name) {
    std::string asset = "../assets/"+name+".png";
    this->textures[name] = LoadTexture(asset.c_str());
}

inline bool file_exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

Texture2D TexturesManager::getTexture(std::string name) {
    if (instance().unknownTextures.count(name) == 1) {
        return instance().defaultTexture;
    }
    auto iter = instance().textures.find(name);
    if (iter != instance().textures.end()) {
        return iter->second;
    } else if (file_exists("../assets/"+name+".png")) {
        instance().loadTexture(name);
        return instance().textures[name];
    } else {
        instance().unknownTextures.insert(name);
        std::cout << "NOPE" << std::endl;
        return instance().defaultTexture;
    }
}
