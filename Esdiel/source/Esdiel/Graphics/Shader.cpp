#include <Esdiel/Graphics/Shader.hpp>

// C++
#include <fstream>
#include <memory>

// glad
#include <glad/glad.h>

namespace
{
    std::unique_ptr<char const[]> GetFileContents(char const* filePath)
    {
        std::ifstream file{ filePath, std::ios_base::binary };

        if (file)
        {
            file.seekg(0, std::ios_base::end);

            auto const size = file.tellg();

            std::unique_ptr<char[]> ptr;

            if (size > 0)
            {
                file.seekg(0, std::ios_base::beg);

                ptr.reset(new char[static_cast<size_t>(size) + 1]);

                file.read(ptr.get(), size);
                ptr[size] = '\0';
            }

            return ptr;
        }

        return nullptr;
    }
}

namespace esd
{
    Shader::Shader() noexcept
        : m_shader { 0 }
    {

    }

    Shader::Shader(Shader&& rhs) noexcept
        : m_shader { rhs.m_shader }
    {
        rhs.M_Defaultize();
    }

    Shader& Shader::operator = (Shader&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_shader = rhs.m_shader;

            rhs.M_Defaultize();
        }

        return *this;
    }

    Shader::~Shader() noexcept
    {
        M_Destroy();
    }

    Shader::NativeHandle_t Shader::GetNativeHandle() const noexcept
    {
        return m_shader;
    }

    bool Shader::LoadFromFile(ShaderType type, char const* filePath)
    {
        auto ptr = GetFileContents(filePath);

        return ptr && M_Compile(type, ptr.get(), -1);
    }

    bool Shader::LoadFromCString(ShaderType type, char const* data) noexcept
    {
        return M_Compile(type, data, -1);
    }

    bool Shader::IsValid() const noexcept
    {
        return m_shader;
    }

    void Shader::M_Defaultize() noexcept
    {
        m_shader = 0;
    }

    void Shader::M_Destroy() noexcept
    {
        glDeleteShader(m_shader);
    }

    bool Shader::M_Compile(ShaderType type, char const* data, int32_t size) noexcept
    {
        NativeHandle_t shader = glCreateShader(impl::GetNativeHandle(type));
        glShaderSource(shader, 1, &data, &size);
        glCompileShader(shader);

        int32_t success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success)
        {
            M_Destroy();

            m_shader = shader;

            return true;
        }
        else
        {
            #if defined(ESD_DEBUG)
            {
                char infoLog[1024];
                glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

                // TODO better logging
                std::fprintf(stderr, "%s", infoLog);
            }
            #endif

            glDeleteShader(shader);

            return false;
        }
    }
}
