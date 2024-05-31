#pragma once
#include "Core/Base.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include <memory>
#include <string>
#include <unordered_map>

using namespace Maylib::Graphics;

namespace Maylib
{
    namespace Core
    {
        class AssetManager
        {
        public:
            static Texture* GetTexture(const char* name);
            static Shader* GetShader(const char* name);

            static void AddTexture(const char* name, const char* path, TextureMapType type, bool flip = false,
                                   bool alpha = false);
            static void AddShader(const char* name, const char* vertexPath, const char* fragmentPath);

            static void Clean();

        private:
            static std::unordered_map<std::string, Ref<Texture>> s_textures;
            static std::unordered_map<std::string, Ref<Shader>> s_shaders;
        };
    }
}
