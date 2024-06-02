#include "Graphics/Light.h"
#include "Core/Log.h"

#include <glm/matrix.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
        BaseLight::BaseLight()
        {
            m_ambientIntensity = 1.f;
            m_position = glm::vec3(0.f);
            m_color = glm::vec3(1.f);
        }

        void BaseLight::UpdateUniforms(Shader* shader)
        {
            shader->Bind();
            shader->SetFloat("baseLight.ambientIntensity", m_ambientIntensity);
            shader->SetVec3("baseLight.color", m_color);
            shader->Unbind();
        }

        DirectionalLight::DirectionalLight()
        {
            m_ambientIntensity = 0.1f;
            m_diffuseIntensity = 1.f;
            m_position = glm::vec3(0.f);
            m_color = glm::vec3(1.f);
            m_localDirection = glm::vec3(0.f);
            m_worldDirection = glm::vec3(0.f);
        }

        void DirectionalLight::CalculateLocalDirection(Model& model)
        {
            glm::mat3 modelMatrix = model.GetModelMatrix();
            glm::mat3 worldToLocal = glm::transpose(modelMatrix);

            m_localDirection = worldToLocal * m_worldDirection;
            m_localDirection = glm::normalize(m_localDirection);
        }

        void DirectionalLight::UpdateUniforms(Shader* shader)
        {
            shader->Bind();
            shader->SetFloat("directionalLight.ambientIntensity", m_ambientIntensity);
            shader->SetFloat("directionalLight.diffuseIntensity", m_diffuseIntensity);
            shader->SetVec3("directionalLight.color", m_color);
            shader->SetVec3("directionalLight.direction", m_localDirection);
            shader->Unbind();
        }
    }
}
