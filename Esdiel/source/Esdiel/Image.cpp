#include <Esdiel/Image.hpp>

// stb
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace rv
{
    Image::Image()
        : m_bytes {}
        , m_width { 0 }
        , m_height { 0 }
        , m_channels { 0 }
    {

    }

    Image::Image(Image&& rhs) noexcept
        : m_bytes { std::move(rhs.m_bytes) }
        , m_width { rhs.m_width }
        , m_height { rhs.m_height }
        , m_channels { rhs.m_channels }
    {
        rhs.m_width = 0;
        rhs.m_height = 0;
        rhs.m_channels = 0;
    }

    Image& Image::operator = (Image&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_bytes = std::move(rhs.m_bytes);
            m_width = rhs.m_width;
            m_height = rhs.m_height;
            m_channels = rhs.m_channels;

            rhs.m_width = 0;
            rhs.m_height = 0;
            rhs.m_channels = 0;
        }

        return *this;
    }

    bool Image::LoadFromFile(char const* filePath)
    {
        int32_t w;
        int32_t h;
        int32_t bpp;

        Byte_t* ptr = stbi_load(filePath, &w, &h, &bpp, STBI_rgb_alpha);

        if (ptr)
        {
            m_width = w;
            m_height = h;
            m_channels = bpp;

            m_bytes.assign(ptr, ptr + (m_width * m_height * 4));

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
                case ImgExtType::BMP: return stbi_write_bmp(filePath, m_width, m_height, m_channels, m_bytes.data());

                case ImgExtType::HDR: return false; // TODO implement

                case ImgExtType::JPG: return stbi_write_jpg(filePath, m_width, m_height, m_channels, m_bytes.data(), 90);

                case ImgExtType::PNG: return stbi_write_png(filePath, m_width, m_height, m_channels, m_bytes.data(), 0);

                case ImgExtType::TGA: return stbi_write_tga(filePath, m_width, m_height, m_channels, m_bytes.data());
            }
        }

        return false;
    }

    void Image::FlipVertically()
    {
        if (!m_bytes.empty())
        {
            size_t const rowSize = m_width * 4;

            auto top    = m_bytes.begin();
            auto bottom = m_bytes.end() - rowSize;

            for (size_t y = 0; y < m_height / 2; ++y)
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
            size_t const rowSize = m_width * 4;

            for (size_t y = 0; y < m_height; ++y)
            {
                auto left  = m_bytes.begin() + y * rowSize;
                auto right = m_bytes.begin() + (y + 1) * rowSize - 4;

                for (size_t x = 0; x < m_width / 2; ++x)
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

    size_t Image::GetPixelsCount() const
    {
        return m_width * m_height;
    }

    ///
    uint32_t Image::GetWidth() const
    {
        return m_width;
    }

    ///
    uint32_t Image::GetHeight() const
    {
        return m_height;
    }

    ///
    uint32_t Image::GetChannelsCount() const
    {
        return m_channels;
    }
}
