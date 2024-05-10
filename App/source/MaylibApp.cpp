#include "MaylibApp.h"

#include <Core/Application.h>
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

    float vertices[] = {
        -0.5f, 0.5f,  0.f, 0.f, 0.f, 0.f, 0.f, 1.f, // v0
        -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, // v1
        0.5f,  -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, // v2
        0.5f,  0.5f,  0.f, 0.f, 0.f, 0.f, 1.f, 1.f  // v3
    };

    Vertex betterVertices[] = {
        { {-0.5f, 0.5f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
        { {0.5f, -0.5f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 0.f}},
        {  {0.5f, 0.5f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f}}
    };

    u32 indices[] = {0, 1, 2, 2, 3, 0};

    ShaderSource shaderSource;
    shaderSource.vertex = ReadFile("assets/shaders/basic_vertex.glsl");
    shaderSource.fragment = ReadFile("assets/shaders/basic_fragment.glsl");
    m_shader.Load(shaderSource);

    m_texture.SetType("diffuse");
    m_texture.Load("assets/textures/checkerboard.png");

    MeshData data;

    for (Vertex v : betterVertices)
        data.vertices.push_back(v);

    for (u32 i : indices)
        data.indices.push_back(i);

    data.textures.push_back(m_texture);

    m_mesh.Create(data);
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
    m_mesh.Draw(m_shader);
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
