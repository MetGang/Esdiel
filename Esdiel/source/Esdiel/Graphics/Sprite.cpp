#include <Esdiel/Graphics/Sprite.hpp>

/// Esdiel
#include <Esdiel/Graphics/Texture.hpp>

namespace esd
{
    Sprite::Sprite()
        : m_vertexBuffer { 4u, {}, PrimitiveType::TriangleFan }
        , m_texture { nullptr }
        , m_color { 1.0f, 1.0f, 1.0f, 1.0f }
        , m_textureRect { 0.0f, 0.0f, 0.0f, 0.0f }
    {

    }

    Sprite::Sprite(Sprite&& rhs) noexcept
        : m_vertexBuffer{ std::move(rhs.m_vertexBuffer) }
        , m_texture { rhs.m_texture }
        , m_color { rhs.m_color }
        , m_textureRect { rhs.m_textureRect }
    {
        
    }

    Sprite& Sprite::operator = (Sprite&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_vertexBuffer = std::move(rhs.m_vertexBuffer);
            m_texture = rhs.m_texture;
            m_color = rhs.m_color;
            m_textureRect = rhs.m_textureRect;

            rhs.M_Defaultize();
        }

        return *this;
    }

    void Sprite::SetTexture(Texture const& texture)
    {
        m_texture = &texture;
        m_textureRect = { 0.0f, 0.0f, texture.GetSize().x, texture.GetSize().y };
    }

    Texture const& Sprite::GetTexture() const
    {
        return *m_texture;
    }

    void Sprite::SetColor(Vec4f const& color)
    {
        m_color = color;
    }

    Vec4f const& Sprite::GetColor() const
    {
        return m_color;
    }

    void Sprite::SetTextureRect(Vec4f const& textureRect)
    {
        m_textureRect = textureRect;
    }

    Vec4f const& Sprite::GetTextureRect() const
    {
        return m_textureRect;
    }

    Vec4f Sprite::GetLocalBounds() const
    {
        M_Update();

        auto const bounds = m_vertexBuffer.GetBounds2D();
        auto const pos = GetPosition();

        return { bounds.x + pos.x, bounds.y + pos.y, bounds.z + pos.x, bounds.w + pos.y };
    }

    void Sprite::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        M_Update();

        m_texture->Bind(0);

        m_vertexBuffer.Render(window, shaderProgram, camera, GetTransform());
    }

    void Sprite::M_Update() const
    {
        auto vertices = m_vertexBuffer.GetData();
        auto const& texSize = m_texture->GetSize();
        auto rect = Vec4f{ m_textureRect.x / texSize.x, m_textureRect.y / texSize.y, m_textureRect.z / texSize.x, m_textureRect.w / texSize.y };

        vertices[0] = {
            { m_textureRect.x, m_textureRect.y, 0.0f },
            m_color,
            { rect.x, rect.y }
        };

        vertices[1] = {
            { m_textureRect.x + m_textureRect.z, m_textureRect.y, 0.0f },
            m_color,
            { rect.x + rect.z, rect.y }
        };

        vertices[2] = {
            { m_textureRect.x + m_textureRect.z, m_textureRect.y + m_textureRect.w, 0.0f },
            m_color,
            { rect.x + rect.z, rect.y + rect.w }
        };

        vertices[3] = {
            { m_textureRect.x, m_textureRect.y + m_textureRect.w, 0.0f },
            m_color,
            { rect.x, rect.y + rect.w }
        };
    }

    void Sprite::M_Defaultize()
    {
        m_vertexBuffer = { 4u, {}, PrimitiveType::TriangleFan };
        m_texture = nullptr;
        m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_textureRect = { 0.0f, 0.0f, 0.0f, 0.0f };
    }
}
