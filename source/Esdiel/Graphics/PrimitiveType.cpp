#include <Esdiel/Graphics/PrimitiveType.hpp>

// glad
#include <glad/glad.h>

namespace esd
{
    namespace impl
    {
        int32_t GetNativeHandle(PrimitiveType type) noexcept
        {
            switch (type)
            {
                case PrimitiveType::Points:        return GL_POINTS;
                case PrimitiveType::Lines:         return GL_LINES;
                case PrimitiveType::LineLoop:      return GL_LINE_LOOP;
                case PrimitiveType::LineStrip:     return GL_LINE_STRIP;
                case PrimitiveType::Triangles:     return GL_TRIANGLES;
                case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
                case PrimitiveType::TriangleFan:   return GL_TRIANGLE_FAN;
            }

            ESD_JUST_ASSERT("Invalid PrimitiveType value");

            return -1;
        }
    }
}
