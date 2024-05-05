#pragma once

#include <Core/Application.h>
#include <Core/VertexArray.h>
#include <Core/Buffer.h>

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
    VertexArray m_vertexArray;
    VertexBuffer m_vertexBuffer;
    IndexBuffer m_indexBuffer;

    Shader m_shader;
    Texture m_texture;
};
