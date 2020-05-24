#pragma once

// Esdiel
#include <Esdiel/Graphics/Texture.hpp>
#include <Esdiel/Graphics/Transformable.hpp>
#include <Esdiel/Graphics/VertexBuffer.hpp>

namespace esd
{
    //
    class Camera;
    class ShaderProgram;
    class Window;

    ///
    class RenderLayer : public Transformable
    {
    public:

        ///
        RenderLayer();

        ///
        RenderLayer(RenderLayer const&) = delete;

        ///
        RenderLayer& operator = (RenderLayer const&) = delete;

        ///
        RenderLayer(RenderLayer&& rhs) noexcept;

        ///
        RenderLayer& operator = (RenderLayer&& rhs) noexcept;

        ///
        ~RenderLayer();

        ///
        bool Create(Vec2u const& size);

        ///
        void SetColor(Vec4f const& color);

        ///
        Vec4f const& GetColor() const;

        ///
        Vec2u const& GetSize() const;

        ///
        Vec2u GetSizeHalved() const;

        ///
        bool IsValid() const;

        ///
        void Bind() const;

        ///
        void Clear(Vec4f const& color = { 0.0f, 0.0f, 0.0f, 0.0f }) const;

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const;

    private:

        ///
        void M_Init();

        ///
        void M_Update() const;

        ///
        void M_Destroy();

        mutable VertexBuffer m_vertexBuffer;
        Texture m_texture;
        uint32_t m_fbo;
        Vec4f m_color;
    };
}
