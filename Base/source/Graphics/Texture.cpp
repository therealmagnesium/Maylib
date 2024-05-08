#include "Graphics/Texture.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Maylib
{
    namespace Graphics
    {
        Texture::Texture() { glGenTextures(1, &m_id); }
        Texture::~Texture() { glDeleteTextures(1, &m_id); }

        void Texture::Bind(u8 slot)
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_id);
        }

        void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

        void Texture::Load(const char* path, bool alpha)
        {
            this->Bind();

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_set_flip_vertically_on_load(true);
            u8* data = stbi_load(path, &m_spec.width, &m_spec.height, &m_spec.channelCount, 0);
            if (!data)
                LOG_WARN("Failed to load texture %s!", path);

            if (!alpha)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_spec.width, m_spec.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_spec.width, m_spec.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }

            stbi_image_free(data);
            this->Unbind();
        }
    }
}
