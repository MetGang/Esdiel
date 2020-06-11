#include <Esdiel/Game/Collider.hpp>

// C++
#include <cmath>

namespace esd
{
    Collider::Collider()
        : m_position { 0.0f, 0.0f }
        , m_radius { 0.0f }
    {

    }

    void Collider::SetPosition(Vec2f const& position)
    {
        m_position = position;
    }

    Vec2f const& Collider::GetPosition() const
    {
        return m_position;
    }

    void Collider::SetRadius(float radius)
    {
        m_radius = radius;
    }

    float Collider::GetRadius() const
    {
        return m_radius;
    }

    bool Collider::CollidesWith(Collider const& other) const
    {
        auto const dx = m_position.x - other.m_position.x;
        auto const dy = m_position.y - other.m_position.y;

        return (dx * dx + dy * dy) < std::pow(m_radius + other.m_radius, 2.0f);
    }
}
