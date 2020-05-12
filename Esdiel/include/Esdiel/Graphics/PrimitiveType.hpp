#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    enum class PrimitiveType : int32_t
    {
        Points,
        Lines,
        LineLoop,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan
    };

    namespace impl
    {
        ///
        int32_t GetNativeHandle(PrimitiveType type) noexcept;
    }
}
