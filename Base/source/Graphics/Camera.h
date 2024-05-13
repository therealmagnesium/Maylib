#pragma once
#include "Graphics/Shader.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Graphics
    {
        class Camera
        {
        public:
            Camera();

            void Update();
            void CalculateMatrix(Shader& shader);

        private:
            void HandleKeyInputs();
            void HandleMouseInputs();

        private:
            float m_moveSpeed = 0.08f;
            float m_sensitivity = 0.1f;

            float m_pitch = 0.f;
            float m_yaw = -90.f;
            float m_roll = 0.f;

            glm::vec3 m_position;
            glm::vec3 m_up;
            glm::vec3 m_orientation;

            glm::mat4 m_view;
            glm::mat4 m_projection;
        };
    }
}
