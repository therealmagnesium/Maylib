#pragma once
#include "Core/Base.h"

namespace Maylib
{
    namespace Graphics
    {
        struct TextureSpecification
        {
            s32 width;
            s32 height;
            s32 channelCount;
        };

        class Texture
        {
        public:
            Texture();
            ~Texture();

            void Bind();
            void Unbind();
            void Load(const char* path);

        private:
            u32 m_id;
            TextureSpecification m_spec;
        };
    }
}
