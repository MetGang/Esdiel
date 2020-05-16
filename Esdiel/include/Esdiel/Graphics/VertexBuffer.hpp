#pragma once

// Esdiel
#include <Esdiel/Graphics/PrimitiveType.hpp>
#include <Esdiel/Graphics/Vertex.hpp>

// C++
#include <vector>

namespace esd
{
    //
    class Camera;
    class ShaderProgram;
    class Transform;
    class Window;

    ///
    class VertexBuffer
    {
    public:

        using Vertex_t   = Vertex;
        using Vertices_t = std::vector<Vertex_t>;

        ///
        VertexBuffer() = delete;

        ///
        explicit VertexBuffer(PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(size_t size, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex_t const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(VertexBuffer const&) = delete;

        ///
        VertexBuffer& operator = (VertexBuffer const&) = delete;

        ///
        VertexBuffer(VertexBuffer&& rhs) noexcept;

        ///
        VertexBuffer& operator = (VertexBuffer&& rhs) noexcept;

        ///
        ~VertexBuffer();

        ///
        VertexBuffer& Assign(size_t size, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        void SetVertex(size_t index, Vertex_t const& vertex);

        ///
        Vertex_t& GetVertex(size_t index);

        ///
        Vertex_t const& GetVertex(size_t index) const;

        ///
        void SetPrimitiveType(PrimitiveType type);

        ///
        PrimitiveType GetPrimitiveType() const;

        ///
        Vertex_t* GetData();

        ///
        Vertex_t const* GetData() const;

        ///
        size_t GetVerticesCount() const;

        ///
        size_t GetBytesCount() const;

        ///
        Vec4f GetBounds2D() const;

        ///
        bool IsValid() const;

        ///
        void Bind() const;

        ///
        template <typename TRenderTarget>
        void Render(TRenderTarget const& renderTarget, ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        template <typename TRenderTarget>
        void Render(TRenderTarget const& renderTarget, ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const;

    private:

        ///
        void M_Init();

        ///
        void M_Update() const;

        ///
        void M_Render() const;

        ///
        void M_Defaultize();

        ///
        void M_Destroy();

        Vertices_t m_vertices;
        mutable size_t m_lowerIndex;
        mutable size_t m_upperIndex;
        PrimitiveType m_type;
        uint32_t m_vao;
        uint32_t m_vbo;
        mutable bool m_needsUpdate;
        mutable bool m_needsReallocate;
    };

    template <typename TRenderTarget>
    void VertexBuffer::Render(TRenderTarget const& renderTarget, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            renderTarget.PrepareToRender(shaderProgram, camera);

            M_Render();
        }
    }

    template <typename TRenderTarget>
    void VertexBuffer::Render(TRenderTarget const& renderTarget, ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            renderTarget.PrepareToRender(shaderProgram, camera, transform);

            M_Render();
        }
    }
}
