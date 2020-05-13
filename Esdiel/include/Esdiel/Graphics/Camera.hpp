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
        Camera() noexcept;

        ///
        Camera(Camera const&) = delete;

        ///
        Camera& operator = (Camera const&) = delete;

        ///
        Camera(Camera&&) = delete;

        ///
        Camera& operator = (Camera&&) = delete;

        ///
        ~Camera() noexcept = default;

        ///
        Mat4x4f GetViewMatrix() const noexcept;

        ///
        Mat4x4f GetProjectionMatrix(Vec2u const& targetSize) const noexcept;

    private:

        Vec3f m_position;
    };
}
