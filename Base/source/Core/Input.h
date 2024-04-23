#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"

#include <SDL2/SDL_scancode.h>
#include <string>

namespace Maylib
{
    namespace Core
    {
        class Input
        {
        public:
            static bool IsKeyDown(SDL_Scancode key);
            static bool IsKeyTyped(SDL_Scancode key);
            static s8 GetAxis(const std::string& axis, bool alt = false);

        private:
            static bool keyTyped;
            static bool keysDown[300];

        private:
            friend class Graphics::Window;
        };

    }
}
