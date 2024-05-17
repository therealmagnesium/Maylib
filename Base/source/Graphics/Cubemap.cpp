#include "Graphics/Cubemap.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Maylib
{
    namespace Graphics
    {
        Cubemap::Cubemap() { glGenTextures(1, &m_id); }

        void Cubemap::Bind() { glBindTexture(GL_TEXTURE_CUBE_MAP, m_id); }
        void Cubemap::Unbind() { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }

        void Cubemap::Load(std::string* texturePaths)
        {
            s32 width;
            s32 height;
            s32 numChannels;

            this->Bind();

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            for (u8 i = 0; i < CUBEMAP_TEXTURE_COUNT; i++)
            {
                m_texturePaths[i] = texturePaths[i];
                stbi_set_flip_vertically_on_load(false);
                u8* data = stbi_load(m_texturePaths[i].c_str(), &width, &height, &numChannels, 0);
                if (!data)
                {
                    LOG_WARN("Failed to load cubemap texture %s!", m_texturePaths[i].c_str());
                    stbi_image_free(data);
                    return;
                }

                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                             data);
                stbi_image_free(data);
            }

            m_cube.Load("assets/models/skybox.obj");

            this->Unbind();
        }

        void Cubemap::Draw(Shader& shader)
        {
            glDepthMask(false);
            shader.Bind();
            shader.SetInt("skybox", 0, false);
            this->Bind();
            shader.Unbind();

            m_cube.Draw(shader);
            glDepthMask(true);
        }
    }
}
