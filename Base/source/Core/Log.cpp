#include "Core/Log.h"
#include "Core/Base.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdarg>
#include <string>

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

        std::string ReadFile(const char* path)
        {
            std::ifstream in(path);
            if (!in)
            {
                LOG_WARN("Can't read file %s!", path);
                return "";
            }

            std::string line;
            std::stringstream stream;

            while (std::getline(in, line))
            {
                stream << line << "\n";
            }

            in.close();

            return stream.str();
        }
    }
}
