#version 330 core
layout (location = 0) in vec3 position;

out vec3 texCoords;
uniform mat4 cameraMatrix;

void main()
{
    texCoords = vec3(position.x, position.y, -position.z);
    vec4 pos = cameraMatrix * vec4(position, 1.f);
    gl_Position = pos;
}
