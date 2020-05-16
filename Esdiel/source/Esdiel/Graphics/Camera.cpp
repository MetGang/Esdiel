#include <Esdiel/Graphics/Camera.hpp>

// C++
#include <string>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace esd
{
    Camera::Camera()
        : m_position { 0.0f, 0.0f, 0.0f }
    {

    }

    Mat4x4f Camera::GetViewMatrix() const
    {
        return Mat4x4f{ 1.0f };
    }

    Mat4x4f Camera::GetProjectionMatrix(Vec2u const& targetSize) const
    {
        return glm::ortho(0.0f + m_position.x, targetSize.x + m_position.x, 0.0f + m_position.y, targetSize.y + m_position.y, -1.0f, 1.0f);
    }
}
