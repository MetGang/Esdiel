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
        Transformable() noexcept;

        ///
        Transformable(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept;

        ///
        Transformable(Transformable const&) noexcept = default;

        ///
        Transformable& operator = (Transformable const&) noexcept = default;

        ///
        Transformable(Transformable&& rhs) noexcept = default;

        ///
        Transformable& operator = (Transformable&& rhs) noexcept = default;

        ///
        ~Transformable() noexcept = default;

        ///
        void SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept;

        ///
        void TranslatePosition(Vec3f const& offset) noexcept;

        ///
        void SetPosition(Vec3f const& position) noexcept;

        ///
        Vec3f const& GetPosition() const noexcept;

        ///
        void TranslateOrigin(Vec3f const& offset) noexcept;

        ///
        void SetOrigin(Vec3f const& origin) noexcept;

        ///
        Vec3f const& GetOrigin() const noexcept;

        ///
        void Rotate(Vec3f const& angle) noexcept;

        ///
        void SetRotation(Vec3f const& rotation) noexcept;

        ///
        Vec3f const& GetRotation() const noexcept;

        ///
        void Scale(Vec3f const& factor) noexcept;

        ///
        void SetScale(Vec3f const& scale) noexcept;

        ///
        Vec3f const& GetScale() const noexcept;

        ///
        Transform const& GetTransform() const noexcept;

        ///
        Transform GetInverseTransform() const noexcept;

    private:

        ///
        void M_UpdateTransform() const noexcept;

        Vec3f m_position;
        Vec3f m_origin;
        Vec3f m_rotation;
        Vec3f m_scale;
        mutable Transform m_cachedTransform;
        mutable bool m_needsUpdate;
    };
}
