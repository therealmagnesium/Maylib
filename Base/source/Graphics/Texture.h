#pragma once
#include "Core/Base.h"
#include <string>

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

            inline std::string& GetType() { return m_type; }
            inline void SetType(const char* type) { m_type = type; }

            void Bind(u8 slot = 0);
            void Unbind();
            void Load(const char* path, bool alpha = false);

        private:
            u32 m_id;
            std::string m_type;
            TextureSpecification m_spec;
        };
    }
}
