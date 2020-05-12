#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    template <typename T>
    struct Vec2
    {
        using Value_t = T;

        static constexpr size_t size = 2;

        union {
            Value_t data[size];
            struct { Value_t x, y; };
        };
    };

    using Vec2b = Vec2<bool>;
    using Vec2i = Vec2<int32_t>;
    using Vec2u = Vec2<uint32_t>;
    using Vec2s = Vec2<size_t>;
    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;

    ///
    template <typename T>
    struct Vec3
    {
        using Value_t = T;

        static constexpr size_t size = 3;

        union {
            Value_t data[size];
            struct { Value_t x, y, z; };
        };
    };

    using Vec3b = Vec3<bool>;
    using Vec3i = Vec3<int32_t>;
    using Vec3u = Vec3<uint32_t>;
    using Vec3s = Vec3<size_t>;
    using Vec3f = Vec3<float>;
    using Vec3d = Vec3<double>;

    ///
    template <typename T>
    struct Vec4
    {
        using Value_t = T;

        static constexpr size_t size = 4;

        union {
            Value_t data[size];
            struct { Value_t x, y, z, w; };
        };
    };

    using Vec4b = Vec4<bool>;
    using Vec4i = Vec4<int32_t>;
    using Vec4u = Vec4<uint32_t>;
    using Vec4s = Vec4<size_t>;
    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
}
