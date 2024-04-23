#pragma once

#include <Core/Base.h>

#include <SDL2/SDL_video.h>
#include <string>

namespace Maylib
{
    namespace Graphics
    {
        class Window
        {
        public:
            Window(u32 width, u32 height, const std::string& title);
            ~Window();

            inline bool ShouldClose() { return m_closed; }
            inline void Close() { m_closed = true; }

            void HandleEvents();
            void Clear(float r, float g, float b);
            void Display();

        private:
            bool m_closed = false;
            SDL_Window* m_handle;
        };
    }
}
