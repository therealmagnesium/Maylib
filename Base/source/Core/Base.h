#pragma once
#include <memory>
#include <stdint.h>
#include <utility>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define V2_FMT "<%.3f, %.3f>"
#define V3_FMT "<%.3f, %.3f, %.3f>"

#define V2_OPEN(v) v.x, v.y
#define V3_OPEN(v) v.x, v.y, v.z

#define LEN(array) sizeof(array) / sizeof(array[0])

namespace Maylib
{
    namespace Core
    {
        template <typename T> using Scope = std::unique_ptr<T>;
        template <typename T> using Ref = std::shared_ptr<T>;

        template <typename T, typename... Args> Scope<T> CreateScope(Args&&... args)
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }

        template <typename T, typename... Args> Ref<T> CreateRef(Args&&... args)
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
    }
}
