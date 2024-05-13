#include "Core/Input.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include <SDL2/SDL_scancode.h>

namespace Maylib
{
    namespace Core
    {
        bool Input::s_keyTyped = false;
        bool Input::s_keysDown[TOTAL_KEYBOARD_KEYS]{};

        s32 Input::s_mouseX = 0;
        s32 Input::s_mouseY = 0;
        bool Input::s_mouseClicked = false;
        bool Input::s_mouseButtonsDown[MOUSE_BUTTON_COUNT]{};

        bool Input::IsKeyDown(SDL_Scancode key) { return s_keysDown[key]; }
        bool Input::IsKeyTyped(SDL_Scancode key) { return s_keysDown[key] && s_keyTyped; }

        bool Input::IsMouseButtonDown(MouseButton button) { return s_mouseButtonsDown[button]; }
        bool Input::IsMouseClicked(MouseButton button) { return s_mouseButtonsDown[button] && s_mouseClicked; }

        s8 Input::GetAxis(const std::string& axis, bool alt)
        {
            s8 val = 0;

            if (axis == "Horizontal")
            {
                if (!alt)
                    val = IsKeyDown(SDL_SCANCODE_RIGHT) - IsKeyDown(SDL_SCANCODE_LEFT);
                else
                    val = IsKeyDown(SDL_SCANCODE_D) - IsKeyDown(SDL_SCANCODE_A);
            }
            else if (axis == "Vertical")
            {
                if (!alt)
                    val = IsKeyDown(SDL_SCANCODE_DOWN) - IsKeyDown(SDL_SCANCODE_UP);
                else
                    val = IsKeyDown(SDL_SCANCODE_S) - IsKeyDown(SDL_SCANCODE_W);
            }
            else
            {
                LOG_WARN("%s is not a valid input axis", axis.c_str());
            }

            return val;
        }
    }
}
