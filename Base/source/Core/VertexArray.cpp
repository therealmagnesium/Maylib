#include "Core/VertexArray.h"
#include <glad/glad.h>

namespace Maylib
{
    namespace Core
    {
        VertexArray::VertexArray() { glGenVertexArrays(1, &m_id); }
        VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

        void VertexArray::Bind() { glBindVertexArray(m_id); }
        void VertexArray::Unbind() { glBindVertexArray(0); }

        void VertexArray::LinkAttribs(u8 location, u8 elementCount, void* offset)
        {
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(location, elementCount, GL_FLOAT, false, ELEMENTS_PER_VERTEX * sizeof(float), offset);
        }
    }
}
