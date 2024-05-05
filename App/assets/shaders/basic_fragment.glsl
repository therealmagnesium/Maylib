#version 460 core
out vec4 fragColor;

in vec3 vsPosition;
in vec2 vsTexCoord;

uniform sampler2D tex0;

void main()
{
    fragColor = texture(tex0, vsTexCoord);
}
