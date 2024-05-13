#include "Core/AssetManager.h"
#include "Core/Log.h"
#include "Graphics/Texture.h"
#include <memory>
#include <unordered_map>

namespace Maylib
{
    namespace Core
    {
        std::unordered_map<std::string, std::shared_ptr<Texture>> AssetManager::s_textures{};

        Texture* AssetManager::GetTexture(const char* name) { return s_textures.at(name).get(); }

        void AssetManager::AddTexture(const char* name, const char* type, const char* path, bool alpha)
        {
            if (s_textures.find(name) != s_textures.end())
            {
                LOG_ERROR("Cannot add texture %s because it already exists!", name);
                return;
            }

            std::shared_ptr<Texture> texture = std::make_shared<Texture>();
            texture->SetType(type);
            texture->Load(path, alpha);

            if (!texture)
            {
                LOG_ERROR("Cannot add texture %s because it failed to load!", name);
                return;
            }

            s_textures[name] = texture;
        }

        void AssetManager::Clean() { s_textures.clear(); }
    }
}
