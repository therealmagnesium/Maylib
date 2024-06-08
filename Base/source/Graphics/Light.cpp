#include "Graphics/Light.h"
#include "Core/Log.h"

#include <glm/matrix.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/vector_float3.hpp>
#include <string>

namespace Maylib
{
    namespace Graphics
    {
        s8 PointLight::s_totalPointLights = 0;

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
            shader->SetFloat("directionalLight.base.ambientIntensity", m_ambientIntensity);
            shader->SetFloat("directionalLight.base.diffuseIntensity", m_diffuseIntensity);
            shader->SetVec3("directionalLight.base.color", m_color);
            shader->SetVec3("directionalLight.direction", m_localDirection);
            shader->Unbind();
        }

        PointLight::PointLight()
        {
            s_totalPointLights++;
            m_id = s_totalPointLights - 1;

            m_ambientIntensity = 0.1f;
            m_diffuseIntensity = 1.f;
            m_color = glm::vec3(1.f, 1.f, 1.f);
            m_worldPosition = glm::vec3(0.f, 0.f, 0.f);
            m_localPosition = glm::vec3(0.f, 0.f, 0.f);
        }

        void PointLight::CalculateLocalPosition(Model& model)
        {
            glm::mat4 modelMatrix = model.GetModelMatrix();
            glm::mat4 worldToLocalTransform = glm::transpose(modelMatrix);
            glm::vec4 worldPosition4f = glm::vec4(m_worldPosition, 1.f);
            glm::vec4 localPosition4f = worldToLocalTransform * worldPosition4f;
            m_localPosition = glm::vec3(localPosition4f);
        }

        void PointLight::UpdateUniforms(Shader* shader)
        {
            std::string id = std::to_string(m_id);

            shader->Bind();

            shader->SetInt("numPointLights", s_totalPointLights);

            shader->SetVec3("pointLights[" + id + "].position", m_localPosition);

            shader->SetFloat("pointLights[" + id + "].base.ambientIntensity", m_ambientIntensity);
            shader->SetFloat("pointLights[" + id + "].base.diffuseIntensity", m_diffuseIntensity);
            shader->SetVec3("pointLights[" + id + "].base.color", m_color);

            shader->SetFloat("pointLights[" + id + "].attenuation.constant", m_attenuation.constant);
            shader->SetFloat("pointLights[" + id + "].attenuation.linear", m_attenuation.linear);
            shader->SetFloat("pointLights[" + id + "].attenuation.exponent", m_attenuation.exponent);

            shader->Unbind();
        }
    }
}
