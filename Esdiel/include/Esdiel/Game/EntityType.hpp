#pragma once

// Esdiel
#include <Esdiel/Utility/AsUnderlying.hpp>

namespace esd
{
    ///
    enum class EntityType : int32_t
    {
        Player,

        Static,
        Follower,
        Stealth,
        Fatty,
        Mouser,
        Madman,
        Eater,
        Guardian,

        COUNT
    };

    ///
    constexpr auto operator + (EntityType value)
    {
        return AsUnderlying(value);
    }

    ///
    constexpr auto operator - (EntityType value)
    {
        return -AsUnderlying(value);
    }
}
