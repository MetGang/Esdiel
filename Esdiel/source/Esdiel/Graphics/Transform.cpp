#include <Esdiel/Graphics/Transform.hpp>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace esd
{
    Transform::Transform(float value) noexcept
        : m_matrix { value }
    {

    }

    Transform::Transform(Mat4x4f const& matrix) noexcept
        : m_matrix { matrix }
    {

    }

    Transform& Transform::SetZero() noexcept
    {
        m_matrix = Mat4x4f{ 0.0f };

        return *this;
    }

    Transform& Transform::SetIdentity() noexcept
    {
        m_matrix = Mat4x4f{ 1.0f };

        return *this;
    }

    Transform& Transform::SetMatrix(Mat4x4f const& matrix) noexcept
    {
        m_matrix = matrix;

        return *this;
    }

    Transform& Transform::Translate(Vec3f const& offset) noexcept
    {
        m_matrix = glm::translate(m_matrix, offset);

        return *this;
    }

    Transform& Transform::Rotate(Vec3f const& angle) noexcept
    {
        // TODO remove gimbal lock, change to quaternions
        m_matrix = glm::rotate(m_matrix, angle.x, { 1.0f, 0.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.y, { 0.0f, 1.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.z, { 0.0f, 0.0f, 1.0f });

        return *this;
    }

    Transform& Transform::Scale(Vec3f const& factor) noexcept
    {
        m_matrix = glm::scale(m_matrix, factor);

        return *this;
    }

    Transform& Transform::Inverse() noexcept
    {
        m_matrix = glm::inverse(m_matrix);

        return *this;
    }

    Transform& Transform::Combine(Transform const& transform) noexcept
    {
        m_matrix *= transform.GetMatrix();

        return *this;
    }

    Transform& Transform::Combine(Mat4x4f const& matrix) noexcept
    {
        m_matrix *= matrix;

        return *this;
    }

    Transform Transform::Translated(Vec3f const& offset) noexcept
    {
        return Transform{ *this }.Translate(offset);
    }

    Transform Transform::Scaled(Vec3f const& factor) noexcept
    {
        return Transform{ *this }.Scale(factor);
    }

    Transform Transform::Rotated(Vec3f const& angle) noexcept
    {
        return Transform{ *this }.Rotate(angle);
    }

    Transform Transform::Inversed() noexcept
    {
        return Transform{ *this }.Inverse();
    }

    Transform Transform::Combined(Transform const& transform) noexcept
    {
        return Transform{ *this }.Combine(transform);
    }

    Transform Transform::Combined(Mat4x4f const& matrix) noexcept
    {
        return Transform{ *this }.Combine(matrix);
    }

    Mat4x4f const& Transform::GetMatrix() const noexcept
    {
        return m_matrix;
    }
}
