#version 330 core
out vec4 fragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in vec3 currentPosition;

uniform sampler2D diffuse1;

uniform vec3 camPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    vec3 n = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    float diffuse = max(dot(n, lightDirection), 0.f);

    float specularStrength = 0.5f;
    vec3 camDirection = normalize(camPosition - currentPosition);
    vec3 reflectDirection = reflect(-lightDirection, n);
    float spec = pow(max(dot(camDirection, reflectDirection), 0.f), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 objectColor = texture2D(diffuse1, texCoord).xyz * lightColor;
    vec3 result = objectColor * (diffuse + specular + 0.25f); 
    fragColor = vec4(result, 1.f);
}
