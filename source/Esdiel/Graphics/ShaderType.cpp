#include <Esdiel/Graphics/ShaderType.hpp>

// glad
#include <glad/glad.h>

namespace esd
{
    namespace impl
    {
        int32_t GetNativeHandle(ShaderType type) noexcept
        {
            switch (type)
            {
                case ShaderType::Vertex:         return GL_VERTEX_SHADER;
                case ShaderType::Geometry:       return GL_GEOMETRY_SHADER;
                case ShaderType::Fragment:       return GL_FRAGMENT_SHADER;
                case ShaderType::TessControl:    return GL_TESS_CONTROL_SHADER;
                case ShaderType::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
                case ShaderType::Compute:        return GL_COMPUTE_SHADER;
            }

            ESD_JUST_ASSERT("Invalid ShaderType value");

            return -1;
        }
    }
}
