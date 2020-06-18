#include <Esdiel/Graphics/RenderLayer.hpp>

// Esdiel
#include <Esdiel/Graphics/Camera.hpp>
#include <Esdiel/Graphics/ShaderProgram.hpp>
#include <Esdiel/Graphics/Window.hpp>

// glad
#include <glad/glad.h>

namespace esd
{
    RenderLayer::RenderLayer()
        : m_vertexBuffer { 4u, {}, PrimitiveType::TriangleFan }
        , m_texture {}
        , m_fbo { 0 }
        , m_color { 1.0f, 1.0f, 1.0f, 1.0f }
    {
        M_Init();
    }

    RenderLayer::RenderLayer(RenderLayer&& rhs) noexcept
        : m_vertexBuffer { std::move(rhs.m_vertexBuffer) }
        , m_texture { std::move(rhs.m_texture) }
        , m_fbo { rhs.m_fbo }
        , m_color { rhs.m_color }
    {
        
    }

    RenderLayer& RenderLayer::operator = (RenderLayer&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_vertexBuffer = std::move(rhs.m_vertexBuffer);
            m_texture = std::move(rhs.m_texture);
            m_fbo = rhs.m_fbo;
            m_color = rhs.m_color;
        }

        return *this;
    }

    RenderLayer::~RenderLayer()
    {
        M_Destroy();
    }

    bool RenderLayer::Create(Vec2u const& size)
    {
        if (m_texture.Create(size))
        {
            Bind();

            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.GetNativeHandle(), 0);

            return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
        }

        return false;
    }

    void RenderLayer::SetColor(Vec4f const& color)
    {
        m_color = color;
    }

    Vec4f const& RenderLayer::GetColor() const
    {
        return m_color;
    }

    Vec2u const& RenderLayer::GetSize() const
    {
        return m_texture.GetSize();
    }

    Vec2u RenderLayer::GetSizeHalved() const
    {
        return m_texture.GetSizeHalved();
    }

    bool RenderLayer::IsValid() const
    {
        return m_texture.IsValid() && m_fbo;
    }

    void RenderLayer::Bind() const
    {
        if (m_fbo)
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
            glViewport(0, 0, m_texture.GetSize().x, m_texture.GetSize().y);
        }
    }

    void RenderLayer::Clear(Vec4f const& color) const
    {
        Bind();

        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderLayer::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        Bind();

        glViewport(0, 0, m_texture.GetSize().x, m_texture.GetSize().y);

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_texture.GetSize());
        mvp *= camera.GetViewMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void RenderLayer::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        Bind();

        glViewport(0, 0, m_texture.GetSize().x, m_texture.GetSize().y);

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_texture.GetSize());
        mvp *= camera.GetViewMatrix();
        mvp *= transform.GetMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void RenderLayer::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        M_Update();

        m_texture.Bind(0);

        m_vertexBuffer.Render(window, shaderProgram, camera, GetTransform());
    }

    void RenderLayer::M_Init()
    {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    }

    void RenderLayer::M_Update() const
    {
        auto vertices = m_vertexBuffer.GetData();

        vertices[0] = { { 0.0f, 0.0f, 0.0f }, m_color, { 0.0f, 0.0f } };
        vertices[1] = { { m_texture.GetSize().x, 0.0f, 0.0f }, m_color, { 1.0f, 0.0f } };
        vertices[2] = { { m_texture.GetSize().x, m_texture.GetSize().y, 0.0f }, m_color, { 1.0f, 1.0f } };
        vertices[3] = { { 0.0f, m_texture.GetSize().y, 0.0f }, m_color, { 0.0f, 1.0f } };
    }

    void RenderLayer::M_Destroy()
    {
        glDeleteFramebuffers(1, &m_fbo);
    }
}
