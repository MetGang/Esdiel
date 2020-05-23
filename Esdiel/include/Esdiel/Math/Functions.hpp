#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

// C++
#include <cmath>

namespace esd
{
    constexpr float pi = 3.14159265359f;

    /// Computes linear interpolation between two values
    constexpr float Lerp(float x, float y, float t) 
    {
        return (x * (1.0f - t)) + (y * t);
    }

    /// Converts radians to degrees
    constexpr float RadToDeg(float x)
    {
        return x * 180.0f / pi;
    }

    /// Converts degrees to radians
    constexpr float DegToRad(float x)
    {
        return x * pi / 180.0f;
    }
}
