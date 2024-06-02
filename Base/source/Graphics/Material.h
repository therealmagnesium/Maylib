#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
        class Material
        {
        public:
            Material();

            inline Texture* GetTexture(TextureMapType type) { return m_textureMaps[type]; }

            inline void SetAmbientColor(float r, float g, float b) { m_ambientColor = glm::vec3(r, g, b); }
            inline void SetDiffuseColor(float r, float g, float b) { m_diffuseColor = glm::vec3(r, g, b); }
            inline void SetSpecularColor(float r, float g, float b) { m_specularColor = glm::vec3(r, g, b); }

            void UpdateUniforms(Shader* shader);
            void SetTexture(TextureMapType type, Texture* texture);

        private:
            glm::vec3 m_ambientColor;
            glm::vec3 m_diffuseColor;
            glm::vec3 m_specularColor;

            Texture* m_textureMaps[TEXTURE_MAP_COUNT]{};
        };
    }
}
