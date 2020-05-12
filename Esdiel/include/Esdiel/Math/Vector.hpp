#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    template <size_t vSize, typename T>
    class Vector
    {
    public:

        using Value_t = T;

        static constexpr size_t size = vSize;

        ///
        constexpr auto operator[] (size_t index) -> Value_t&
        {
            return data[index];
        }

        ///
        constexpr auto operator[] (size_t index) const -> Value_t const&
        {
            return data[index];
        }

        Value_t data[size];
    };

    template <typename T>
    using Vec2 = Vector<2, T>;

    using Vec2b = Vec2<bool>;
    using Vec2i = Vec2<int32_t>;
    using Vec2u = Vec2<uint32_t>;
    using Vec2s = Vec2<size_t>;
    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;

    template <typename T>
    using Vec3 = Vector<3, T>;

    using Vec3b = Vec3<bool>;
    using Vec3i = Vec3<int32_t>;
    using Vec3u = Vec3<uint32_t>;
    using Vec3s = Vec3<size_t>;
    using Vec3f = Vec3<float>;
    using Vec3d = Vec3<double>;

    template <typename T>
    using Vec4 = Vector<4, T>;

    using Vec4b = Vec4<bool>;
    using Vec4i = Vec4<int32_t>;
    using Vec4u = Vec4<uint32_t>;
    using Vec4s = Vec4<size_t>;
    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
}
