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
            float m_moveSpeed = 0.08f;

            glm::vec3 m_position;
            glm::vec3 m_up;
            glm::vec3 m_orientation;

            glm::mat4 m_view;
            glm::mat4 m_projection;
        };
    }
}
