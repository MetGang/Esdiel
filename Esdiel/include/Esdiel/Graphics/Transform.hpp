#pragma once

// Esdiel
#include <Esdiel/Math/Matrix.hpp>
#include <Esdiel/Math/Vector.hpp>

namespace esd
{
    ///
    class Transform
    {
    public:

        ///
        Transform() noexcept = default;

        ///
        explicit Transform(float value) noexcept;

        ///
        explicit Transform(Mat4x4f const& matrix) noexcept;

        ///
        Transform(Transform const&) noexcept = default;

        ///
        Transform& operator = (Transform const&) noexcept = default;

        ///
        Transform(Transform&& rhs) noexcept = default;

        ///
        Transform& operator = (Transform&& rhs) noexcept = default;

        ///
        ~Transform() noexcept = default;

        ///
        Transform& SetZero() noexcept;

        ///
        Transform& SetIdentity() noexcept;

        ///
        Transform& SetMatrix(Mat4x4f const& matrix) noexcept;

        ///
        Transform& Translate(Vec3f const& offset) noexcept;

        ///
        Transform& Rotate(Vec3f const& angle) noexcept;

        ///
        Transform& Scale(Vec3f const& factor) noexcept;

        ///
        Transform& Inverse() noexcept;

        ///
        Transform& Combine(Transform const& transform) noexcept;

        ///
        Transform& Combine(Mat4x4f const& matrix) noexcept;

        ///
        Transform Translated(Vec3f const& offset) noexcept;

        ///
        Transform Rotated(Vec3f const& angle) noexcept;

        ///
        Transform Scaled(Vec3f const& factor) noexcept;

        ///
        Transform Inversed() noexcept;

        ///
        Transform Combined(Transform const& transform) noexcept;

        ///
        Transform Combined(Mat4x4f const& matrix) noexcept;

        ///
        Mat4x4f const& GetMatrix() const noexcept;

    private:

        Mat4x4f m_matrix;
    };
}
