#pragma once

// Esdiel
#include <Esdiel/Math/Vector.hpp>

// C++
#include <vector>

namespace esd
{
    //
    class Color;

    ///
    enum class ImgExtType : int32_t
    {
        BMP,
        HDR,
        JPG,
        PNG,
        TGA
    };

    ///
    class Image
    {
    public:

        using Byte_t  = uint8_t;
        using Bytes_t = std::vector<Byte_t>;

        ///
        Image();

        ///
        Image(Image const&) = default;

        ///
        Image& operator = (Image const&) = default;

        ///
        Image(Image&& rhs) noexcept;

        ///
        Image& operator = (Image&& rhs) noexcept;

        ///
        ~Image() = default;

        ///
        void Create(Vec2u const& size, Color const& color);

        ///
        bool LoadFromFile(char const* filePath);

        ///
        bool SaveToFile(char const* filePath, ImgExtType extension, bool flipVertically = false) const;

        ///
        void FlipVertically();

        ///
        void FlipHorizontally();

        ///
        Byte_t* GetData();

        ///
        Byte_t const* GetData() const;

        ///
        size_t GetPixelsCount() const;

        ///
        uint32_t GetWidth() const;

        ///
        uint32_t GetHeight() const;

        ///
        Vec2u GetSize() const;

        ///
        uint32_t GetChannelsCount() const;

    private:

        Bytes_t m_bytes;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_channels;
    };
}
