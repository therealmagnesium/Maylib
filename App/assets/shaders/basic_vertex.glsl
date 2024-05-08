#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 vsPosition;
out vec2 vsTexCoord;

void main()
{
    vsPosition = position;
    vsTexCoord = texCoord;
    gl_Position = vec4(position, 1.0);
}
