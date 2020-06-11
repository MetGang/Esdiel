#pragma once

// Esdiel
#include <Esdiel/Math/Matrix.hpp>
#include <Esdiel/Math/Vector.hpp>

namespace esd
{
    ///
    class Camera
    {
    public:

        ///
        Camera();

        ///
        Camera(Camera const&) = default;

        ///
        Camera& operator = (Camera const&) = default;

        ///
        Camera(Camera&&) noexcept = default;

        ///
        Camera& operator = (Camera&&) noexcept = default;

        ///
        ~Camera() = default;

        ///
        void SetPosition(Vec3f const& position);

        ///
        Vec3f const& GetPosition() const;

        ///
        Mat4x4f GetViewMatrix() const;

        ///
        Mat4x4f GetProjectionMatrix(Vec2u const& targetSize) const;

    private:

        Vec3f m_position;
    };
}
