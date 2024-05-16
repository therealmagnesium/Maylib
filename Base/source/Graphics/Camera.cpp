#include "Graphics/Camera.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Graphics/Shader.h"

#include <SDL2/SDL_mouse.h>
#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
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

            m_position = glm::vec3(0.f, 0.f, 5.f);
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
            if (!app->DebugEnabled())
            {
                this->HandleKeyInputs();
                this->HandleMouseInputs();
            }
        }

        void Camera::HandleKeyInputs()
        {
            glm::vec3 right = glm::cross(m_orientation, m_up);

            if (Input::IsKeyDown(SDL_SCANCODE_A))
                m_position += m_moveSpeed * -right;

            if (Input::IsKeyDown(SDL_SCANCODE_D))
                m_position += m_moveSpeed * right;

            if (Input::IsKeyDown(SDL_SCANCODE_W) && !Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * m_up;

            if (Input::IsKeyDown(SDL_SCANCODE_S) && !Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * -m_up;

            if (Input::IsKeyDown(SDL_SCANCODE_W) && Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * m_orientation;

            if (Input::IsKeyDown(SDL_SCANCODE_S) && Input::IsKeyDown(SDL_SCANCODE_LSHIFT))
                m_position += m_moveSpeed * -m_orientation;
        }

        void Camera::HandleMouseInputs()
        {
            static s32 lastX = 0;
            static s32 lastY = 0;
            static bool firstClick = true;

            if (Input::IsMouseButtonDown(MOUSE_LEFT))
            {
                SDL_ShowCursor(false);

                if (firstClick)
                {
                    lastX = Input::GetMouseX();
                    lastY = Input::GetMouseY();
                    firstClick = false;
                }

                float xOffset = Input::GetMouseX() - lastX;
                float yOffset = Input::GetMouseY() - lastY;

                lastX = Input::GetMouseX();
                lastY = Input::GetMouseY();

                xOffset *= m_sensitivity;
                yOffset *= m_sensitivity;

                m_yaw += xOffset;
                m_pitch += yOffset;

                if (m_pitch > 80.f)
                    m_pitch = 80.f;
                if (m_pitch < -80.f)
                    m_pitch = -80.f;

                m_orientation.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
                m_orientation.y = sin(glm::radians(-m_pitch));
                m_orientation.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

                m_orientation = glm::normalize(m_orientation);
            }
            else
            {
                SDL_ShowCursor(true);
                firstClick = true;
            }
        }
    }
}
