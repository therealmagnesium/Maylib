#include "Core/Application.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"
#include <glad/glad.h>

namespace Maylib
{
    namespace Core
    {
        Application* Application::s_instance;

        static float clearRedChannel;
        static float clearGreenChannel;
        static float clearBlueChannel;

        Application::Application(const AppInfo& info)
        {
            s_instance = this;
            m_info = info;

            m_window.Create(info.screenWidth, info.screenHeight, info.name);
        }

        Application::~Application() {}

        void Application::Run()
        {
            while (m_running)
            {
                m_running = !m_window.ShouldClose();

                m_window.HandleEvents();
                this->OnUpdate();

                if (m_debugMode)
                    this->OnUIRender();

                m_window.Clear(clearRedChannel, clearGreenChannel, clearBlueChannel);
                this->OnRender();
                m_window.Display();
            }
        }

        void Application::Quit()
        {
            m_running = false;
            m_window.Close();
        }

        void Application::SetClearColor(float r, float g, float b)
        {
            clearRedChannel = r;
            clearGreenChannel = g;
            clearBlueChannel = b;
        }
    }
}
