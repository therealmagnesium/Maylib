#pragma once
#include <imgui.h>

namespace Maylib
{
    namespace UI
    {
        namespace Colors
        {
            constexpr ImColor background = ImColor(36, 36, 36, 255);
            constexpr ImColor groupHeader = ImColor(46, 46, 46, 255);
            constexpr ImColor groupHeaderHover = ImColor(36, 36, 36, 255);
            constexpr ImColor titlebar = ImColor(21, 21, 21, 255);
            constexpr ImColor button = ImColor(56, 56, 56, 255);
            constexpr ImColor buttonActive = ImColor(70, 70, 70, 255);
            constexpr ImColor buttonHover = ImColor(56, 56, 56, 150);
        }

        void SetTheme();
    }
}
