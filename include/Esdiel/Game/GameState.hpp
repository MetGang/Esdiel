#pragma once

// Esdiel
#include <Esdiel/Utility/AsUnderlying.hpp>

namespace esd
{
    ///
    enum class GameState : int32_t
    {
        Menu,
        InGame,
        GameOver
    };

    ///
    constexpr auto operator + (GameState value)
    {
        return AsUnderlying(value);
    }

    ///
    constexpr auto operator - (GameState value)
    {
        return -AsUnderlying(value);
    }
}
