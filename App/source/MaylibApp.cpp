#include "MaylibApp.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>
#include <Core/Time.h>
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

    ShaderSource skyboxShaderSource;
    skyboxShaderSource.vertex = ReadFile("assets/shaders/skybox_vertex.glsl");
    skyboxShaderSource.fragment = ReadFile("assets/shaders/skybox_fragment.glsl");
    m_skyboxShader.Load(skyboxShaderSource);

    AssetManager::AddTexture("model_diffuse", "diffuse", "assets/textures/backpack/diffuse.jpg");
    Texture* texture = AssetManager::GetTexture("model_diffuse");

    m_model.SetTexture(TEXTURE_MAP_DIFFUSE, texture);
    m_model.SetRotation(0.f, 45.f, 0.f);
    m_model.Load("assets/models/backpack.obj");

    std::string paths[6] = {
        "assets/textures/skybox/right.jpg",  "assets/textures/skybox/left.jpg",  "assets/textures/skybox/top.jpg",
        "assets/textures/skybox/bottom.jpg", "assets/textures/skybox/front.jpg", "assets/textures/skybox/back.jpg",
    };

    m_skybox.Load(paths);
}

void MaylibApp::OnUpdate()
{
    if (Input::IsKeyTyped(SDL_SCANCODE_ESCAPE))
        this->Quit();

    if (Input::IsKeyTyped(SDL_SCANCODE_E))
        this->ToggleDebug();

    m_camera.Update();
}

void MaylibApp::OnRender()
{
    m_camera.CalculateMatrix(m_skyboxShader, true);
    m_skybox.Draw(m_skyboxShader);

    m_camera.CalculateMatrix(m_shader);
    m_model.Draw(m_shader);
}

void MaylibApp::OnUIRender()
{
    ImGui::Begin("Debug Menu");
    {
        ImGui::Button("Hello");
        ImGui::Text("FPS: %.3f", 1.f / Time::GetElapsed());
        ImGui::Text("Delta time: %f", Time::GetElapsed());
    }
    ImGui::End();
}
