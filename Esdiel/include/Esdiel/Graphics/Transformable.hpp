#pragma once

// Esdiel
#include <Esdiel/Graphics/Transform.hpp>

namespace esd
{
    ///
    class Transformable
    {
    public:

        ///
        Transformable();

        ///
        Transformable(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale);

        ///
        Transformable(Transformable const&) = default;

        ///
        Transformable& operator = (Transformable const&) = default;

        ///
        Transformable(Transformable&& rhs) noexcept = default;

        ///
        Transformable& operator = (Transformable&& rhs) noexcept = default;

        ///
        ~Transformable() = default;

        ///
        void SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale);

        ///
        void TranslatePosition(Vec3f const& offset);

        ///
        void SetPosition(Vec3f const& position);

        ///
        Vec3f const& GetPosition() const;

        ///
        void TranslateOrigin(Vec3f const& offset);

        ///
        void SetOrigin(Vec3f const& origin);

        ///
        Vec3f const& GetOrigin() const;

        ///
        void Rotate(Vec3f const& angle);

        ///
        void SetRotation(Vec3f const& rotation);

        ///
        Vec3f const& GetRotation() const;

        ///
        void Scale(Vec3f const& factor);

        ///
        void SetScale(Vec3f const& scale);

        ///
        Vec3f const& GetScale() const;

        ///
        Transform const& GetTransform() const;

        ///
        Transform GetInverseTransform() const;

    private:

        ///
        void M_UpdateTransform() const;

        Vec3f m_position;
        Vec3f m_origin;
        Vec3f m_rotation;
        Vec3f m_scale;
        mutable Transform m_cachedTransform;
        mutable bool m_needsUpdate;
    };
}
