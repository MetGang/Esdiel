#pragma once

// Esdiel
#include <Esdiel/Graphics/VertexBuffer.hpp>
#include <Esdiel/Graphics/Transformable.hpp>

// C++
#include <vector>

namespace esd
{
    //
    class Texture;

    ///
    class AnimatedSprite : public Transformable
    {
    public:

        ///
        AnimatedSprite();

        ///
        AnimatedSprite(AnimatedSprite const&) = delete;

        ///
        AnimatedSprite& operator = (AnimatedSprite const&) = delete;

        ///
        AnimatedSprite(AnimatedSprite&& rhs) noexcept;

        ///
        AnimatedSprite& operator = (AnimatedSprite&& rhs) noexcept;

        ///
        ~AnimatedSprite() = default;

        ///
        void SetTexture(Texture const& texture);

        ///
        Texture const& GetTexture() const;

        ///
        void SetColor(Vec4f const& color);

        ///
        Vec4f const& GetColor() const;

        ///
        void SetFrameSize(Vec2f const& frameSize);

        ///
        Vec2f const& GetFrameSize() const;

        ///
        void SetCurrentFrame(uint32_t index);

        ///
        uint32_t GetCurrentFrame() const;

        ///
        void SetFramesInRowCount(uint32_t count);

        ///
        uint32_t GetramesInRowCount() const;

        ///
        Vec4f GetLocalBounds() const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        void Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera) const;

    private:

        ///
        void M_Update() const;

        ///
        void M_Defaultize();

        mutable VertexBuffer m_vertexBuffer;
        Texture const* m_texture;
        Vec4f m_color;
        Vec2f m_frameSize;
        uint32_t m_currentFrame;
        uint32_t m_framesInRowCount;
    };
}
