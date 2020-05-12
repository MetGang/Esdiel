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
        Color();

        ///
        explicit Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        ///
        explicit Color(uint32_t packed);

        ///
        Color(Color const&) = default;

        ///
        Color& operator = (Color const&) = default;

        ///
        Color(Color&& rhs) noexcept = default;

        ///
        Color& operator = (Color&& rhs) noexcept = default;

        ///
        ~Color() = default;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
}
