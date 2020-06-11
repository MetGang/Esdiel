#pragma once

// Esdiel
#include <Esdiel/Math/Vector.hpp>

namespace esd
{
    ///
    struct Vertex
    {
        Vec3f position = { 0.0f, 0.0f, 0.0f };
        Vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };
        Vec2f texCoord = { 0.0f, 0.0f };
    };
}
