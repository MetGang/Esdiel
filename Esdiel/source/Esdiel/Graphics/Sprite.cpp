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
        auto const texRect = Vec4f {
            m_textureRect.x / m_texture->GetSize().x,
            m_textureRect.y / m_texture->GetSize().y,
            m_textureRect.z / m_texture->GetSize().x,
            m_textureRect.w / m_texture->GetSize().y
        };

        auto vertices = m_vertexBuffer.GetData();

        vertices[0] = { { 0.0f, 0.0f, 0.0f }, m_color, { texRect.x, texRect.y + texRect.w } };
        vertices[1] = { { m_textureRect.z, 0.0f, 0.0f }, m_color, { texRect.x + texRect.z, texRect.y + texRect.w } };
        vertices[2] = { { m_textureRect.z, m_textureRect.w, 0.0f }, m_color, { texRect.x + texRect.z, texRect.y } };
        vertices[3] = { { 0.0f, m_textureRect.w, 0.0f }, m_color, { texRect.x, texRect.y } };
    }

    void Sprite::M_Defaultize()
    {
        m_vertexBuffer = { 4u, {}, PrimitiveType::TriangleFan };
        m_texture = nullptr;
        m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_textureRect = { 0.0f, 0.0f, 0.0f, 0.0f };
    }
}
