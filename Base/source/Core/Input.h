#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"

#include <SDL2/SDL_scancode.h>
#include <string>

#define TOTAL_KEYBOARD_KEYS 300

namespace Maylib
{
    namespace Core
    {
        enum MouseButton
        {
            MOUSE_LEFT = 0,
            MOUSE_MIDDLE,
            MOUSE_RIGHT,
            MOUSE_BUTTON_COUNT
        };

        class Input
        {
        public:
            static bool IsKeyDown(SDL_Scancode key);
            static bool IsKeyTyped(SDL_Scancode key);
            static s8 GetAxis(const std::string& axis, bool alt = false);

            static inline s32 GetMouseX() { return s_mouseX; };
            static inline s32 GetMouseY() { return s_mouseY; };
            static bool IsMouseClicked(MouseButton button);
            static bool IsMouseButtonDown(MouseButton button);

        private:
            static bool s_keyTyped;
            static bool s_keysDown[TOTAL_KEYBOARD_KEYS];

            static s32 s_mouseX;
            static s32 s_mouseY;
            static bool s_mouseClicked;
            static bool s_mouseButtonsDown[MOUSE_BUTTON_COUNT];

        private:
            friend class Graphics::Window;
        };

    }
}
