#include "MaylibApp.h"
#include <Core/Input.h>
#include <Core/Log.h>

#include <SDL2/SDL_scancode.h>
#include <imgui.h>

using namespace Maylib::Core;
using namespace Maylib::Graphics;

MaylibApp::MaylibApp(const AppInfo& info) : Application(info) {}

void MaylibApp::OnUpdate()
{
    if (Input::IsKeyTyped(SDL_SCANCODE_ESCAPE))
        this->Quit();
}

void MaylibApp::OnUIRender() { ImGui::ShowDemoWindow(); }
