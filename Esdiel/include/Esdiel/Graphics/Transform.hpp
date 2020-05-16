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
        Transform() = default;

        ///
        explicit Transform(float value);

        ///
        explicit Transform(Mat4x4f const& matrix);

        ///
        Transform(Transform const&) = default;

        ///
        Transform& operator = (Transform const&) = default;

        ///
        Transform(Transform&& rhs) noexcept = default;

        ///
        Transform& operator = (Transform&& rhs) noexcept = default;

        ///
        ~Transform() = default;

        ///
        Transform& SetZero();

        ///
        Transform& SetIdentity();

        ///
        Transform& SetMatrix(Mat4x4f const& matrix);

        ///
        Transform& Translate(Vec3f const& offset);

        ///
        Transform& Rotate(Vec3f const& angle);

        ///
        Transform& Scale(Vec3f const& factor);

        ///
        Transform& Inverse();

        ///
        Transform& Combine(Transform const& transform);

        ///
        Transform& Combine(Mat4x4f const& matrix);

        ///
        Transform Translated(Vec3f const& offset);

        ///
        Transform Rotated(Vec3f const& angle);

        ///
        Transform Scaled(Vec3f const& factor);

        ///
        Transform Inversed();

        ///
        Transform Combined(Transform const& transform);

        ///
        Transform Combined(Mat4x4f const& matrix);

        ///
        Mat4x4f const& GetMatrix() const;

    private:

        Mat4x4f m_matrix;
    };
}
