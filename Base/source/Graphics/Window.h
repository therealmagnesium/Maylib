#pragma once

#include <Core/Base.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <string>

namespace Maylib
{
    namespace Graphics
    {
        class Window
        {
        public:
            Window() = default;
            Window(u32 width, u32 height, const std::string& title);
            ~Window();

            inline bool ShouldClose() { return m_closed; }
            inline void Close() { m_closed = true; }

            void Create(u32 width, u32 height, const std::string& title);
            void Clear(float r, float g, float b);
            void Display();
            void HandleEvents();

        private:
            void HandleEventTypes(const SDL_Event& event);
            void HandleWindowEvents(const SDL_Event& event);

        private:
            bool m_closed = false;
            SDL_Window* m_handle;
        };
    }
}
