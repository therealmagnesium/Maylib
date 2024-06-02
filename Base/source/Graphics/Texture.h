#pragma once
#include "Core/Base.h"
#include <string>

namespace Maylib
{
    namespace Graphics
    {
        enum TextureMapType
        {
            TEXTURE_MAP_DIFFUSE = 0,
            TEXTURE_MAP_SPECULAR,
            TEXTURE_MAP_COUNT,
        };

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

            inline TextureMapType GetType() { return m_type; }
            inline void SetType(TextureMapType type) { m_type = type; }

            void Bind(u8 slot = 0);
            void Unbind();
            void Load(const char* path, bool flip = false);

        private:
            u32 m_id;
            TextureMapType m_type;
            TextureSpecification m_spec;
        };
    }
}
