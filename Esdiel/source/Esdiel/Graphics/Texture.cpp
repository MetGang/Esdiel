#include <Esdiel/Graphics/Texture.hpp>

// Esdiel
#include <Esdiel/Graphics/Image.hpp>

// glad
#include <glad/glad.h>

namespace esd
{
    Texture::Texture()
        : m_texture { 0 }
        , m_width { 0 }
        , m_height { 0 }
    {

    }

    Texture::Texture(Texture&& rhs) noexcept
        : m_texture { rhs.m_texture }
    {
        rhs.m_texture = 0;
    }

    Texture& Texture::operator = (Texture&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_texture = rhs.m_texture;
            rhs.m_texture = 0;
        }

        return *this;
    }

    Texture::~Texture()
    {
        M_Destroy();
    }

    Texture::NativeHandle_t Texture::GetNativeHandle() const
    {
        return m_texture;
    }

    bool Texture::Create(Vec2u const& size, void const* data)
    {
        M_Destroy();

        m_width = size[0];
        m_height = size[1];

        glGenTextures(1, &m_texture);

        Bind(0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        return true;
    }

    bool Texture::LoadFromImage(Image const& image)
    {
        return Create(image.GetSize(), image.GetData());
    }

    bool Texture::LoadFromFile(char const* path)
    {
        Image image;

        if (image.LoadFromFile(path))
        {
            return LoadFromImage(image);
        }

        return false;
    }

    uint32_t Image::GetWidth() const
    {
        return m_width;
    }

    uint32_t Image::GetHeight() const
    {
        return m_height;
    }

    Vec2u Texture::GetSize() const
    {
        return { m_width, m_height };
    }

    bool Texture::IsValid() const
    {
        return m_texture;
    }

    void Texture::M_Destroy()
    {
        glDeleteTextures(1, &m_texture);
    }

    void Texture::Bind(size_t slot) const
    {
        if (m_texture)
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }
    }
}
