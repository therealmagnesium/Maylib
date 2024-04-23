#include <Core/Base.h>
#include <Core/Log.h>
#include <Core/Input.h>
#include <Graphics/Window.h>

#include <SDL2/SDL_scancode.h>

using namespace Maylib;
using namespace Maylib::Graphics;

int main(int argc, char* argv[])
{
    Window window(1280, 720, "Maylib App");

    while (!window.ShouldClose())
    {
        window.HandleEvents();

        if (Core::Input::IsKeyTyped(SDL_SCANCODE_ESCAPE))
            window.Close();

        window.Clear(0.08, 0.07, 0.15);
        window.Display();
    }
    return 0;
}
