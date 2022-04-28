//
// Created by Arthur on 27/02/2022.
//

#pragma once

#include <unordered_map>
#include <set>
#include <string>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif
#define RLIGHTS_IMPLEMENTATION

class TexturesManager {
private:
    TexturesManager();
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Model> models;
    std::set<std::string> unknownTextures;
    std::set<std::string> unknownModels;
    Texture2D defaultTexture{};
    Model defaultModel{};

    Shader fog_ambient_shader;
    Shader ambient_shader;
    int fog_ambient_location;
    int ambient_ambient_location;
    int fog_color_location;

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

    static Shader* getFogShader();
    static Shader* getClassicShader();
    static void setShaderBrightness(float brightness);
    static void setShaderColor(float color[4]);
    static void setShaderPosition(Vector3 position);
};
