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

    fog_ambient_shader = LoadShader(TextFormat("../assets/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                               TextFormat("../assets/shaders/glsl%i/fog.fs", GLSL_VERSION));
    fog_ambient_shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(fog_ambient_shader, "matModel");
    fog_ambient_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(fog_ambient_shader, "viewPos");
    fog_ambient_location = GetShaderLocation(fog_ambient_shader, "ambient");
    fog_color_location = GetShaderLocation(fog_ambient_shader, "fogColor");

    ambient_shader = LoadShader(TextFormat("../assets/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                               TextFormat("../assets/shaders/glsl%i/ambient.fs", GLSL_VERSION));
    ambient_shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(ambient_shader, "matModel");
    ambient_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(ambient_shader, "viewPos");
    ambient_ambient_location = GetShaderLocation(ambient_shader, "ambient");
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
             for (int i = 0; i < model.materialCount; i++) {
                 model.materials[i].shader = *(getFogShader());
             }
             instance().models[name] = model;
             return &instance().models[name];
         } else if (file_exists("../assets/"+name+".png")) {
             std::cout << "found texture " << name << std::endl;
             Model model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
             model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(getTexture(name));
             model.materials[0].shader = *(getFogShader());
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

Shader* TexturesManager::getFogShader() {
    return &instance().fog_ambient_shader;
}

Shader* TexturesManager::getClassicShader() {
    return &instance().ambient_shader;
}

void TexturesManager::setShaderBrightness(float brightness) {
    SetShaderValue(instance().fog_ambient_shader, instance().fog_ambient_location, (float[4]) {brightness, brightness, brightness, brightness}, SHADER_UNIFORM_VEC4);
    SetShaderValue(instance().ambient_shader, instance().ambient_ambient_location, (float[4]) {brightness, brightness, brightness, brightness}, SHADER_UNIFORM_VEC4);
}

void TexturesManager::setShaderColor(float color[4]) {
    SetShaderValue(instance().fog_ambient_shader, instance().fog_color_location, color, SHADER_UNIFORM_VEC4);
}

void TexturesManager::setShaderPosition(Vector3 position) {
    SetShaderValue(instance().fog_ambient_shader, instance().fog_ambient_shader.locs[SHADER_LOC_VECTOR_VIEW], &position, SHADER_UNIFORM_VEC3);
    SetShaderValue(instance().ambient_shader, instance().ambient_shader.locs[SHADER_LOC_VECTOR_VIEW], &position, SHADER_UNIFORM_VEC3);
}
