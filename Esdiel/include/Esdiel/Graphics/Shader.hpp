#pragma once

// Esdiel
#include <Esdiel/Graphics/ShaderType.hpp>

namespace esd
{
    ///
    class Shader
    {
    public:

        using NativeHandle_t = uint32_t;

        ///
        Shader();

        ///
        Shader(Shader const&) = delete;

        ///
        Shader& operator = (Shader const&) = delete;

        ///
        Shader(Shader&& rhs) noexcept;

        ///
        Shader& operator = (Shader&& rhs) noexcept;

        ///
        ~Shader();

        ///
        NativeHandle_t GetNativeHandle() const;

        ///
        bool LoadFromFile(ShaderType type, char const* filePath);

        ///
        bool LoadFromCString(ShaderType type, char const* data);

        ///
        bool IsValid() const;

    private:

        ///
        void M_Defaultize();

        ///
        void M_Destroy();

        ///
        bool M_Compile(ShaderType type, char const* data, int32_t size);

        NativeHandle_t m_shader;
    };
}
