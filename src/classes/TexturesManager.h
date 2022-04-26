//
// Created by Arthur on 27/02/2022.
//

#pragma once

#include <unordered_map>
#include <set>
#include <string>

class TexturesManager {
private:
    TexturesManager();
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Model> models;
    std::set<std::string> unknownTextures;
    std::set<std::string> unknownModels;
    Texture2D defaultTexture{};
    Model defaultModel{};
    Shader *shader;
    void loadTexture(const std::string& name);
public:
    TexturesManager(const TexturesManager&) = delete;
    ~TexturesManager();

    static auto& instance(){
        static TexturesManager manager;
        return manager;
    }
    static Texture2D* getTexture(const std::string& name);
    static Model* getModel(const std::string& name);
    static void setShader(Shader *shader);
};
