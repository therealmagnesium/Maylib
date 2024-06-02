#include "MaylibApp.h"
#include "Core/Math.h"
#include "glm/gtc/type_ptr.hpp"

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

static bool drawSkybox = true;
static glm::vec3 lightDirection = glm::vec3(1.f, 0.f, 0.f);

MaylibApp::MaylibApp(const AppInfo& info) : Application(info)
{
    this->SetClearColor(0.01f, 0.01f, 0.01f);
    this->SetPrimaryCamera(&m_camera);

    m_camera.SetPosition(0.f, 1.f, 5.f);

    AssetManager::AddShader("basic", "assets/shaders/basic_vertex.glsl", "assets/shaders/basic_fragment.glsl");
    AssetManager::AddShader("skybox", "assets/shaders/skybox_vertex.glsl", "assets/shaders/skybox_fragment.glsl");
    AssetManager::AddShader("lighting", "assets/shaders/lighting_vertex.glsl", "assets/shaders/lighting_fragment.glsl");

    m_basicShader = AssetManager::GetShader("basic");
    m_skyboxShader = AssetManager::GetShader("skybox");
    m_lightingShader = AssetManager::GetShader("lighting");

    m_light.SetWorldDirection(V3_OPEN(lightDirection));

    m_model.SetPosition(0.f, 0.f, 0.f);
    m_model.SetRotation(0.f, 45.f, 0.f);
    m_model.SetScale(5.f, 5.f, 5.f);
    m_model.Load("assets/models/vase.obj");

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

    if (Input::IsKeyTyped(SDL_SCANCODE_F))
        this->ToggleFullscreen();

    m_camera.Update();

    m_light.SetWorldDirection(V3_OPEN(lightDirection));
    m_light.CalculateLocalDirection(m_model);
}

void MaylibApp::OnRender()
{
    m_light.UpdateUniforms(m_basicShader);

    if (drawSkybox)
        m_skybox.Draw(m_skyboxShader);

    m_model.Draw(m_basicShader);
}

void MaylibApp::OnUIRender()
{
    ImGui::Begin("Debug Menu");
    {
        ImGui::Text("FPS: %.3f", 1.f / Time::GetElapsed());
        ImGui::Text("Delta time: %f", Time::GetElapsed());
        ImGui::Text("Cam position: " V3_FMT, V3_OPEN(m_camera.GetPosition()));
        ImGui::Text("Cam rotation: " V3_FMT, V3_OPEN(m_camera.GetRotation()));

        ImGui::Checkbox("Skybox? ", &drawSkybox);
        ImGui::ColorPicker3("Light color", glm::value_ptr(m_light.GetColor()));

        ImGui::DragFloat3("Light direction", glm::value_ptr(lightDirection));
        ImGui::DragFloat3("Model position", glm::value_ptr(m_model.GetPosition()));
        ImGui::DragFloat3("Model rotation", glm::value_ptr(m_model.GetRotation()));
        ImGui::DragFloat3("Model scale", glm::value_ptr(m_model.GetScale()));
    }
    ImGui::End();
}
