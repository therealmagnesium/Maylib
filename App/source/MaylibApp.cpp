#include "MaylibApp.h"
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
static glm::vec3 lightPosition = glm::vec3(0.f);
static glm::vec3 lightColor = glm::vec3(250.f / 255.f, 1.f, 204.f / 255.f);

MaylibApp::MaylibApp(const AppInfo& info) : Application(info)
{
    this->SetClearColor(0.01f, 0.01f, 0.01f);
    this->SetPrimaryCamera(&m_camera);

    AssetManager::AddShader("basic", "assets/shaders/basic_vertex.glsl", "assets/shaders/basic_fragment.glsl");
    AssetManager::AddShader("skybox", "assets/shaders/skybox_vertex.glsl", "assets/shaders/skybox_fragment.glsl");
    AssetManager::AddShader("lighting", "assets/shaders/lighting_vertex.glsl", "assets/shaders/lighting_fragment.glsl");
    AssetManager::AddTexture("model_diffuse", "assets/textures/duck/diffuse.jpg", TEXTURE_MAP_DIFFUSE, true);

    m_basicShader = AssetManager::GetShader("basic");
    m_skyboxShader = AssetManager::GetShader("skybox");
    m_lightingShader = AssetManager::GetShader("lighting");
    Texture* texture = AssetManager::GetTexture("model_diffuse");

    m_model.SetTexture(TEXTURE_MAP_DIFFUSE, texture);
    m_model.SetPosition(0.f, 0.f, -3.f);
    m_model.SetRotation(0.f, 45.f, 0.f);
    m_model.Load("assets/models/duck.obj");

    m_lightCube.SetPosition(5.f, 0.f, 0.f);
    m_lightCube.Load("assets/models/box.obj");

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
}

void MaylibApp::OnRender()
{
    lightPosition = m_lightCube.GetPosition();

    m_lightingShader->Bind();
    m_lightingShader->SetVec3("lightPosition", lightPosition);
    m_lightingShader->SetVec3("lightColor", lightColor);
    m_lightingShader->SetVec3("camPosition", m_camera.GetPosition());
    m_lightingShader->Unbind();

    m_basicShader->Bind();
    m_basicShader->SetVec3("lightPosition", lightPosition);
    m_basicShader->SetVec3("lightColor", lightColor);
    m_basicShader->Unbind();

    if (drawSkybox)
        m_skybox.Draw(m_skyboxShader);

    m_model.Draw(m_basicShader);
    m_lightCube.Draw(m_lightingShader);
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
        ImGui::ColorPicker4("Light color", glm::value_ptr(lightColor));

        ImGui::DragFloat3("Model position", glm::value_ptr(m_model.GetPosition()));
        ImGui::DragFloat3("Model rotation", glm::value_ptr(m_model.GetRotation()));
        ImGui::DragFloat3("Model scale", glm::value_ptr(m_model.GetScale()));
    }
    ImGui::End();
}
