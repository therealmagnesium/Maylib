#version 330 core

const int MAX_POINT_LIGHTS = 2;

struct Attenuation
{
    float constant;
    float linear;
    float exponent;
};

struct BaseLight
{
    float ambientIntensity;
    float diffuseIntensity;
    vec3 color;
};

struct DirectionalLight 
{
    BaseLight base;
    vec3 direction;
};

struct PointLight
{
    BaseLight base;
    Attenuation attenuation;
    vec3 position;
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

uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec4 CalcLightInternal(BaseLight light, vec3 direction, vec3 n)
{
    vec4 ambientColor = vec4(light.color, 1.f) *
                        light.ambientIntensity *
                        vec4(material.ambientColor, 1.f); 

    float diffuseFactor = dot(normalize(normal), -direction);

    vec4 diffuseColor = vec4(0.f);
    vec4 specularColor = vec4(0.f);

    if (diffuseFactor > 0.f)
    {
        diffuseColor = vec4(light.color, 1.f) *
                        light.diffuseIntensity *
                        vec4(material.diffuseColor, 1.f) *
                        diffuseFactor;

        vec3 pixelToCamera = normalize(cameraPosition - position);
        vec3 lightReflect = normalize(reflect(direction, n));
        float specularFactor = dot(pixelToCamera, lightReflect);

        if (specularFactor > 0.f)
        {
            float specularExponent = texture2D(specular1, texCoord).r * 255.f;
            specularFactor = pow(specularFactor, specularExponent);
            specularColor = vec4(light.color, 1.f) *
                light.diffuseIntensity *
                vec4(material.specularColor, 1.f) * specularFactor;
        }
    }

    return (ambientColor + diffuseColor + specularColor);
}

vec4 CalcDirectionalLight(vec3 n)
{
    return CalcLightInternal(directionalLight.base, directionalLight.direction, n);
}

vec4 CalcPointLight(vec3 n, int index)
{
    vec3 lightDirection = position - pointLights[index].position;
    float distance = length(lightDirection);
    lightDirection = normalize(lightDirection);

    vec4 color = CalcLightInternal(pointLights[index].base, lightDirection, n);
    float attenuation = pointLights[index].attenuation.constant +
                        pointLights[index].attenuation.linear * distance +
                        pointLights[index].attenuation.exponent * distance * distance;

    return color / attenuation;
}

void main()
{
    vec3 n = normalize(normal);
    vec4 totalLight = CalcDirectionalLight(n);

    for (int i = 0; i < numPointLights; i++)
    {
        totalLight += CalcPointLight(n, i);
    }

    fragColor = texture2D(diffuse1, texCoord) * totalLight;
}
