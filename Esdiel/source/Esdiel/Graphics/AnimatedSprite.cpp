#include <Esdiel/Graphics/AnimatedSprite.hpp>

/// Esdiel
#include <Esdiel/Graphics/Texture.hpp>

namespace esd
{
    AnimatedSprite::AnimatedSprite()
        : m_vertexBuffer { 4u, {}, PrimitiveType::TriangleFan }
        , m_texture { nullptr }
        , m_color { 1.0f, 1.0f, 1.0f, 1.0f }
        , m_frameSize { 0.0f, 0.0f }
        , m_currentFrame { 0 }
        , m_framesInRowCount { 1 }
    {

    }

    AnimatedSprite::AnimatedSprite(AnimatedSprite&& rhs) noexcept
        : m_vertexBuffer{ std::move(rhs.m_vertexBuffer) }
        , m_texture { rhs.m_texture }
        , m_color { rhs.m_color }
        , m_frameSize { rhs.m_frameSize }
        , m_currentFrame { rhs.m_currentFrame }
        , m_framesInRowCount { rhs.m_framesInRowCount }
    {
        
    }

    AnimatedSprite& AnimatedSprite::operator = (AnimatedSprite&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_vertexBuffer = std::move(rhs.m_vertexBuffer);
            m_texture = rhs.m_texture;
            m_color = rhs.m_color;
            m_frameSize = rhs.m_frameSize;
            m_currentFrame = rhs.m_currentFrame;
            m_framesInRowCount = rhs.m_framesInRowCount;

            rhs.M_Defaultize();
        }

        return *this;
    }

    void AnimatedSprite::SetTexture(Texture const& texture)
    {
        m_texture = &texture;
    }

    Texture const& AnimatedSprite::GetTexture() const
    {
        return *m_texture;
    }

    void AnimatedSprite::SetColor(Vec4f const& color)
    {
        m_color = color;
    }

    Vec4f const& AnimatedSprite::GetColor() const
    {
        return m_color;
    }

    void AnimatedSprite::SetFrameSize(Vec2f const& frameSize)
    {
        m_frameSize = frameSize;
    }

    Vec2f const& AnimatedSprite::GetFrameSize() const
    {
        return m_frameSize;
    }

    void AnimatedSprite::SetCurrentFrame(uint32_t index)
    {
        m_currentFrame = index;
    }

    uint32_t AnimatedSprite::GetCurrentFrame() const
    {
        return m_currentFrame;
    }

    void AnimatedSprite::SetFramesInRowCount(uint32_t count)
    {
        m_framesInRowCount = count;
    }

    uint32_t AnimatedSprite::GetramesInRowCount() const
    {
        return m_framesInRowCount;
    }

    Vec4f AnimatedSprite::GetLocalBounds() const
    {
        M_Update();

        auto const bounds = m_vertexBuffer.GetBounds2D();
        auto const pos = GetPosition();

        return { bounds.x + pos.x, bounds.y + pos.y, bounds.z + pos.x, bounds.w + pos.y };
    }

    void AnimatedSprite::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        M_Update();

        m_texture->Bind(0);

        m_vertexBuffer.Render(window, shaderProgram, camera, GetTransform());
    }

    void AnimatedSprite::Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        M_Update();

        m_texture->Bind(0);

        m_vertexBuffer.Render(renderLayer, shaderProgram, camera, GetTransform());
    }

    void AnimatedSprite::M_Update() const
    {
        auto const texRect = Vec4f {
            (m_currentFrame % m_framesInRowCount) * m_frameSize.x / m_texture->GetSize().x,
            (m_currentFrame / m_framesInRowCount) * m_frameSize.y / m_texture->GetSize().y,
            m_frameSize.x / m_texture->GetSize().x,
            m_frameSize.y / m_texture->GetSize().y
        };

        auto vertices = m_vertexBuffer.GetData();

        vertices[0] = { { 0.0f, 0.0f, 0.0f }, m_color, { texRect.x, texRect.y + texRect.w } };
        vertices[1] = { { m_frameSize.x, 0.0f, 0.0f }, m_color, { texRect.x + texRect.z, texRect.y + texRect.w } };
        vertices[2] = { { m_frameSize.x, m_frameSize.y, 0.0f }, m_color, { texRect.x + texRect.z, texRect.y } };
        vertices[3] = { { 0.0f, m_frameSize.y, 0.0f }, m_color, { texRect.x, texRect.y } };
    }

    void AnimatedSprite::M_Defaultize()
    {
        m_vertexBuffer = { 4u, {}, PrimitiveType::TriangleFan };
        m_texture = nullptr;
        m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_frameSize = { 0.0f, 0.0f };
        m_currentFrame = 0;
        m_framesInRowCount = 1;
    }
}
