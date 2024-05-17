#pragma once
#include <glm/glm.hpp>

namespace Maylib
{
    namespace Core
    {
        struct Transform
        {
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale;
        };
    }
}
