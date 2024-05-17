#include "Graphics/Model.h"
#include "Core/AssetManager.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Vertex.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"

#include <cstring>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Maylib
{
    namespace Graphics
    {
        Model::Model()
        {
            m_modelMatrix = glm::mat4(1.f);
            m_transform.position = glm::vec3(0.f);
            m_transform.rotation = glm::vec3(0.f);
            m_transform.scale = glm::vec3(1.f);

            this->SetupMatrix();
        }

        void Model::Load(const char* path)
        {
            Assimp::Importer importer;
            u32 flags = aiProcess_Triangulate | aiProcess_FlipUVs;
            const aiScene* scene = importer.ReadFile(path, flags);

            if (!scene || !scene->mRootNode)
            {
                LOG_WARN("Failed to load model %s!", path);
                return;
            }

            this->ProcessNode(scene->mRootNode, scene);
            this->SetupMatrix();
        }

        void Model::Draw(Shader& shader)
        {
            shader.Bind();
            shader.SetMat4("modelMatrix", m_modelMatrix);
            shader.Unbind();

            for (u32 i = 0; i < m_meshes.size(); i++)
                m_meshes[i]->Draw(shader);
        }

        void Model::SetTexture(TextureMapType type, Texture* texture)
        {
            if (!texture)
            {
                LOG_ERROR("Model::SetDiffuseTexture() - Cannot set diffuse texture because it's null");
                return;
            }

            m_textureMaps[type] = texture;
            m_loadedTextureMaps[type] = true;
        }

        void Model::ProcessNode(aiNode* node, const aiScene* scene)
        {
            for (u32 i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                m_meshes.push_back(this->ProcessMesh(mesh, scene));
            }

            for (u32 i = 0; i < node->mNumChildren; i++)
                this->ProcessNode(node->mChildren[i], scene);
        }

        Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
        {
            MeshData meshData;

            for (u32 i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex;
                glm::vec3 vec;

                vec.x = mesh->mVertices[i].x;
                vec.y = mesh->mVertices[i].y;
                vec.z = mesh->mVertices[i].z;

                vertex.position = vec;

                if (mesh->HasNormals())
                {
                    vec.x = mesh->mNormals[i].x;
                    vec.y = mesh->mNormals[i].y;
                    vec.z = mesh->mNormals[i].z;
                    vertex.normal = vec;
                }

                if (mesh->mTextureCoords[0])
                {
                    glm::vec2 vec2;
                    vec2.x = mesh->mTextureCoords[0][i].x;
                    vec2.y = mesh->mTextureCoords[0][i].y;
                    vertex.texCoords = vec2;
                }
                else
                    vertex.texCoords = glm::vec2(0.f);

                meshData.vertices.push_back(vertex);
            }

            for (u32 i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];

                for (u32 j = 0; j < face.mNumIndices; j++)
                    meshData.indices.push_back(face.mIndices[j]);
            }

            for (u32 i = 0; i < TEXTURE_MAP_COUNT; i++)
            {
                if (m_loadedTextureMaps[i])
                    meshData.textures.push_back(m_textureMaps[i]);
            }

            return new Mesh(meshData);
        }

        void Model::SetupMatrix()
        {
            m_modelMatrix = glm::translate(m_modelMatrix, m_transform.position);
            m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.rotation.x), glm::vec3(1.f, 0.f, 0.f));
            m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.rotation.y), glm::vec3(0.f, 1.f, 0.f));
            m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.rotation.z), glm::vec3(0.f, 0.f, 1.f));
            m_modelMatrix = glm::scale(m_modelMatrix, m_transform.scale);
        }

        void Model::SetPosition(float x, float y, float z) { m_transform.position = glm::vec3(x, y, z); }
        void Model::SetRotation(float x, float y, float z) { m_transform.rotation = glm::vec3(x, y, z); }
        void Model::SetScale(float x, float y, float z) { m_transform.scale = glm::vec3(x, y, z); }
    }

}
