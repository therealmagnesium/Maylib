#include "Core/Application.h"

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
            while (!m_window.ShouldClose())
            {
                m_window.HandleEvents();
                this->OnUpdate();
                this->OnUIRender();

                m_window.Clear(0.08f, 0.07f, 0.15f);
                m_window.Display();
            }
        }

        void Application::Quit() { m_window.Close(); }

    }
}
