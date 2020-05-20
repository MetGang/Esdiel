#include <Esdiel/Graphics/ShaderProgram.hpp>

// C++
#include <algorithm>
#include <cstdio>

// glad
#include <glad/glad.h>

// glm
#include <glm/gtc/type_ptr.hpp>

namespace esd
{
    ShaderProgram::ShaderProgram()
        : m_program { 0 }
        , m_uniformsLocation {}
    {

    }

    ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept
        : m_program { rhs.m_program }
        , m_uniformsLocation { std::move(rhs.m_uniformsLocation) }
    {
        
    }

    ShaderProgram& ShaderProgram::operator = (ShaderProgram&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_program = rhs.m_program;
            m_uniformsLocation = std::move(rhs.m_uniformsLocation);
        }

        return *this;
    }

    ShaderProgram::~ShaderProgram()
    {
        M_Destroy();
    }

    ShaderProgram::NativeHandle_t ShaderProgram::GetNativeHandle() const
    {
        return m_program;
    }

    bool ShaderProgram::LinkShaders(std::initializer_list<Shader*> il)
    {
        if (std::all_of(il.begin(), il.end(), [](auto const ptr) { return ptr->IsValid(); }))
        {
            NativeHandle_t program = glCreateProgram();

            for (auto const ptr : il)
            {
                glAttachShader(program, ptr->GetNativeHandle());
            }

            glLinkProgram(program);

            if (M_FinishLinking(program))
            {
                for (auto const ptr : il)
                {
                    glDetachShader(program, ptr->GetNativeHandle());
                }

                return true;
            }
            
            return false;
        }

        #if defined(ESD_DEBUG)
        {
            // TODO better logging
            std::fprintf(stderr, "Sent shaders must be valid ones\n");
        }
        #endif

        return false;
    }

    void ShaderProgram::UseProgram() const
    {
        glUseProgram(m_program);
    }

    bool ShaderProgram::SetUniform(char const* name, bool value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform1i(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2b const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform2i(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3b const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform3i(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4b const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform4i(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, int32_t value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform1i(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2i const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform2i(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3i const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform3i(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4i const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform4i(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, uint32_t value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform1ui(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2u const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform2ui(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3u const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform3ui(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4u const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform4ui(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, float value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform1f(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform2f(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform3f(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniform4f(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Mat2x2f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniformMatrix2fv(it->second, 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Mat3x3f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Mat4x4f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::IsValid() const
    {
        return m_program;
    }

    void ShaderProgram::M_Destroy()
    {
        glDeleteProgram(m_program);

        m_uniformsLocation.clear();
    }

    bool ShaderProgram::M_FinishLinking(NativeHandle_t program)
    {
        int32_t success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (success)
        {
            M_Destroy();

            m_program = program;

            int32_t count;
            int32_t size;
            GLenum type;
            char name[64];

            glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &count);

            for (int32_t i = 0; i < count; ++i)
            {
                glGetActiveUniform(m_program, i, sizeof(name), nullptr, &size, &type, name);

                m_uniformsLocation.emplace(FNV1a_32(name), i);
            }

            return true;
        }
        else
        {
            #if defined(ESD_DEBUG)
            {
                char infoLog[1024];
                glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);

                // TODO better log 'infoLog'
                std::fprintf(stderr, "%s", infoLog);
            }
            #endif

            glDeleteProgram(program);

            return false;
        }
    }
}
