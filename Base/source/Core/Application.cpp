#include "Core/Application.h"
#include "Core/Log.h"

namespace Maylib
{
    namespace Core
    {
        Application* Application::s_instance;

        Application::Application(const AppInfo& info)
        {
            s_instance = this;
            m_window.Create(info.screenWidth, info.screenHeight, info.name);
        }

        Application::~Application() { this->Quit(); }

        void Application::Run()
        {
            while (m_running)
            {
                m_running = !m_window.ShouldClose();

                m_window.HandleEvents();
                this->OnUpdate();
                this->OnUIRender();

                m_window.Clear(0.28f, 0.28f, 0.28f);
                m_window.Display();
            }
        }

        void Application::Quit()
        {
            m_running = false;
            m_window.Close();
        }

    }
}
