#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

// C++
#include <type_traits>

namespace esd
{
    ///
    template <typename Enum>
    constexpr auto AsUnderlying(Enum e)
    {
        return static_cast<std::underlying_type_t<Enum>>(e);
    }
}
