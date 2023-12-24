#define EPS 1e-9

// ... – vector in global coordinate system
// pseudoColor = color/material.color

struct WorldShading
{
	vec3 backgroundColor;
	float ambient;
	float fogGradient;
	float fogDensity;
};

struct Material
{
	vec3 color;
	float diffuse;
	float specular;
	float shininess;
};

struct DirectionalLight
{
	bool isActive;
	vec3 direction;
	vec3 color;
};

struct PointLight
{
	bool isActive;
	vec3 position;
	vec3 color;
	float attenuationQuadratic;
	float attenuationLinear;
	float attenuationConstant;
};

struct SpotLight
{
	bool isActive;
	vec3 position;
	vec3 direction;
	vec3 color;
	float attenuationQuadratic;
	float attenuationLinear;
	float attenuationConstant;
	float cutoffInnerRad;
	float cutoffOuterRad;
};

in vec4 position;
in vec2 texturePosition;
in vec4 normalVector;

uniform vec3 cameraPosition;
uniform WorldShading worldShading;
uniform Material material;
uniform bool isTextureEnabled;
uniform sampler2D textureSampler;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHT_COUNT];
uniform PointLight pointLights[MAX_POINT_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_SPOT_LIGHT_COUNT];

out vec4 outColor;

vec3 calcViewVector();

vec3 calcPseudoColorDirectionalLight(int i, vec3 viewVector);
vec3 calcPseudoColorPointLight(int i, vec3 viewVector);
vec3 calcPseudoColorSpotLight(int i, vec3 viewVector);

float calcBrightness(vec3 viewVector, vec3 lightVector);
float calcAttenuation(float attenuationQuadratic, float attenuationLinear,
	float attenuationConstant, vec3 position, vec3 lightPosition);
float calcCutoffCoef(float cutoffInnerRad, float cutoffOuterRad, vec3 lightVector,
	vec3 lightDirection);
vec3 applyFog(vec3 color);

void main()
{
	vec3 pseudoColor = vec3(worldShading.ambient, worldShading.ambient, worldShading.ambient);
	vec3 viewVector = calcViewVector();
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_COUNT; ++i)
	{
		if (directionalLights[i].isActive)
		{
			pseudoColor += calcPseudoColorDirectionalLight(i, viewVector);
		}
	}
	for (int i = 0; i < MAX_POINT_LIGHT_COUNT; ++i)
	{
		if (pointLights[i].isActive)
		{
			pseudoColor += calcPseudoColorPointLight(i, viewVector);
		}
	}
	for (int i = 0; i < MAX_SPOT_LIGHT_COUNT; ++i)
	{
		if (spotLights[i].isActive)
		{
			pseudoColor += calcPseudoColorSpotLight(i, viewVector);
		}
	}

	vec3 surfaceColor;
	if (isTextureEnabled)
	{
		surfaceColor = texture(textureSampler, texturePosition).xyz;
	}
	else
	{
		surfaceColor = material.color;
	}

	outColor = vec4(applyFog(pseudoColor * surfaceColor), 1);
}

vec3 calcViewVector()
{
	return normalize(cameraPosition - position.xyz);
}

vec3 calcPseudoColorDirectionalLight(int i, vec3 viewVector)
{
	vec3 lightVector = directionalLights[i].direction;

	float brightness = calcBrightness(viewVector, lightVector);

	return brightness * directionalLights[i].color;
}

vec3 calcPseudoColorPointLight(int i, vec3 viewVector)
{
	vec3 lightVector = normalize(pointLights[i].position - position.xyz);

	float brightness = calcBrightness(viewVector, lightVector);
	float attenuation = calcAttenuation(pointLights[i].attenuationQuadratic,
		pointLights[i].attenuationLinear, pointLights[i].attenuationConstant, position.xyz,
		pointLights[i].position);

	return attenuation * brightness * pointLights[i].color;
}

vec3 calcPseudoColorSpotLight(int i, vec3 viewVector)
{
	vec3 lightVector = normalize(spotLights[i].position - position.xyz);

	float cutoffCoef = calcCutoffCoef(spotLights[i].cutoffInnerRad, spotLights[i].cutoffOuterRad,
		lightVector, spotLights[i].direction);
	if (cutoffCoef < EPS)
	{
		return vec3(0, 0, 0);
	}

	float brightness = calcBrightness(viewVector, lightVector);
	float attenuation = calcAttenuation(spotLights[i].attenuationQuadratic,
		spotLights[i].attenuationLinear, spotLights[i].attenuationConstant, position.xyz,
		spotLights[i].position);

	return attenuation * cutoffCoef * brightness * spotLights[i].color;
}

float calcBrightness(vec3 viewVector, vec3 lightVector)
{
	float cosNormalLight = dot(normalVector.xyz, lightVector);
	vec3 reflectionVector = normalize(2 * cosNormalLight * normalVector.xyz - lightVector);
	float cosViewReflection = dot(viewVector, reflectionVector);

	if (cosNormalLight < 0)
	{
		cosNormalLight = 0;
	}
	if (cosViewReflection < 0)
	{
		cosViewReflection = 0;
	}

	return material.diffuse * cosNormalLight + material.specular *
		pow(cosViewReflection, material.shininess);
}

float calcAttenuation(float attenuationQuadratic, float attenuationLinear,
	float attenuationConstant, vec3 position, vec3 lightPosition)
{
	float distance = length(position - lightPosition);
	return 1 / (attenuationQuadratic * distance * distance +
		attenuationLinear * distance + attenuationConstant);
}

float calcCutoffCoef(float cutoffInnerRad, float cutoffOuterRad, vec3 lightVector,
	vec3 lightDirection)
{
	float cosLightDirection = dot(lightVector, lightDirection);
	if (cosLightDirection < cos(cutoffOuterRad))
	{
		return 0;
	}
	if (cosLightDirection < cos(cutoffInnerRad))
	{
		return (cosLightDirection - cos(cutoffOuterRad)) / (cos(cutoffInnerRad) -
			cos(cutoffOuterRad));
	}
	return 1;
}

vec3 applyFog(vec3 color)
{
	float distance = length(position.xyz - cameraPosition);
	float fogCoef = exp(-pow((worldShading.fogDensity * distance), worldShading.fogGradient));
	return fogCoef * color + (1 - fogCoef) * worldShading.backgroundColor;
}
