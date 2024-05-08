#pragma once
#define ELEMENTS_PER_VERTEX 8 // 3 position, 3 normal, 2 uv
#define VERTEX_POS_OFFSET offsetof(Vertex, position)
#define VERTEX_NORMAL_OFFSET offsetof(Vertex, normal)
#define VERTEX_UV_OFFSET offsetof(Vertex, texCoords)

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Maylib
{
    namespace Core
    {
        struct Vertex
        {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 texCoords;
        };
    }
}
