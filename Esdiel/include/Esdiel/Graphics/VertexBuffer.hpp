#pragma once

// Esdiel
#include <Esdiel/Graphics/PrimitiveType.hpp>
#include <Esdiel/Graphics/Vertex.hpp>

// C++
#include <vector>

namespace esd
{
    //
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
        ~VertexBuffer() noexcept;

        ///
        VertexBuffer& Assign(size_t size, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        void SetVertex(size_t index, Vertex_t const& vertex) noexcept;

        ///
        Vertex_t& GetVertex(size_t index) noexcept;

        ///
        Vertex_t const& GetVertex(size_t index) const noexcept;

        ///
        void SetPrimitiveType(PrimitiveType type) noexcept;

        ///
        PrimitiveType GetPrimitiveType() const noexcept;

        ///
        Vertex_t* GetData() noexcept;

        ///
        Vertex_t const* GetData() const noexcept;

        ///
        size_t GetVerticesCount() const noexcept;

        ///
        size_t GetBytesCount() const noexcept;

        ///
        Vec4f GetBounds2D() const noexcept;

        ///
        bool IsValid() const noexcept;

        ///
        void Bind() const noexcept;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram) const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Transform const& transform) const;

    private:

        ///
        void M_Init() noexcept;

        ///
        void M_Update() const noexcept;

        ///
        void M_Render() const noexcept;

        ///
        void M_Defaultize() noexcept;

        ///
        void M_Destroy() noexcept;

        Vertices_t m_vertices;
        mutable size_t m_lowerIndex;
        mutable size_t m_upperIndex;
        PrimitiveType m_type;
        uint32_t m_vao;
        uint32_t m_vbo;
        mutable bool m_needsUpdate;
        mutable bool m_needsReallocate;
    };
}
