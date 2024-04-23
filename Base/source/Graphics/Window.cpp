#include "Graphics/Window.h"

#include <SDL2/SDL_events.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <cassert>
#include <cstdio>
#include <string>

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
                printf("Failed to init sdl2!\n");
                return;
            }

            u32 flags = 0;
            m_handle =
                SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

            if (!m_handle)
            {
                printf("Failed to create window!\n");
                return;
            }

            SDL_GL_CreateContext(m_handle);
            gladLoadGL();
        }

        Window::~Window()
        {
            SDL_DestroyWindow(m_handle);
            SDL_Quit();
        }

        void Window::HandleEvents()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                    {
                        m_closed = true;
                        break;
                    }

                    default:
                        break;
                }
            }
        }
    }
}
