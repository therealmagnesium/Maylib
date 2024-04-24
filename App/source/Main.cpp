#include <Core/Application.h>

using namespace Maylib;
using namespace Maylib::Core;
using namespace Maylib::Graphics;

int main(int argc, char* argv[])
{
    AppInfo info;
    info.name = "Maylib App";
    info.author = "Magnus Ahlstromer V";
    info.screenWidth = 1280;
    info.screenHeight = 720;

    Application app(info);
    app.Run();

    return 0;
}
