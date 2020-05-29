#pragma once

// Esdiel
#include <Esdiel/Utility/AsUnderlying.hpp>

namespace esd
{
    ///
    enum class EntityType : int32_t
    {
        Player,
        Enemy,
        Bonus,

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

    ///
    enum class BonusType : int32_t
    {
        Regular,
        Good,

        COUNT
    };
    
    ///
    constexpr auto operator + (BonusType value)
    {
        return AsUnderlying(value);
    }

    ///
    constexpr auto operator - (BonusType value)
    {
        return -AsUnderlying(value);
    }

    ///
    enum class EnemyType : int32_t
    {
        Static,
        Follower,
        Stealth,
        Fatty,
        Mouser,
        Madman,
        Eater,

        COUNT
    };

    ///
    constexpr auto operator + (EnemyType value)
    {
        return AsUnderlying(value);
    }

    ///
    constexpr auto operator - (EnemyType value)
    {
        return -AsUnderlying(value);
    }

    union EntitySubType
    {
        EnemyType e;
        BonusType b;
    };
}
