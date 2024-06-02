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

            inline float GetYaw() { return m_yaw; }
            inline float GetPitch() { return m_pitch; }
            inline float GetRoll() { return m_roll; }
            inline glm::vec3& GetPosition() { return m_position; }
            inline glm::vec3& GetRotation() { return m_rotation; }

            inline void SetPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }

            void Update();
            void CalculateMatrix(Shader* shader, glm::mat4 transformMatrix, bool convertView = false);

        private:
            void HandleKeyInputs();
            void HandleMouseInputs();

        private:
            float m_moveSpeed = 5.f;
            float m_sensitivity = 5.f;

            float m_yaw = -90.f;
            float m_pitch = 0.f;
            float m_roll = 0.f;

            glm::vec3 m_position;
            glm::vec3 m_rotation;
            glm::vec3 m_up;
            glm::vec3 m_orientation;

            glm::mat4 m_view;
            glm::mat4 m_projection;
        };
    }
}
