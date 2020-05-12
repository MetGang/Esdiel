#pragma once

// Esdiel
#include <Esdiel/Math/Vector.hpp>

namespace esd
{
    //
    class Image;

    ///
    class Texture
    {
    public:

        using NativeHandle_t = uint32_t;

        ///
        Texture() noexcept;

        ///
        Texture(Texture const&) = delete;

        ///
        Texture& operator = (Texture const&) = delete;

        ///
        Texture(Texture&& rhs) noexcept;

        ///
        Texture& operator = (Texture&& rhs) noexcept;

        ///
        ~Texture() noexcept;

        ///
        NativeHandle_t GetNativeHandle() const noexcept;

        ///
        bool Create(Vec2u const& size, void const* data = nullptr) noexcept;

        ///
        bool LoadFromImage(Image const& image) noexcept;

        ///
        bool LoadFromFile(char const* path);

        ///
        uint32_t GetWidth() const noexcept;

        ///
        uint32_t GetHeight() const noexcept;

        ///
        Vec2u GetSize() const noexcept;

        ///
        bool IsValid() const noexcept;

        ///
        void Bind(size_t slot) const noexcept;

    private:

        ///
        void M_Defaultize() noexcept;

        ///
        void M_Destroy() noexcept;

        NativeHandle_t m_texture;
        uint32_t m_width;
        uint32_t m_height;
    };
}
