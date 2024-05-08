#pragma once
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
            void LinkAttribs(u8 location, u8 elementCount, u64 offset);

        private:
            u32 m_id;
        };
    }
}
