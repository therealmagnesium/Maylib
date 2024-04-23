#pragma once
#include "Core/Base.h"

#define LOG_INFO(...) Maylib::Core::Log(Maylib::Core::LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_WARN(...) Maylib::Core::Log(Maylib::Core::LOG_LEVEL_WARN, __VA_ARGS__)
#define LOG_ERROR(...) Maylib::Core::Log(Maylib::Core::LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_FATAL(...) Maylib::Core::Log(Maylib::Core::LOG_LEVEL_FATAL, __VA_ARGS__)

namespace Maylib
{
    namespace Core
    {
        enum LogLevel
        {
            LOG_LEVEL_INFO = 0,
            LOG_LEVEL_WARN,
            LOG_LEVEL_ERROR,
            LOG_LEVEL_FATAL,
        };

        void Log(u8 logLevel, const char* message, ...);
    }
}
