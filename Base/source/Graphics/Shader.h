#pragma once
#include "Core/Base.h"
#include <glm/ext/matrix_float4x4.hpp>
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

            void SetInt(const std::string& name, s32 value, bool debug = false);
            void SetFloat(const std::string& name, float value, bool debug = false);
            void SetVec3(const std::string& name, glm::vec3 value, bool debug = false);
            void SetVec4(const std::string& name, glm::vec4 value, bool debug = false);
            void SetMat4(const std::string& name, glm::mat4 value, bool debug = false);

        private:
            u32 CompileShader(u32 type, const std::string& source);
            void CreateProgram(u32 vertexShader, u32 fragmentShader);

        private:
            u32 m_id;
        };
    }
}
