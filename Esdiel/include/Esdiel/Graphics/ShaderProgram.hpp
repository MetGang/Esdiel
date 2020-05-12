#pragma once

// Esdiel
#include <Esdiel/Graphics/Shader.hpp>
#include <Esdiel/Math/Vector.hpp>
#include <Esdiel/Utility/FNV.hpp>

// C++
#include <map>

namespace esd
{
    ///
    class ShaderProgram
    {
    public:

        using NativeHandle_t     = uint32_t;
        using UniformsLocation_t = std::map<Hash32_t, int32_t>;

        ///
        ShaderProgram();

        ///
        ShaderProgram(ShaderProgram const&) = delete;

        ///
        ShaderProgram& operator = (ShaderProgram const&) = delete;

        ///
        ShaderProgram(ShaderProgram&& rhs) noexcept;

        ///
        ShaderProgram& operator = (ShaderProgram&& rhs) noexcept;

        ///
        ~ShaderProgram();

        ///
        NativeHandle_t GetNativeHandle() const;

        ///
        bool LinkShaders(std::initializer_list<Shader*> il);

        ///
        void UseProgram() const;

        ///
        bool SetUniform(char const* name, bool value) const;

        ///
        bool SetUniform(char const* name, Vec2b const& value) const;

        ///
        bool SetUniform(char const* name, Vec3b const& value) const;

        ///
        bool SetUniform(char const* name, Vec4b const& value) const;

        ///
        bool SetUniform(char const* name, int32_t value) const;

        ///
        bool SetUniform(char const* name, Vec2i const& value) const;

        ///
        bool SetUniform(char const* name, Vec3i const& value) const;

        ///
        bool SetUniform(char const* name, Vec4i const& value) const;

        ///
        bool SetUniform(char const* name, uint32_t value) const;

        ///
        bool SetUniform(char const* name, Vec2u const& value) const;

        ///
        bool SetUniform(char const* name, Vec3u const& value) const;

        ///
        bool SetUniform(char const* name, Vec4u const& value) const;

        ///
        bool SetUniform(char const* name, float value) const;

        ///
        bool SetUniform(char const* name, Vec2f const& value) const;

        ///
        bool SetUniform(char const* name, Vec3f const& value) const;

        ///
        bool SetUniform(char const* name, Vec4f const& value) const;

        ///
        bool IsValid() const;

    private:

        ///
        void M_Destroy();

        ///
        bool M_FinishLinking(NativeHandle_t program);

        NativeHandle_t m_program;
        UniformsLocation_t m_uniformsLocation;
    };
}
