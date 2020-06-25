#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    constexpr float pi = 3.14159265359f;

    /// Computes linear interpolation between two values
    float Lerp(float x, float y, float t);

    /// Converts radians to degrees
    float RadToDeg(float x);

    /// Converts degrees to radians
    float DegToRad(float x);

    /// Computes distance between two pints
    float Distance(float x1, float y1, float x2, float y2);
}
