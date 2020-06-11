#include <Esdiel/Graphics/Image.hpp>

// stb
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace esd
{
    Image::Image()
        : m_bytes {}
        , m_size { 0, 0 }
        , m_channels { 0 }
    {

    }

    void Image::Clear()
    {
        m_bytes.clear();
        m_size = { 0, 0 };
        m_channels = 0;
    }

    bool Image::LoadFromFile(char const* filePath)
    {
        int32_t w;
        int32_t h;
        int32_t bpp;

        Byte_t* ptr = stbi_load(filePath, &w, &h, &bpp, STBI_rgb_alpha);

        if (ptr)
        {
            m_size.x = w;
            m_size.y = h;
            m_channels = bpp;

            m_bytes.assign(ptr, ptr + (w * h * 4));

            stbi_image_free(ptr);

            return true;
        }

        return false;
    }

    bool Image::SaveToFile(char const* filePath, ImgExtType extension, bool flipVertically) const
    {
        stbi_flip_vertically_on_write(flipVertically);

        if (!m_bytes.empty())
        {
            switch (extension)
            {
                case ImgExtType::BMP: return stbi_write_bmp(filePath, m_size.x, m_size.y, m_channels, m_bytes.data());

                case ImgExtType::HDR: return false; // TODO implement

                case ImgExtType::JPG: return stbi_write_jpg(filePath, m_size.x, m_size.y, m_channels, m_bytes.data(), 90);

                case ImgExtType::PNG: return stbi_write_png(filePath, m_size.x, m_size.y, m_channels, m_bytes.data(), 0);

                case ImgExtType::TGA: return stbi_write_tga(filePath, m_size.x, m_size.y, m_channels, m_bytes.data());
            }
        }

        return false;
    }

    void Image::FlipVertically()
    {
        if (!m_bytes.empty())
        {
            size_t const rowSize = m_size.x * 4;

            auto top    = m_bytes.begin();
            auto bottom = m_bytes.end() - rowSize;

            for (size_t y = 0; y < m_size.y / 2; ++y)
            {
                std::swap_ranges(top, top + rowSize, bottom);

                top += rowSize;
                bottom -= rowSize;
            }
        }
    }

    void Image::FlipHorizontally()
    {
        if (!m_bytes.empty())
        {
            size_t const rowSize = m_size.x * 4;

            for (size_t y = 0; y < m_size.y; ++y)
            {
                auto left  = m_bytes.begin() + y * rowSize;
                auto right = m_bytes.begin() + (y + 1) * rowSize - 4;

                for (size_t x = 0; x < m_size.x / 2; ++x)
                {
                    std::swap_ranges(left, left + 4, right);

                    left += 4;
                    right -= 4;
                }
            }
        }
    }

    Image::Byte_t* Image::GetData()
    {
        return m_bytes.data();
    }

    Image::Byte_t const* Image::GetData() const
    {
        return m_bytes.data();
    }

    Vec2u const& Image::GetSize() const
    {
        return m_size;
    }

    Vec2u Image::GetSizeHalved() const
    {
        return m_size / 2u;
    }

    uint32_t Image::GetChannelsCount() const
    {
        return m_channels;
    }

    size_t Image::GetPixelsCount() const
    {
        return m_size.x * m_size.y;
    }

    size_t Image::GetBytesCount() const
    {
        return m_size.x * m_size.y * 4;
    }
}
