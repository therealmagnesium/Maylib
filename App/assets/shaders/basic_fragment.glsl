#version 460 core
out vec4 fragColor;

in vec3 vsPosition;
in vec2 vsTexCoord;

uniform sampler2D diffuse1;

void main()
{
    //fragColor = texture(diffuse1, vsTexCoord);
    fragColor = vec4(0, 1, 0, 1);
}
