#include "Core/Buffer.h"
#include "Core/Vertex.h"
#include <glad/glad.h>

namespace Maylib
{
    namespace Core
    {
        VertexBuffer::VertexBuffer() { glGenBuffers(1, &m_id); }
        VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_id); }

        void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
        void VertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

        void VertexBuffer::SetData(Vertex* vertices, u32 numVertices)
        {
            glBufferData(GL_ARRAY_BUFFER, numVertices * ELEMENTS_PER_VERTEX * sizeof(float), vertices, GL_STATIC_DRAW);
        }

        IndexBuffer::IndexBuffer() { glGenBuffers(1, &m_id); }
        IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_id); }

        void IndexBuffer::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
        void IndexBuffer::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

        void IndexBuffer::SetData(u32* indices, u32 numIndices)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(u32), indices, GL_STATIC_DRAW);
        }
    }
}
