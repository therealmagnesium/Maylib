#pragma once
#include "Core/Base.h"
#include <string>

namespace Maylib
{
    namespace Graphics
    {
        struct ShaderSource
        {
            std::string vertex;
            std::string fragment;
        };

        class Shader
        {
        public:
            Shader();
            ~Shader();

            void Bind();
            void Unbind();
            void Load(const ShaderSource& source);

            void SetInt(const std::string& name, s32 value);
            void SetFloat(const std::string& name, float value);

        private:
            u32 CompileShader(u32 type, const std::string& source);
            void CreateProgram(u32 vertexShader, u32 fragmentShader);

        private:
            u32 m_id;
        };
    }
}
