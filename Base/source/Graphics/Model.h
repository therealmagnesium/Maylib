#pragma once
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"

#include <assimp/Importer.hpp>
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

            void Load(const char* path);
            void Draw(Shader& shader);

        private:
            void ProcessNode(aiNode* node, const aiScene* scene);
            Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

        private:
            std::vector<Mesh> m_meshes;
            std::string m_directory;
        };
    }
}
