#version 330 core
out vec4 fragColor;

in vec3 vsPosition;
in vec2 vsTexCoord;

uniform sampler2D diffuse1;

void main()
{
    fragColor = texture2D(diffuse1, vsTexCoord);
    //fragColor = vec4(0.2, 0.8, 0.6, 1);
}
