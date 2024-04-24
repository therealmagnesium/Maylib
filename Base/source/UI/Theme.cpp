#include "UI/Theme.h"
#include <imgui.h>

namespace Maylib
{
    namespace UI
    {
        void SetTheme()
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4* colors = ImGui::GetStyle().Colors;

            colors[ImGuiCol_WindowBg] = Colors::titlebar;
            colors[ImGuiCol_ChildBg] = Colors::background;

            colors[ImGuiCol_Header] = Colors::groupHeader;
            colors[ImGuiCol_HeaderActive] = Colors::groupHeader;
            colors[ImGuiCol_HeaderHovered] = Colors::groupHeaderHover;

            colors[ImGuiCol_Button] = Colors::button;
            colors[ImGuiCol_ButtonActive] = Colors::buttonActive;
            colors[ImGuiCol_ButtonHovered] = Colors::buttonHover;

            colors[ImGuiCol_TitleBg] = Colors::titlebar;
            colors[ImGuiCol_TitleBgActive] = Colors::titlebar;

            colors[ImGuiCol_MenuBarBg] = ImColor(0, 0, 0, 255);
        }
    }
}
