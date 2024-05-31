#include "Core/AssetManager.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <memory>
#include <unordered_map>

namespace Maylib
{
    namespace Core
    {
        std::unordered_map<std::string, std::shared_ptr<Texture>> AssetManager::s_textures{};
        std::unordered_map<std::string, std::shared_ptr<Shader>> AssetManager::s_shaders{};

        Texture* AssetManager::GetTexture(const char* name) { return s_textures[name].get(); }
        Shader* AssetManager::GetShader(const char* name) { return s_shaders[name].get(); }

        void AssetManager::AddTexture(const char* name, const char* path, TextureMapType type, bool flip, bool alpha)
        {
            if (s_textures.find(name) != s_textures.end())
            {
                LOG_ERROR("Cannot add texture %s because it already exists!", name);
                return;
            }

            Ref<Texture> texture = CreateRef<Texture>();
            texture->SetType(type);
            texture->Load(path, flip, alpha);

            if (!texture)
            {
                LOG_ERROR("Cannot add texture %s because it failed to load!", name);
                return;
            }

            s_textures[name] = texture;
        }

        void AssetManager::AddShader(const char* name, const char* vertexPath, const char* fragmentPath)
        {
            if (s_shaders.find(name) != s_shaders.end())
            {
                LOG_ERROR("Cannot add texture %s because it already exists!", name);
                return;
            }

            ShaderSource shaderSource;
            shaderSource.vertex = ReadFile(vertexPath);
            shaderSource.fragment = ReadFile(fragmentPath);

            Ref<Shader> shader = CreateRef<Shader>();
            shader->Load(shaderSource);

            if (!shader)
            {
                LOG_ERROR("Cannot add texture %s because it failed to load!", name);
                return;
            }

            s_shaders[name] = shader;
        }

        void AssetManager::Clean()
        {
            s_textures.clear();
            s_shaders.clear();
        }
    }
}
