#include "Graphics/Model.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Vertex.h"
#include "Graphics/Mesh.h"

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
        Model::Model() {}

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

            std::string strPath = std::string(path);
            m_directory = strPath.substr(0, strPath.find_last_of('/'));

            this->ProcessNode(scene->mRootNode, scene);
        }

        void Model::Draw(Shader& shader)
        {
            for (u32 i = 0; i < m_meshes.size(); i++)
                m_meshes[i].Draw(shader);
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

        Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

            return Mesh(meshData);
        }
    }
}
