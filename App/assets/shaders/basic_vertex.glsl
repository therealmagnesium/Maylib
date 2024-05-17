#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 vsPosition;
out vec2 vsTexCoord;

uniform mat4 modelMatrix;
uniform mat4 camMatrix;

void main()
{
    vsPosition = position;
    vsTexCoord = texCoord;
    gl_Position = camMatrix * modelMatrix * vec4(position, 1.0);
}
