#pragma once

#include "Core/Base.h"

namespace Maylib
{
    namespace Core
    {
        class VertexBuffer
        {
        public:
            VertexBuffer();
            ~VertexBuffer();

            void Bind();
            void Unbind();
            void SetData(float* vertices, u32 numVertices);

        private:
            u32 m_id;
        };

        class IndexBuffer
        {
        public:
            IndexBuffer();
            ~IndexBuffer();

            void Bind();
            void Unbind();
            void SetData(u32* indices, u32 numIndices);

        private:
            u32 m_id;
        };
    }
}