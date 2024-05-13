#include "Graphics/Window.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "UI/Theme.h"

#include <SDL2/SDL_mouse.h>
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
        Window::Window(u32 width, u32 height, const std::string& title) { this->Create(width, height, title); }

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

            u32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
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

            glEnable(GL_DEPTH_TEST);

            ImGui::CreateContext();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            SetTheme();

            ImGui_ImplSDL2_InitForOpenGL(m_handle, glContext);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        void Window::HandleEvents()
        {
            Input::s_keyTyped = false;
            Input::s_mouseClicked = false;

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                this->HandleEventTypes(event);
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        }

        void Window::Clear(float r, float g, float b)
        {
            ImGui::Render();

            glClearColor(r, g, b, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::Display()
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(m_handle);
        }

        void Window::HandleEventTypes(const SDL_Event& event)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    m_closed = true;
                    break;
                }

                case SDL_KEYDOWN:
                {
                    bool keyCheck = Input::s_keysDown[event.key.keysym.scancode];
                    Input::s_keyTyped = (keyCheck) ? false : true;
                    Input::s_keysDown[event.key.keysym.scancode] = true;

                    break;
                }

                case SDL_KEYUP:
                {
                    Input::s_keyTyped = false;
                    Input::s_keysDown[event.key.keysym.scancode] = false;

                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    SDL_GetMouseState(&Input::s_mouseX, &Input::s_mouseY);
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {
                    bool buttonCheck = Input::s_mouseButtonsDown[event.button.button - 1];
                    Input::s_mouseClicked = (buttonCheck) ? false : true;
                    Input::s_mouseButtonsDown[event.button.button - 1] = true;
                    break;
                }

                case SDL_MOUSEBUTTONUP:
                {
                    Input::s_mouseClicked = false;
                    Input::s_mouseButtonsDown[event.button.button - 1] = false;
                    break;
                }

                case SDL_WINDOWEVENT:
                {
                    this->HandleWindowEvents(event);
                    break;
                }

                default:
                    break;
            }
        }

        void Window::HandleWindowEvents(const SDL_Event& event)
        {
            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    s32 newWidth = event.window.data1;
                    s32 newHeight = event.window.data2;

                    AppInfo& appInfo = Application::Get()->GetInfo();
                    appInfo.screenWidth = newWidth;
                    appInfo.screenHeight = newHeight;

                    LOG_INFO("Window resized to %dx%d", newWidth, newHeight);
                    glViewport(0, 0, newWidth, newHeight);
                    break;
                }

                default:
                    break;
            }
        }
    }
}
