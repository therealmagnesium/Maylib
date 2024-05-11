#pragma once
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <string>
#include <vector>

namespace Maylib
{
    namespace Graphics
    {
        enum TextureMapType
        {
            TEXTURE_MAP_DIFFUSE = 0,
            TEXTURE_MAP_SPECULAR,
            TEXTURE_MAP_COUNT,
        };

        class Model
        {
        public:
            Model();

            void Load(const char* path);
            void Draw(Shader& shader);
            void SetTexture(TextureMapType type, Texture* texture);

        private:
            void ProcessNode(aiNode* node, const aiScene* scene);
            Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

        private:
            std::string m_directory;
            std::vector<Mesh*> m_meshes;

            Texture* m_textureMaps[TEXTURE_MAP_COUNT]{};
            bool m_loadedTextureMaps[TEXTURE_MAP_COUNT]{};
        };
    }
}
