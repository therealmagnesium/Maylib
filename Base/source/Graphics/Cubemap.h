#pragma once
#define CUBEMAP_TEXTURE_COUNT 6

#include "Core/Base.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include <string>

namespace Maylib
{
    namespace Graphics
    {
        class Cubemap
        {
        public:
            Cubemap();

            void Bind();
            void Unbind();
            void Load(std::string* texturePaths);
            void Draw(Shader* shader);

        private:
            u32 m_id;
            Model m_cube;
            std::string m_texturePaths[CUBEMAP_TEXTURE_COUNT];
        };
    }
}
