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
        Image(Image&&) noexcept = default;

        ///
        Image& operator = (Image&&) noexcept = default;

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
        Vec2u const& GetSize() const;

        ///
        uint32_t GetChannelsCount() const;

        ///
        size_t GetPixelsCount() const;

        ///
        size_t GetBytesCount() const;

    private:

        Bytes_t m_bytes;
        Vec2u m_size;
        uint32_t m_channels;
    };
}
