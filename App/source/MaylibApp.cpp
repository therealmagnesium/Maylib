#include "MaylibApp.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>
#include <Core/Vertex.h>
#include <Core/VertexArray.h>

#include <Graphics/Shader.h>

#include <SDL2/SDL_scancode.h>
#include <imgui.h>
#include <glad/glad.h>

using namespace Maylib::Core;
using namespace Maylib::Graphics;

MaylibApp::MaylibApp(const AppInfo& info) : Application(info)
{
    this->SetClearColor(0.05f, 0.05f, 0.1f);

    ShaderSource shaderSource;
    shaderSource.vertex = ReadFile("assets/shaders/basic_vertex.glsl");
    shaderSource.fragment = ReadFile("assets/shaders/basic_fragment.glsl");
    m_shader.Load(shaderSource);

    AssetManager::AddTexture("model_diffuse", "diffuse", "assets/models/diffuse.jpg");
    Texture* texture = AssetManager::GetTexture("model_diffuse");

    m_model.SetTexture(TEXTURE_MAP_DIFFUSE, texture);
    m_model.Load("assets/models/backpack.obj");
}

void MaylibApp::OnUpdate()
{
    if (Input::IsKeyTyped(SDL_SCANCODE_ESCAPE))
        this->Quit();

    if (Input::IsKeyTyped(SDL_SCANCODE_D))
        this->ToggleDebug();

    m_camera.Update();
}

void MaylibApp::OnRender()
{
    m_camera.CalculateMatrix(m_shader);
    m_model.Draw(m_shader);
}

void MaylibApp::OnUIRender()
{
    ImGui::Begin("Debug Menu");
    {
        ImGui::Button("Hello");
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
}
