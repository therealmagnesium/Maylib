#pragma once
#include "Core/Base.h"
#include "Core/Buffer.h"
#include "Core/Vertex.h"
#include "Core/VertexArray.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <vector>

using namespace Maylib::Core;

namespace Maylib
{
    namespace Graphics
    {
        struct MeshData
        {
            std::vector<Vertex> vertices;
            std::vector<u32> indices;
            std::vector<Texture*> textures;
        };

        class Mesh
        {
        public:
            Mesh();
            Mesh(const MeshData& data);

            void Create(const MeshData& data);
            void Draw(Shader& shader);

        private:
            MeshData m_data;
            VertexArray m_vertexArray;
            VertexBuffer m_vertexBuffer;
            IndexBuffer m_indexBuffer;
        };
    }
}
