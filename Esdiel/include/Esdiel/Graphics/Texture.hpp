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
        Texture();

        ///
        Texture(Texture const&) = delete;

        ///
        Texture& operator = (Texture const&) = delete;

        ///
        Texture(Texture&& rhs) noexcept;

        ///
        Texture& operator = (Texture&& rhs) noexcept;

        ///
        ~Texture();

        ///
        NativeHandle_t GetNativeHandle() const;

        ///
        bool Create(Vec2u const& size, void const* data = nullptr);

        ///
        bool LoadFromImage(Image const& image);

        ///
        bool LoadFromFile(char const* path);

        ///
        uint32_t GetWidth() const;

        ///
        uint32_t GetHeight() const;

        ///
        Vec2u GetSize() const;

        ///
        bool IsValid() const;

        ///
        void Bind(size_t slot) const;

    private:

        ///
        void M_Destroy();

        NativeHandle_t m_texture;
        uint32_t m_width;
        uint32_t m_height;
    };
}
