#pragma once

// Esdiel
#include <Esdiel/Utility/AsUnderlying.hpp>

namespace esd
{
    ///
    enum class AnimationState : int32_t
    {
        Basic,
        Special1,
        Special2
    };

    ///
    constexpr auto operator + (AnimationState value)
    {
        return AsUnderlying(value);
    }

    ///
    constexpr auto operator - (AnimationState value)
    {
        return -AsUnderlying(value);
    }
}
