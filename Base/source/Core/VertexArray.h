#pragma once
#define ELEMENTS_PER_VERTEX 5 // 3 position, 2 uv
#define VERTEX_POS_OFFSET (void*)(0 * sizeof(float))
#define VERTEX_UV_OFFSET (void*)(3 * sizeof(float))

#include "Core/Base.h"

namespace Maylib
{
    namespace Core
    {
        class VertexArray
        {
        public:
            VertexArray();
            ~VertexArray();

            void Bind();
            void Unbind();
            void LinkAttribs(u8 location, u8 elementCount, void* offset);

        private:
            u32 m_id;
        };
    }
}
