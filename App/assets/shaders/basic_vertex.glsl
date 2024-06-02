#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

out vec3 currentPosition;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

void main()
{
    position = aPosition;
    texCoord = aTexCoord;
    normal = aNormal;

    currentPosition = vec3(modelMatrix * vec4(position, 1.f));
    gl_Position = cameraMatrix * vec4(currentPosition, 1.f);
}
