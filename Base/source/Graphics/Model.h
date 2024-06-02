#pragma once
#include "Core/Math.h"
#include "Graphics/Material.h"
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
            ~Model();

            inline glm::vec3& GetPosition() { return m_transform.position; }
            inline glm::vec3& GetRotation() { return m_transform.rotation; }
            inline glm::vec3& GetScale() { return m_transform.scale; }
            inline glm::mat4& GetModelMatrix() { return m_modelMatrix; }

            void SetPosition(float x, float y, float z);
            void SetRotation(float x, float y, float z);
            void SetScale(float x, float y, float z);

            void Load(const char* path);
            void Draw(Shader* shader, bool skybox = false);

        private:
            void SetupMatrix();
            void ProcessNode(aiNode* node, const aiScene* scene);
            Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

        private:
            Transform m_transform;
            glm::mat4 m_modelMatrix;

            std::vector<Mesh*> m_meshes;
            std::vector<Material*> m_materials;
        };
    }
}
