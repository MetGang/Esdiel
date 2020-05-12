#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    class Color
    {
    public:

        ///
        Color() noexcept;

        ///
        explicit Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept;

        ///
        explicit Color(uint32_t packed) noexcept;

        ///
        Color(Color const&) noexcept = default;

        ///
        Color& operator = (Color const&) noexcept = default;

        ///
        Color(Color&& rhs) noexcept = default;

        ///
        Color& operator = (Color&& rhs) noexcept = default;

        ///
        ~Color() noexcept = default;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
}
