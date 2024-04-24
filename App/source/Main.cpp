#include "MaylibApp.h"

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

    MaylibApp app(info);
    app.Run();

    return 0;
}
