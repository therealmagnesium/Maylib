#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"
#include "Core/Base.h"
#include "Core/Buffer.h"
#include "Core/Log.h"
#include "Core/Vertex.h"
#include "Core/VertexArray.h"

#include <string>
#include <vector>

#include <glad/glad.h>

using namespace Maylib::Core;

namespace Maylib
{
    namespace Graphics
    {
        Mesh::Mesh() {}
        Mesh::Mesh(const MeshData& data) { this->Create(data); }

        void Mesh::Create(const MeshData& data)
        {
            m_data = data;

            m_vertexArray.Bind();

            m_vertexBuffer.Bind();
            m_vertexBuffer.SetData(m_data.vertices.data(), m_data.vertices.size());

            m_indexBuffer.Bind();
            m_indexBuffer.SetData(m_data.indices.data(), m_data.indices.size());

            m_vertexArray.LinkAttribs(0, 3, VERTEX_POS_OFFSET);
            m_vertexArray.LinkAttribs(1, 3, VERTEX_NORMAL_OFFSET);
            m_vertexArray.LinkAttribs(2, 2, VERTEX_UV_OFFSET);

            m_vertexArray.Unbind();
            m_vertexBuffer.Unbind();
            m_indexBuffer.Unbind();
        }

        void Mesh::Draw(Shader& shader)
        {
            shader.Bind();

            u32 numDiffuse = 1;
            u32 numSpecular = 1;

            for (u32 i = 0; i < m_data.textures.size(); i++)
            {
                std::string number;
                std::string name = m_data.textures[i].GetType();

                if (name == "diffuse")
                    number = std::to_string(numDiffuse++);
                else if (name == "specular")
                    number = std::to_string(numSpecular++);
                else
                    LOG_WARN("Mesh::Draw(Shader&) - Unknown texture type %s", name.c_str());

                shader.SetInt(name + number, i);
                m_data.textures[i].Bind(i);
            }

            m_vertexArray.Bind();
            glDrawElements(GL_TRIANGLES, m_data.indices.size(), GL_UNSIGNED_INT, 0);
            m_vertexArray.Unbind();

            shader.Unbind();
        }
    }
}
