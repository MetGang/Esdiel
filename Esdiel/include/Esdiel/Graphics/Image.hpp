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
        Image() noexcept;

        ///
        Image(Image const&) = default;

        ///
        Image& operator = (Image const&) = default;

        ///
        Image(Image&& rhs) noexcept;

        ///
        Image& operator = (Image&& rhs) noexcept;

        ///
        ~Image() noexcept = default;

        ///
        void Create(Vec2u const& size, Color const& color);

        ///
        bool LoadFromFile(char const* filePath);

        ///
        bool SaveToFile(char const* filePath, ImgExtType extension, bool flipVertically = false) const noexcept;

        ///
        void FlipVertically() noexcept;

        ///
        void FlipHorizontally() noexcept;

        ///
        Byte_t* GetData() noexcept;

        ///
        Byte_t const* GetData() const noexcept;

        ///
        size_t GetPixelsCount() const noexcept;

        ///
        uint32_t GetWidth() const noexcept;

        ///
        uint32_t GetHeight() const noexcept;

        ///
        Vec2u GetSize() const noexcept;

        ///
        uint32_t GetChannelsCount() const noexcept;

    private:

        Bytes_t m_bytes;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_channels;
    };
}
