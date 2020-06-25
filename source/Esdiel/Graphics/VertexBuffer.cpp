#include <Esdiel/Graphics/VertexBuffer.hpp>

// Esdiel
#include <Esdiel/Graphics/Camera.hpp>
#include <Esdiel/Graphics/RenderLayer.hpp>
#include <Esdiel/Graphics/ShaderProgram.hpp>
#include <Esdiel/Graphics/Transform.hpp>
#include <Esdiel/Graphics/Window.hpp>
#include <Esdiel/Utility/OffsetOf.hpp>

// C++
#include <algorithm>
#include <utility>

// glad
#include <glad/glad.h>

namespace esd
{
    inline constexpr size_t minIndex = 0;
    inline constexpr size_t maxIndex = static_cast<size_t>(-1);

    VertexBuffer::VertexBuffer(PrimitiveType type)
        : m_vertices {}
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { true }
        , m_needsReallocate { true }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(size_t size, Vertex_t const& vertex, PrimitiveType type)
        : m_vertices { size, vertex }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { true }
        , m_needsReallocate { true }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type)
        : m_vertices { begin, end }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { true }
        , m_needsReallocate { true }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(Vertex_t const* vertices, size_t size, PrimitiveType type)
        : VertexBuffer { vertices, vertices + size, type }
    {
        
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& rhs) noexcept
        : m_vertices { std::move(rhs.m_vertices) }
        , m_lowerIndex { rhs.m_lowerIndex }
        , m_upperIndex { rhs.m_upperIndex }
        , m_type { rhs.m_type }
        , m_vao { rhs.m_vao }
        , m_vbo { rhs.m_vbo }
        , m_needsUpdate { rhs.m_needsUpdate }
        , m_needsReallocate { rhs.m_needsReallocate }
    {
        
    }

    VertexBuffer& VertexBuffer::operator = (VertexBuffer&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_vertices = std::move(rhs.m_vertices);
            m_lowerIndex = rhs.m_lowerIndex;
            m_upperIndex = rhs.m_upperIndex;
            m_type = rhs.m_type;
            m_vao = rhs.m_vao;
            m_vbo = rhs.m_vbo;
            m_needsUpdate = rhs.m_needsUpdate;
            m_needsReallocate = rhs.m_needsReallocate;
        }

        return *this;
    }

    VertexBuffer::~VertexBuffer()
    {
        M_Destroy();
    }

    VertexBuffer& VertexBuffer::Assign(size_t size, Vertex_t const& vertex, PrimitiveType type)
    {
        return *this = VertexBuffer{ size, vertex, type };
    }

    VertexBuffer& VertexBuffer::Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type)
    {
        return *this = VertexBuffer{ begin, end, type };
    }

    VertexBuffer& VertexBuffer::Assign(Vertex_t const* vertices, size_t size, PrimitiveType type)
    {
        return *this = VertexBuffer{ vertices, size, type };
    }

    void VertexBuffer::SetVertex(size_t index, Vertex_t const& vertex)
    {
        m_vertices[index] = vertex;

        m_lowerIndex = std::min(m_lowerIndex, index);
        m_upperIndex = std::max(m_upperIndex, index);

        m_needsUpdate = true;
    }

    VertexBuffer::Vertex_t& VertexBuffer::GetVertex(size_t index)
    {
        m_lowerIndex = std::min(m_lowerIndex, index);
        m_upperIndex = std::max(m_upperIndex, index);

        m_needsUpdate = true;

        return m_vertices[index];
    }

    VertexBuffer::Vertex_t const& VertexBuffer::GetVertex(size_t index) const
    {
        return m_vertices[index];
    }

    void VertexBuffer::SetPrimitiveType(PrimitiveType type)
    {
        m_type = type;
    }

    PrimitiveType VertexBuffer::GetPrimitiveType() const
    {
        return m_type;
    }

    VertexBuffer::Vertex_t* VertexBuffer::GetData()
    {
        m_needsUpdate = true;

        m_lowerIndex = minIndex;
        m_upperIndex = m_vertices.size() - 1;

        return m_vertices.empty() ? nullptr : m_vertices.data();
    }

    VertexBuffer::Vertex_t const* VertexBuffer::GetData() const
    {
        return m_vertices.empty() ? nullptr : m_vertices.data();
    }

    size_t VertexBuffer::GetVerticesCount() const
    {
        return m_vertices.size();
    }

    size_t VertexBuffer::GetBytesCount() const
    {
        return m_vertices.size() * sizeof(Vertex_t);
    }

    bool VertexBuffer::IsValid() const
    {
        return m_vao && m_vbo;
    }

    Vec4f VertexBuffer::GetBounds2D() const
    {
        if (!m_vertices.empty())
        {
            auto left   = m_vertices[0].position.x;
            auto top    = m_vertices[0].position.y;
            auto right  = m_vertices[0].position.x;
            auto bottom = m_vertices[0].position.y;

            for (size_t i = 1; i < m_vertices.size(); ++i)
            {
                auto const pos = m_vertices[i].position;

                if (pos.x < left)
                {
                    left = pos.x;
                }
                else if (pos.x > right)
                {
                    right = pos.x;
                }

                if (pos.y < top)
                {
                    top = pos.y;
                }
                else if (pos.y > bottom)
                {
                    bottom = pos.y;
                }
            }

            return { left, top, right - left, bottom - top };
        }
        else
        {
            return { 0.0f, 0.0f, 0.0f, 0.0f };
        }
    }

    void VertexBuffer::Bind() const
    {
        if (m_vao && m_vbo)
        {
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        }
    }

    void VertexBuffer::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            window.PrepareToRender(shaderProgram, camera);

            M_Render();
        }
    }

    void VertexBuffer::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            window.PrepareToRender(shaderProgram, camera, transform);

            M_Render();
        }
    }

    void VertexBuffer::Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            renderLayer.PrepareToRender(shaderProgram, camera);

            M_Render();
        }
    }

    void VertexBuffer::Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            renderLayer.PrepareToRender(shaderProgram, camera, transform);

            M_Render();
        }
    }

    void VertexBuffer::M_Init()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        Bind();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, decltype(Vertex_t::position)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, decltype(Vertex_t::color)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, decltype(Vertex_t::texCoord)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::texCoord));
    }

    void VertexBuffer::M_Render() const
    {
        Bind();

        M_Update();

        glDrawArrays(impl::GetNativeHandle(m_type), 0, m_vertices.size());
    }

    void VertexBuffer::M_Update() const
    {
        if (m_needsUpdate)
        {
            if (m_needsReallocate)
            {
                glBufferData(GL_ARRAY_BUFFER, GetBytesCount(), GetData(), GL_DYNAMIC_DRAW);

                m_needsReallocate = false;
            }
            else
            {
                GLintptr const offset = sizeof(Vertex_t) * m_lowerIndex;
                GLsizeiptr const size = sizeof(Vertex_t) * (m_upperIndex - m_lowerIndex + 1);

                glBufferSubData(GL_ARRAY_BUFFER, offset, size, GetData() + m_lowerIndex);
            }

            m_lowerIndex = maxIndex;
            m_upperIndex = minIndex;

            m_needsUpdate = false;
        }
    }

    void VertexBuffer::M_Destroy()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);

        m_vertices.clear();
    }
}
