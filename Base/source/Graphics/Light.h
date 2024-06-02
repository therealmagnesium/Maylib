#pragma once
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
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
    }
}
