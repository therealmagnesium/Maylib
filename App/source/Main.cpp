#include <stdio.h>
#include <stdlib.h>

#include <Core/Base.h>
#include <Core/Log.h>
#include <Graphics/Window.h>

using namespace Maylib;
using namespace Maylib::Graphics;

int main(int argc, char* argv[])
{
    Window window(1024, 576, "Maylib App");

    while (!window.ShouldClose())
    {
        window.HandleEvents();
    }
    return 0;
}
