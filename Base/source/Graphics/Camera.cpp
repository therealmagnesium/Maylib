#include "Graphics/Camera.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Graphics/Shader.h"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace Maylib::Core;

namespace Maylib
{
    namespace Graphics
    {
        static Application* app;
        static float aspect;

        Camera::Camera()
        {
            app = Application::Get();
            AppInfo& appInfo = app->GetInfo();
            aspect = (float)appInfo.screenWidth / appInfo.screenHeight;

            m_position = glm::vec3(0.f, 0.f, 2.f);
            m_up = glm::vec3(0.f, 1.f, 0.f);
            m_orientation = glm::vec3(0.f, 0.f, -1.f);

            m_view = glm::mat4(1.f);
            m_projection = glm::mat4(1.f);
        }

        void Camera::CalculateMatrix(Shader& shader)
        {
            shader.Bind();

            m_view = glm::lookAt(m_position, m_position + m_orientation, m_up);
            m_projection = glm::perspective(glm::radians(45.f), aspect, 0.1f, 1000.f);

            shader.SetMat4("camMatrix", m_projection * m_view, true);

            shader.Unbind();
        }

        void Camera::Update()
        {
            glm::vec3 right = glm::cross(m_orientation, m_up);

            if (Input::IsKeyDown(SDL_SCANCODE_LEFT))
                m_position += m_moveSpeed * -right;

            if (Input::IsKeyDown(SDL_SCANCODE_RIGHT))
                m_position += m_moveSpeed * right;

            if (Input::IsKeyDown(SDL_SCANCODE_UP) && !Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * m_up;

            if (Input::IsKeyDown(SDL_SCANCODE_DOWN) && !Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * -m_up;

            if (Input::IsKeyDown(SDL_SCANCODE_UP) && Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * m_orientation;

            if (Input::IsKeyDown(SDL_SCANCODE_DOWN) && Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * -m_orientation;
        }
    }
}
