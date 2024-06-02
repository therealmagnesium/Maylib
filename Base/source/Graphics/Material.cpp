#include "Graphics/Material.h"
#include "Core/Log.h"

#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
        Material::Material()
        {
            m_ambientColor = glm::vec3(1.f);
            m_diffuseColor = glm::vec3(1.f);
            m_specularColor = glm::vec3(1.f);

            m_textureMaps[TEXTURE_MAP_DIFFUSE] = NULL;
            m_textureMaps[TEXTURE_MAP_SPECULAR] = NULL;
        }

        void Material::UpdateUniforms(Shader* shader)
        {
            shader->Bind();
            shader->SetVec3("material.ambientColor", m_ambientColor);
            shader->SetVec3("material.diffuseColor", m_diffuseColor);
            shader->SetVec3("material.specularColor", m_specularColor);
            shader->Unbind();
        }

        void Material::SetTexture(TextureMapType type, Texture* texture)
        {
            if (!texture)
            {
                LOG_ERROR("Material::SetTexture() - Cannot set diffuse texture because it's null");
                return;
            }

            m_textureMaps[type] = texture;
        }

    }
}
