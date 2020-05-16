#pragma once

// Esdiel
#include <Esdiel/Graphics/ImgExtType.hpp>
#include <Esdiel/Math/Vector.hpp>

// C++
#include <vector>

namespace esd
{
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
        void Clear();

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
        uint32_t GetWidth() const;

        ///
        uint32_t GetHeight() const;

        ///
        Vec2u GetSize() const;

        ///
        uint32_t GetChannelsCount() const;

        ///
        size_t GetPixelsCount() const;

        ///
        size_t GetBytesCount() const;

    private:

        ///
        void M_Defaultize();

        Bytes_t m_bytes;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_channels;
    };
}
