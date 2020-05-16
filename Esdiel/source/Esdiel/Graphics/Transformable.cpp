#include <Esdiel/Graphics/Transformable.hpp>

// C++
#include <string>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>

namespace esd
{
    Transformable::Transformable()
        : m_position { 0.0f, 0.0f, 0.0f }
        , m_origin { 0.0f, 0.0f, 0.0f }
        , m_rotation { 0.0f, 0.0f, 0.0f }
        , m_scale { 1.0f, 1.0f, 1.0f }
        , m_cachedTransform { 1.0f }
        , m_needsUpdate { false }
    {

    }

    Transformable::Transformable(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale)
        : m_position { position }
        , m_origin { origin }
        , m_rotation { rotation }
        , m_scale { scale }
        , m_cachedTransform {}
        , m_needsUpdate { true }
    {
        
    }

    void Transformable::SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale)
    {
        m_position = position;
        m_origin = origin;
        m_rotation = rotation;
        m_scale = scale;

        m_needsUpdate = true;
    }

    void Transformable::TranslatePosition(Vec3f const& offset)
    {
        m_position += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetPosition(Vec3f const& position) 
    {
        m_position = position;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetPosition() const
    {
        return m_position;
    }

    void Transformable::TranslateOrigin(Vec3f const& offset)
    {
        m_origin += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetOrigin(Vec3f const& origin)
    {
        m_origin = origin;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetOrigin() const
    {
        return m_origin;
    }

    void Transformable::Rotate(Vec3f const& angle)
    {
        m_rotation += angle;

        m_needsUpdate = true;
    }

    void Transformable::SetRotation(Vec3f const& rotation)
    {
        m_rotation = rotation;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetRotation() const
    {
        return m_rotation;
    }

    void Transformable::Scale(Vec3f const& factor)
    {
        m_scale *= factor;

        m_needsUpdate = true;
    }

    void Transformable::SetScale(Vec3f const& scale)
    {
        m_scale = scale;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetScale() const
    {
        return m_scale;
    }

    Transform const& Transformable::GetTransform() const
    {
        M_UpdateTransform();

        return m_cachedTransform;
    }

    Transform Transformable::GetInverseTransform() const
    {
        M_UpdateTransform();

        return m_cachedTransform.Inversed();
    }

    void Transformable::M_UpdateTransform() const
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
