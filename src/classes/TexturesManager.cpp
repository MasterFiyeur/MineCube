//
// Created by Arthur on 27/02/2022.
//

#include <iostream>
#include "raylib.h"

#include "TexturesManager.h"
#include "Utils.h"

TexturesManager::TexturesManager() {
    loadTexture("missing_texture");
    this->defaultTexture = this->textures["missing_texture"];
    this->defaultModel = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
}

TexturesManager::~TexturesManager() {
    for (auto &texture : this->textures) {
        UnloadTexture(texture.second);
    }
    for (auto &model : this->models) {
        UnloadModel(model.second);
    }
}

void TexturesManager::loadTexture(const std::string& name) {
    std::string asset = "../assets/"+name+".png";
    this->textures[name] = LoadTexture(asset.c_str());
    GenTextureMipmaps(&this->textures[name]);
    SetTextureFilter(this->textures[name], TEXTURE_FILTER_POINT);
}

Texture2D* TexturesManager::getTexture(const std::string& name) {
    if (instance().unknownTextures.count(name) == 1) {
        return &instance().defaultTexture;
    }
    auto iter = instance().textures.find(name);
    if (iter != instance().textures.end()) {
        return &iter->second;
    } else if (file_exists("../assets/"+name+".png")) {
        instance().loadTexture(name);
        return &instance().textures[name];
    } else {
        instance().unknownTextures.insert(name);
        std::cout << "ERROR: unknown texture " << name << std::endl;
        return &instance().defaultTexture;
    }
}

Model* TexturesManager::getModel(const std::string& name) {
    if (instance().unknownModels.count(name) == 1) {
        return &instance().defaultModel;
    }
    try {
        return &instance().models.at(name);
    } catch (const std::out_of_range& e) {
        // unknown model
         if (file_exists("../assets/models/"+name+".obj")) {
             std::cout << "found model " << name << std::endl;
             Model model = LoadModel(("../assets/models/"+name+".obj").c_str());
             for (int i=0; i<model.materialCount; i++) {
                 model.materials[i].shader = *(instance().shader);
             }
             instance().models[name] = model;
             return &instance().models[name];
         } else if (file_exists("../assets/"+name+".png")) {
             std::cout << "found texture " << name << std::endl;
             Model model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
             model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(getTexture(name));
             model.materials[0].shader = *(instance().shader);
             instance().models[name] = model;
             return &instance().models[name];
        } else {
             instance().unknownModels.insert(name);
             std::cout << "ERROR: unknown model " << name << std::endl;
             instance().defaultModel = *TexturesManager::getModel("missing_texture");
             return &instance().defaultModel;
         }
    }
}

void TexturesManager::setShader(Shader *shader) {
    instance().shader = shader;
}