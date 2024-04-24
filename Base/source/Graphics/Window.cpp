#include "Graphics/Window.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "UI/Theme.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h>
#include <string>

using namespace Maylib::Core;
using namespace Maylib::UI;

namespace Maylib
{
    namespace Graphics
    {
        Window::Window(u32 width, u32 height, const std::string& title)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

            if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            {
                LOG_FATAL("Failed to init sdl2!\n");
                return;
            }

            u32 flags = SDL_WINDOW_OPENGL;
            m_handle =
                SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

            if (!m_handle)
            {
                LOG_FATAL("Failed to create window!\n");
                return;
            }

            SDL_GLContext glContext = SDL_GL_CreateContext(m_handle);
            SDL_GL_MakeCurrent(m_handle, glContext);
            SDL_GL_SetSwapInterval(1);

            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
            {
                LOG_FATAL("Failed to load glad!\n");
                return;
            }

            LOG_INFO("GPU vendor: %s", glGetString(GL_VENDOR));
            LOG_INFO("GPU renderer: %s", glGetString(GL_RENDERER));
            LOG_INFO("GPU version: %s", glGetString(GL_VERSION));

            ImGui::CreateContext();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            // ImGui::StyleColorsDark();
            SetTheme();

            ImGui_ImplSDL2_InitForOpenGL(m_handle, glContext);
            ImGui_ImplOpenGL3_Init("#version 460");
        }

        Window::~Window()
        {
            SDL_DestroyWindow(m_handle);
            SDL_Quit();
        }

        void Window::Create(u32 width, u32 height, const std::string& title)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

            if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            {
                LOG_FATAL("Failed to init sdl2!\n");
                return;
            }

            u32 flags = SDL_WINDOW_OPENGL;
            m_handle =
                SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

            if (!m_handle)
            {
                LOG_FATAL("Failed to create window!\n");
                return;
            }

            SDL_GLContext glContext = SDL_GL_CreateContext(m_handle);
            SDL_GL_MakeCurrent(m_handle, glContext);
            SDL_GL_SetSwapInterval(1);

            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
            {
                LOG_FATAL("Failed to load glad!\n");
                return;
            }

            LOG_INFO("GPU vendor: %s", glGetString(GL_VENDOR));
            LOG_INFO("GPU renderer: %s", glGetString(GL_RENDERER));
            LOG_INFO("GPU version: %s", glGetString(GL_VERSION));

            ImGui::CreateContext();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            // ImGui::StyleColorsDark();
            SetTheme();

            ImGui_ImplSDL2_InitForOpenGL(m_handle, glContext);
            ImGui_ImplOpenGL3_Init("#version 460");
        }

        void Window::HandleEvents()
        {
            Input::keyTyped = false;

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);

                switch (event.type)
                {
                    case SDL_QUIT:
                    {
                        m_closed = true;
                        break;
                    }

                    case SDL_KEYDOWN:
                    {
                        bool keyCheck = Input::keysDown[event.key.keysym.scancode];
                        Input::keyTyped = (keyCheck) ? false : true;
                        Input::keysDown[event.key.keysym.scancode] = true;

                        break;
                    }

                    case SDL_KEYUP:
                    {
                        Input::keyTyped = false;
                        Input::keysDown[event.key.keysym.scancode] = false;

                        break;
                    }

                    default:
                        break;
                }
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        }

        void Window::Clear(float r, float g, float b)
        {
            ImGui::Render();

            glClearColor(r, g, b, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Window::Display()
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(m_handle);
        }
    }
}
