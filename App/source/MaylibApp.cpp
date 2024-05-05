#include "MaylibApp.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>
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
        -0.5f, 0.5f,  0.f, 0.f, 1.f, // v0
        -0.5f, -0.5f, 0.f, 0.f, 0.f, // v1
        0.5f,  -0.5f, 0.f, 1.f, 0.f, // v2
        0.5f,  0.5f,  0.f, 1.f, 1.f  // v3
    };

    u32 indices[] = {0, 1, 2, 2, 3, 0};

    m_vertexArray.Bind();

    m_vertexBuffer.Bind();
    m_vertexBuffer.SetData(vertices, LEN(vertices));

    m_indexBuffer.Bind();
    m_indexBuffer.SetData(indices, LEN(indices));

    m_vertexArray.LinkAttribs(0, 3, VERTEX_POS_OFFSET);
    m_vertexArray.LinkAttribs(2, 2, VERTEX_UV_OFFSET);

    m_vertexArray.Unbind();
    m_vertexBuffer.Unbind();
    m_indexBuffer.Unbind();

    ShaderSource shaderSource;
    shaderSource.vertex = ReadFile("assets/shaders/basic_vertex.glsl");
    shaderSource.fragment = ReadFile("assets/shaders/basic_fragment.glsl");
    m_shader.Load(shaderSource);

    m_texture.Load("assets/textures/checkerboard.png");
}

void MaylibApp::OnUpdate()
{
    if (Input::IsKeyTyped(SDL_SCANCODE_ESCAPE))
        this->Quit();

    if (Input::IsKeyTyped(SDL_SCANCODE_D))
        this->ToggleDebug();
}

void MaylibApp::OnRender()
{
    m_shader.Bind();
    m_texture.Bind();
    m_vertexArray.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_vertexArray.Unbind();
    m_texture.Unbind();
    m_shader.Unbind();
}

void MaylibApp::OnUIRender()
{
    ImGui::Begin("Debug Menu");
    {
        ImGui::Button("Hello");
    }
    ImGui::End();
}
