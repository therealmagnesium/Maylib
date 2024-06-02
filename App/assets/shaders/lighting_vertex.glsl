#version 330 core
layout (location = 0) in vec3 aPosition;

out vec3 position;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

void main()
{
    position = aPosition;
    gl_Position = cameraMatrix * modelMatrix * vec4(position, 1.f);
}
