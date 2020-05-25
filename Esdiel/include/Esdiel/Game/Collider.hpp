#pragma once

// Esdiel
#include <Esdiel/Math/Vector.hpp>

namespace esd
{
    ///
    class Collider
    {
    public:

        ///
        Collider();

        ///
        Collider(Collider const&) = default;

        ///
        Collider& operator = (Collider const&) = default;

        ///
        Collider(Collider&& rhs) noexcept = default;

        ///
        Collider& operator = (Collider&& rhs) noexcept = default;

        ///
        ~Collider() = default;

        ///
        void SetPosition(Vec2f const& position);

        ///
        Vec2f const& GetPosition() const;

        ///
        void SetRadius(float radius);

        ///
        float GetRadius() const;

        ///
        bool CollidesWith(Collider const& other) const;

    private:

        Vec2f m_position;
        float m_radius;
    };
}
