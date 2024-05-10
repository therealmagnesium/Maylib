#include "Graphics/Shader.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Maylib
{
    namespace Graphics
    {
        Shader::Shader() {}
        Shader::~Shader() { glDeleteProgram(m_id); }

        void Shader::Bind() { glUseProgram(m_id); }
        void Shader::Unbind() { glUseProgram(0); }

        void Shader::Load(const ShaderSource& source)
        {
            u32 vertexShader = this->CompileShader(GL_VERTEX_SHADER, source.vertex);
            u32 fragmentShader = this->CompileShader(GL_FRAGMENT_SHADER, source.fragment);
            this->CreateProgram(vertexShader, fragmentShader);
        }

        void Shader::SetInt(const std::string& name, s32 value, bool debug)
        {
            s32 location = glGetUniformLocation(m_id, name.c_str());
            if (location == -1 && debug)
            {
                LOG_WARN("int '%s' was not found in shader, or it is not in use", name.c_str());
                return;
            }

            glUniform1i(location, value);
        }

        void Shader::SetFloat(const std::string& name, float value, bool debug)
        {
            s32 location = glGetUniformLocation(m_id, name.c_str());
            if (location == -1 && debug)
            {
                LOG_WARN("float '%s' was not found in shader, or it is not in use", name.c_str());
                return;
            }

            glUniform1f(location, value);
        }

        void Shader::SetMat4(const std::string& name, glm::mat4 value, bool debug)
        {
            s32 location = glGetUniformLocation(m_id, name.c_str());

            if (location == -1 && debug)
            {
                LOG_WARN("float '%s' was not found in shader, or it is not in use", name.c_str());
                return;
            }

            glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
        }

        u32 Shader::CompileShader(u32 type, const std::string& source)
        {
            u32 shader = glCreateShader(type);
            const char* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, NULL);
            glCompileShader(shader);

            s32 success;
            char infoLog[512];
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                LOG_WARN("Shader failed to compile!\n %s", infoLog);
            }

            return shader;
        }

        void Shader::CreateProgram(u32 vertexShader, u32 fragmentShader)
        {
            m_id = glCreateProgram();
            glAttachShader(m_id, vertexShader);
            glAttachShader(m_id, fragmentShader);
            glLinkProgram(m_id);
            glValidateProgram(m_id);

            s32 success;
            char infoLog[512];
            glGetProgramiv(m_id, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(m_id, 512, NULL, infoLog);
                LOG_WARN("Shader program failed to link!\n %s", infoLog);
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }
    }
}
