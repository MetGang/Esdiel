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
        Shader() noexcept;

        ///
        Shader(Shader const&) = delete;

        ///
        Shader& operator = (Shader const&) = delete;

        ///
        Shader(Shader&& rhs) noexcept;

        ///
        Shader& operator = (Shader&& rhs) noexcept;

        ///
        ~Shader() noexcept;

        ///
        NativeHandle_t GetNativeHandle() const noexcept;

        ///
        bool LoadFromFile(ShaderType type, char const* filePath);

        ///
        bool LoadFromCString(ShaderType type, char const* data) noexcept;

        ///
        bool IsValid() const noexcept;

    private:

        ///
        void M_Defaultize() noexcept;

        ///
        void M_Destroy() noexcept;

        ///
        bool M_Compile(ShaderType type, char const* data, int32_t size) noexcept;

        NativeHandle_t m_shader;
    };
}
