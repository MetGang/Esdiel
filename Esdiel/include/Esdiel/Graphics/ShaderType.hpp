#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    enum class ShaderType : int32_t
    {
        Vertex,
        Geometry,
        Fragment,
        TessControl,
        TessEvaluation,
        Compute
    };

    namespace impl
    {
        ///
        int32_t GetNativeHandle(ShaderType type) noexcept;
    }
}
