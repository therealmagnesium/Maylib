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

        class Math
        {
        public:
            static float Clampf(float f, float max, float min = 0.f)
            {
                float newFloat = f;

                if (f > max)
                    newFloat = max;

                if (f < min)
                    newFloat = min;

                return newFloat;
            }

            static float Clampfr(float f, float max, float min = 0.f)
            {
                float newFloat = f;

                if (f > max)
                    newFloat = 0.f;

                if (f < min)
                    newFloat = max;

                return newFloat;
            }
        };
    }
}
