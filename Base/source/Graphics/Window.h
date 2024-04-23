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

            void HandleEvents();

        private:
            bool m_closed = false;
            SDL_Window* m_handle;
        };
    }
}
