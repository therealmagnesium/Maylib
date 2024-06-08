#pragma once

#include <Core/Application.h>

#include <Graphics/Camera.h>
#include <Graphics/Cubemap.h>
#include <Graphics/Light.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

using namespace Maylib::Core;
using namespace Maylib::Graphics;

class MaylibApp : public Application
{
public:
    MaylibApp(const AppInfo& info);

    void OnUpdate() override;
    void OnRender() override;
    void OnUIRender() override;

private:
    Camera m_camera;

    Model m_model;
    Model m_lightCube;

    Cubemap m_skybox;
    PointLight m_pointLight;
    PointLight m_pointLight2;

    Shader* m_skyboxShader;
    Shader* m_basicShader;
    Shader* m_lightingShader;
};
