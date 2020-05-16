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
    class Sprite : public Transformable
    {
    public:

        ///
        Sprite();

        ///
        Sprite(Sprite const&) = delete;

        ///
        Sprite& operator = (Sprite const&) = delete;

        ///
        Sprite(Sprite&& rhs) noexcept;

        ///
        Sprite& operator = (Sprite&& rhs) noexcept;

        ///
        ~Sprite() = default;

        ///
        void SetTexture(Texture const& texture);

        ///
        Texture const& GetTexture() const;

        ///
        void SetColor(Vec4f const& color);

        ///
        Vec4f const& GetColor() const;

        ///
        void SetTextureRect(Vec4f const& textureRect);

        ///
        Vec4f const& GetTextureRect() const;

        ///
        Vec4f GetLocalBounds() const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const;

    private:

        ///
        void M_Update() const;

        ///
        void M_Defaultize();

        mutable VertexBuffer m_vertexBuffer;
        Texture const* m_texture;
        Vec4f m_color;
        Vec4f m_textureRect;
    };
}
