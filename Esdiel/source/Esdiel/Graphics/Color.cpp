#include <Esdiel/Graphics/Color.hpp>

namespace esd
{
    Color::Color() noexcept
        : r { 0 }
        , g { 0 }
        , b { 0 }
        , a { 255 }
    {

    }

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
        : r { r }
        , g { g }
        , b { b }
        , a { a }
    {

    }

    Color::Color(uint32_t packed) noexcept
        : r { static_cast<uint8_t>((packed >> 24) & 0xff) }
        , g { static_cast<uint8_t>((packed >> 16) & 0xff) }
        , b { static_cast<uint8_t>((packed >> 8) & 0xff) }
        , a { static_cast<uint8_t>((packed >> 0) & 0xff) }
    {

    }
}
