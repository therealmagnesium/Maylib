#include "Core/Input.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include <SDL2/SDL_scancode.h>

namespace Maylib
{
    namespace Core
    {
        bool Input::keyTyped = false;
        bool Input::keysDown[300]{0};

        bool Input::IsKeyDown(SDL_Scancode key) { return keysDown[key]; }
        bool Input::IsKeyTyped(SDL_Scancode key) { return keysDown[key] && keyTyped; }

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
