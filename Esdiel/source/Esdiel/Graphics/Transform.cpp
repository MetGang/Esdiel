#include <Esdiel/Graphics/Transform.hpp>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace esd
{
    Transform::Transform(float value)
        : m_matrix { value }
    {

    }

    Transform::Transform(Mat4x4f const& matrix)
        : m_matrix { matrix }
    {

    }

    Transform& Transform::SetZero()
    {
        m_matrix = Mat4x4f{ 0.0f };

        return *this;
    }

    Transform& Transform::SetIdentity()
    {
        m_matrix = Mat4x4f{ 1.0f };

        return *this;
    }

    Transform& Transform::SetMatrix(Mat4x4f const& matrix)
    {
        m_matrix = matrix;

        return *this;
    }

    Transform& Transform::Translate(Vec3f const& offset)
    {
        m_matrix = glm::translate(m_matrix, offset);

        return *this;
    }

    Transform& Transform::Rotate(Vec3f const& angle)
    {
        // TODO remove gimbal lock, change to quaternions
        m_matrix = glm::rotate(m_matrix, angle.x, { 1.0f, 0.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.y, { 0.0f, 1.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.z, { 0.0f, 0.0f, 1.0f });

        return *this;
    }

    Transform& Transform::Scale(Vec3f const& factor)
    {
        m_matrix = glm::scale(m_matrix, factor);

        return *this;
    }

    Transform& Transform::Inverse()
    {
        m_matrix = glm::inverse(m_matrix);

        return *this;
    }

    Transform& Transform::Combine(Transform const& transform)
    {
        m_matrix *= transform.GetMatrix();

        return *this;
    }

    Transform& Transform::Combine(Mat4x4f const& matrix)
    {
        m_matrix *= matrix;

        return *this;
    }

    Transform Transform::Translated(Vec3f const& offset)
    {
        return Transform{ *this }.Translate(offset);
    }

    Transform Transform::Scaled(Vec3f const& factor)
    {
        return Transform{ *this }.Scale(factor);
    }

    Transform Transform::Rotated(Vec3f const& angle)
    {
        return Transform{ *this }.Rotate(angle);
    }

    Transform Transform::Inversed()
    {
        return Transform{ *this }.Inverse();
    }

    Transform Transform::Combined(Transform const& transform)
    {
        return Transform{ *this }.Combine(transform);
    }

    Transform Transform::Combined(Mat4x4f const& matrix)
    {
        return Transform{ *this }.Combine(matrix);
    }

    Mat4x4f const& Transform::GetMatrix() const
    {
        return m_matrix;
    }
}
