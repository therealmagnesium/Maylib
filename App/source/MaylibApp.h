#pragma once

#include <Core/Application.h>

#include <Graphics/Camera.h>
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
    Mesh m_mesh;
    Model m_model;
    Shader m_shader;
    Texture m_texture;

    Camera m_camera;
};
