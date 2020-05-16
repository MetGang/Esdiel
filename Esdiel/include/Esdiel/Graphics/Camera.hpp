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
        Camera(Camera const&) = delete;

        ///
        Camera& operator = (Camera const&) = delete;

        ///
        Camera(Camera&&) = delete;

        ///
        Camera& operator = (Camera&&) = delete;

        ///
        ~Camera() = default;

        ///
        Mat4x4f GetViewMatrix() const;

        ///
        Mat4x4f GetProjectionMatrix(Vec2u const& targetSize) const;

    private:

        Vec3f m_position;
    };
}
