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

    /// Computes distance between two pints
    constexpr float Distance(float x1, float y1, float x2, float y2)
    {
        return std::sqrt(std::pow(x1 - x2, 2.0f) + std::pow(y1 - y2, 2.0f));
    }
}
