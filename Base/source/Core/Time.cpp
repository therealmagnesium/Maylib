#include "Core/Time.h"

namespace Maylib
{
    namespace Core
    {
        float Time::s_deltaTime = 0.f;
        float Time::s_lastFrameTime = 0.f;
        u16 Time::s_targetFPS = 60;

        Time::Time() {}
    }
}
