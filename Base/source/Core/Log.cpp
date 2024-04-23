#include "Core/Log.h"
#include "Core/Base.h"
#include <stdio.h>
#include <cstdarg>

namespace Maylib
{
    namespace Core
    {
        void Log(u8 logLevel, const char* format, ...)
        {
            va_list args;

            switch (logLevel)
            {
                case LOG_LEVEL_INFO:
                {
                    va_start(args, format);
                    {
                        printf("[Info] ");
                        vprintf(format, args);
                        printf("\n");
                    }
                    va_end(args);

                    break;
                }

                case LOG_LEVEL_WARN:
                {
                    va_start(args, format);
                    {
                        printf("[Warn] ");
                        vprintf(format, args);
                        printf("\n");
                    }
                    va_end(args);

                    break;
                }

                case LOG_LEVEL_ERROR:
                {
                    va_start(args, format);
                    {
                        printf("[Error] ");
                        vprintf(format, args);
                        printf("\n");
                    }
                    va_end(args);

                    break;
                }

                case LOG_LEVEL_FATAL:
                {
                    va_start(args, format);
                    {
                        printf("[Fatal] ");
                        vprintf(format, args);
                        printf("\n");
                    }
                    va_end(args);

                    break;
                }

                default:
                    break;
            }
        }
    }
}
