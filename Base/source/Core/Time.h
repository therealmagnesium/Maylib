#pragma once
#include "Core/Base.h"

namespace Maylib
{
    namespace Core
    {
        class Time
        {
        public:
            Time();

            static inline float GetElapsed() { return s_deltaTime; }

        private:
            static float s_deltaTime;
            static float s_prevTime;
            static u16 s_targetFPS;

        private:
            friend class Application;
        };
    }
}
