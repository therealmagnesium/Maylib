#pragma once
#include "Core/Math.h"
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
        class Model
        {
        public:
            Model();

            inline glm::vec3& GetPosition() { return m_transform.position; }
            inline glm::vec3& GetRotation() { return m_transform.rotation; }
            inline glm::vec3& GetScale() { return m_transform.scale; }

            void SetPosition(float x, float y, float z);
            void SetRotation(float x, float y, float z);
            void SetScale(float x, float y, float z);

            void Load(const char* path);
            void Draw(Shader* shader, bool skybox = false);
            void SetTexture(TextureMapType type, Texture* texture);

        private:
            void SetupMatrix();
            void ProcessNode(aiNode* node, const aiScene* scene);
            Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

        private:
            Transform m_transform;
            glm::mat4 m_modelMatrix;

            std::vector<Mesh*> m_meshes;
            Texture* m_textureMaps[TEXTURE_MAP_COUNT]{};
            bool m_loadedTextureMaps[TEXTURE_MAP_COUNT]{};
        };
    }
}
