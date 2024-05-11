#pragma once
#include "Graphics/Texture.h"
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
            static void AddTexture(const char* name, const char* type, const char* path);

        private:
            static std::unordered_map<std::string, Texture*> s_textures;
        };
    }
}
