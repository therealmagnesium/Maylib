#version 330 core

struct DirectionalLight 
{
    float ambientIntensity;
    float diffuseIntensity;
    vec3 color;
    vec3 direction;
};

struct Material
{
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
};

out vec4 fragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoord;

in vec3 currentPosition;

uniform vec3 cameraPosition;

uniform sampler2D diffuse1;
uniform sampler2D specular1;

uniform DirectionalLight directionalLight;
uniform Material material;

void main()
{
    vec4 ambientColor = vec4(directionalLight.color, 1.f) *
                        directionalLight.ambientIntensity *
                        vec4(material.ambientColor, 1.f);

    float diffuseFactor = dot(normalize(normal), -directionalLight.direction);
    vec4 diffuseColor = vec4(0.f);

    if (diffuseFactor > 0.f)
    {
        diffuseColor = vec4(directionalLight.color, 1.f) *
                        directionalLight.diffuseIntensity *
                        vec4(material.diffuseColor, 1.f) *
                        diffuseFactor;
    }

    vec4 specularColor = vec4(0.f);
    vec3 pixelToCamera = normalize(cameraPosition - position);
    vec3 lightReflect = normalize(reflect(directionalLight.direction, normalize(normal)));
    float specularFactor = dot(pixelToCamera, lightReflect);

    if (specularFactor > 0.f)
    {
        float specularExponent = texture2D(specular1, texCoord).r * 255.f;
        specularFactor = pow(specularFactor, specularExponent);
        specularColor = vec4(directionalLight.color, 1.f) *
                        vec4(material.specularColor, 1.f) *
                        specularFactor;
    }

    fragColor = texture2D(diffuse1, texCoord) * clamp((ambientColor + diffuseColor + specularColor), 0.f, 3.f);
}
