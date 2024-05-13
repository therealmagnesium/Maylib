#pragma once
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

            static void AddTexture(const char* name, const char* type, const char* path, bool alpha = false);
            static void Clean();

        private:
            static std::unordered_map<std::string, std::shared_ptr<Texture>> s_textures;
        };
    }
}
