#include "Core/Time.h"

namespace Maylib
{
    namespace Core
    {
        float Time::s_deltaTime = 0.f;
        float Time::s_prevTime = 0.f;
        u16 Time::s_targetFPS = 30;

        Time::Time() {}
    }
}
