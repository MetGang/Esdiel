#include <Esdiel/Math/Functions.hpp>

// C++
#include <cmath>

namespace esd
{
    float Lerp(float x, float y, float t) 
    {
        return (x * (1.0f - t)) + (y * t);
    }

    float RadToDeg(float x)
    {
        return x * 180.0f / pi;
    }

    float DegToRad(float x)
    {
        return x * pi / 180.0f;
    }

    float Distance(float x1, float y1, float x2, float y2)
    {
        return std::sqrt(std::pow(x1 - x2, 2.0f) + std::pow(y1 - y2, 2.0f));
    }
}
