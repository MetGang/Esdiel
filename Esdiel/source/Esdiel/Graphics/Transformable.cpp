#include <Esdiel/Graphics/Transformable.hpp>

// C++
#include <string>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>

namespace esd
{
    Transformable::Transformable() noexcept
        : m_position { 0.0f, 0.0f, 0.0f }
        , m_origin { 0.0f, 0.0f, 0.0f }
        , m_rotation { 0.0f, 0.0f, 0.0f }
        , m_scale { 1.0f, 1.0f, 1.0f }
        , m_cachedTransform { 1.0f }
        , m_needsUpdate { false }
    {

    }

    Transformable::Transformable(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept
        : m_position { position }
        , m_origin { origin }
        , m_rotation { rotation }
        , m_scale { scale }
        , m_cachedTransform {}
        , m_needsUpdate { true }
    {
        
    }

    void Transformable::SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept
    {
        m_position = position;
        m_origin = origin;
        m_rotation = rotation;
        m_scale = scale;

        m_needsUpdate = true;
    }

    void Transformable::TranslatePosition(Vec3f const& offset) noexcept
    {
        m_position += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetPosition(Vec3f const& position)  noexcept
    {
        m_position = position;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetPosition() const noexcept
    {
        return m_position;
    }

    void Transformable::TranslateOrigin(Vec3f const& offset) noexcept
    {
        m_origin += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetOrigin(Vec3f const& origin) noexcept
    {
        m_origin = origin;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetOrigin() const noexcept
    {
        return m_origin;
    }

    void Transformable::Rotate(Vec3f const& angle) noexcept
    {
        m_rotation += angle;

        m_needsUpdate = true;
    }

    void Transformable::SetRotation(Vec3f const& rotation) noexcept
    {
        m_rotation = rotation;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetRotation() const noexcept
    {
        return m_rotation;
    }

    void Transformable::Scale(Vec3f const& factor) noexcept
    {
        m_scale *= factor;

        m_needsUpdate = true;
    }

    void Transformable::SetScale(Vec3f const& scale) noexcept
    {
        m_scale = scale;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetScale() const noexcept
    {
        return m_scale;
    }

    Transform const& Transformable::GetTransform() const noexcept
    {
        M_UpdateTransform();

        return m_cachedTransform;
    }

    Transform Transformable::GetInverseTransform() const noexcept
    {
        M_UpdateTransform();

        return m_cachedTransform.Inversed();
    }

    void Transformable::M_UpdateTransform() const noexcept
    {
        if (m_needsUpdate)
        {
            m_cachedTransform
                .SetIdentity()
                .Translate(m_position)
                .Rotate(m_rotation)
                .Scale(m_scale)
                .Translate(-m_origin);

            m_needsUpdate = false;
        }
    }
}
