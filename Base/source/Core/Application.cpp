#include "Core/Application.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"
#include "Core/Time.h"
#include <SDL2/SDL_timer.h>
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
                u64 start = SDL_GetPerformanceCounter();
                m_running = !m_window.ShouldClose();

                m_window.HandleEvents();
                this->OnUpdate();

                if (m_debugMode)
                    this->OnUIRender();

                m_window.Clear(clearRedChannel, clearGreenChannel, clearBlueChannel);
                this->OnRender();
                m_window.Display();

                u64 end = SDL_GetPerformanceCounter();

                float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
                Time::s_deltaTime = elapsed;
                /*
                                if (1000.f / Time::s_targetFPS > end - start)
                                    SDL_Delay(floor((1000.f / Time::s_targetFPS) - (Time::s_deltaTime * 1000.f)));*/
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
