#include "Core/AssetManager.h"
#include "Core/Log.h"
#include "Graphics/Texture.h"
#include <unordered_map>

namespace Maylib
{
    namespace Core
    {
        std::unordered_map<std::string, Texture*> AssetManager::s_textures{};

        Texture* AssetManager::GetTexture(const char* name) { return s_textures.at(name); }

        void AssetManager::AddTexture(const char* name, const char* type, const char* path)
        {
            if (s_textures.find(name) != s_textures.end())
            {
                LOG_ERROR("Cannot add texture %s because it already exists!", name);
                return;
            }

            Texture* texture = new Texture();
            texture->SetType(type);
            texture->Load(path);

            if (!texture)
            {
                LOG_ERROR("Cannot add texture %s because it failed to load!", name);
                return;
            }

            s_textures[name] = texture;
        }
    }
}
