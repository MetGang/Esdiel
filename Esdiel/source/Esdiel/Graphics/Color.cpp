#include <Esdiel/Graphics/Color.hpp>

namespace esd
{
    Color::Color()
        : r { 0 }
        , g { 0 }
        , b { 0 }
        , a { 255 }
    {

    }

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r { r }
        , g { g }
        , b { b }
        , a { a }
    {

    }

    Color::Color(uint32_t packed)
        : r { (packed >> 24) & 0xff }
        , g { (packed >> 16) & 0xff }
        , b { (packed >> 8) & 0xff }
        , a { (packed >> 0) & 0xff }
    {

    }
}
