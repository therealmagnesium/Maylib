#pragma once
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
        struct LightAttenuation
        {
            float constant = 1.f;
            float linear = 0.2f;
            float exponent = 0.0f;
        };

        class BaseLight
        {
        public:
            BaseLight();

            inline glm::vec3& GetPosition() { return m_position; }
            inline glm::vec3& GetColor() { return m_color; }

            inline void SetPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }

            void UpdateUniforms(Shader* shader);

        private:
            float m_ambientIntensity;
            glm::vec3 m_position;
            glm::vec3 m_color;
        };

        class DirectionalLight
        {
        public:
            DirectionalLight();

            inline glm::vec3& GetPosition() { return m_position; }
            inline glm::vec3& GetColor() { return m_color; }

            inline void SetPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }
            inline void SetWorldDirection(float x, float y, float z) { m_worldDirection = glm::vec3(x, y, z); }

            void CalculateLocalDirection(Model& model);
            void UpdateUniforms(Shader* shader);

        private:
            float m_ambientIntensity;
            float m_diffuseIntensity;

            glm::vec3 m_position;
            glm::vec3 m_color;
            glm::vec3 m_localDirection;
            glm::vec3 m_worldDirection;
        };

        class PointLight
        {
        public:
            PointLight();

            inline glm::vec3& GetPosition() { return m_worldPosition; }
            inline glm::vec3& GetColor() { return m_color; }

            inline void SetPosition(float x, float y, float z) { m_worldPosition = glm::vec3(x, y, z); }
            inline void SetColor(float r, float g, float b) { m_color = glm::vec3(r, g, b); }

            void CalculateLocalPosition(Model& model);
            void UpdateUniforms(Shader* shader);

        private:
            s8 m_id = -1;

            float m_ambientIntensity;
            float m_diffuseIntensity;

            glm::vec3 m_color;
            glm::vec3 m_worldPosition;
            glm::vec3 m_localPosition;

            LightAttenuation m_attenuation;

        private:
            static s8 s_totalPointLights;
        };
    }
}
