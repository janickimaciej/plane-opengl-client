#define EPS 1e-9

// ... – vector in global coordinate system

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
	bool isMetal;
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

vec3 calcDiffuseDirectionalLight(int i);
vec3 calcSpecularDirectionalLight(int i, vec3 viewVector);
vec3 calcDiffusePointLight(int i);
vec3 calcSpecularPointLight(int i, vec3 viewVector);
vec3 calcDiffuseSpotLight(int i);
vec3 calcSpecularSpotLight(int i, vec3 viewVector);

float calcDiffuseBrightness(vec3 lightVector);
float calcSpecularBrightness(vec3 viewVector, vec3 lightVector);
float calcAttenuation(float attenuationQuadratic, float attenuationLinear,
	float attenuationConstant, vec3 position, vec3 lightPosition);
float calcCutoffCoef(float cutoffInnerRad, float cutoffOuterRad, vec3 lightVector,
	vec3 lightDirection);
vec3 applyFog(vec3 color);

void main()
{
	vec3 ambient = vec3(worldShading.ambient, worldShading.ambient, worldShading.ambient);
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);
	vec3 viewVector = calcViewVector();
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_COUNT; ++i)
	{
		if (directionalLights[i].isActive)
		{
			diffuse += calcDiffuseDirectionalLight(i);
			specular += calcSpecularDirectionalLight(i, viewVector);
		}
	}
	for (int i = 0; i < MAX_POINT_LIGHT_COUNT; ++i)
	{
		if (pointLights[i].isActive)
		{
			diffuse += calcDiffusePointLight(i);
			specular += calcSpecularPointLight(i, viewVector);
		}
	}
	for (int i = 0; i < MAX_SPOT_LIGHT_COUNT; ++i)
	{
		if (spotLights[i].isActive)
		{
			diffuse += calcDiffuseSpotLight(i);
			specular += calcSpecularSpotLight(i, viewVector);
		}
	}

	vec3 surfaceColor = material.color;
	if (isTextureEnabled)
	{
		surfaceColor = surfaceColor * texture(textureSampler, texturePosition).xyz;
	}

	vec3 color;
	if (material.isMetal)
	{
		color = (ambient + diffuse + specular) * surfaceColor;
	}
	else
	{
		color = (ambient + diffuse) * surfaceColor;
		color += specular;
	}

	outColor = vec4(applyFog(color), 1);
}

vec3 calcViewVector()
{
	return normalize(cameraPosition - position.xyz);
}

vec3 calcDiffuseDirectionalLight(int i)
{
	vec3 lightVector = directionalLights[i].direction;

	float brightness = calcDiffuseBrightness(lightVector);

	return brightness * directionalLights[i].color;
}

vec3 calcSpecularDirectionalLight(int i, vec3 viewVector)
{
	vec3 lightVector = directionalLights[i].direction;

	float brightness = calcSpecularBrightness(viewVector, lightVector);

	return brightness * directionalLights[i].color;
}

vec3 calcDiffusePointLight(int i)
{
	vec3 lightVector = normalize(pointLights[i].position - position.xyz);

	float brightness = calcDiffuseBrightness(lightVector);
	float attenuation = calcAttenuation(pointLights[i].attenuationQuadratic,
		pointLights[i].attenuationLinear, pointLights[i].attenuationConstant, position.xyz,
		pointLights[i].position);

	return attenuation * brightness * pointLights[i].color;
}

vec3 calcSpecularPointLight(int i, vec3 viewVector)
{
	vec3 lightVector = normalize(pointLights[i].position - position.xyz);

	float brightness = calcSpecularBrightness(viewVector, lightVector);
	float attenuation = calcAttenuation(pointLights[i].attenuationQuadratic,
		pointLights[i].attenuationLinear, pointLights[i].attenuationConstant, position.xyz,
		pointLights[i].position);

	return attenuation * brightness * pointLights[i].color;
}

vec3 calcDiffuseSpotLight(int i)
{
	vec3 lightVector = normalize(spotLights[i].position - position.xyz);

	float cutoffCoef = calcCutoffCoef(spotLights[i].cutoffInnerRad, spotLights[i].cutoffOuterRad,
		lightVector, spotLights[i].direction);
	if (cutoffCoef < EPS)
	{
		return vec3(0, 0, 0);
	}

	float brightness = calcDiffuseBrightness(lightVector);
	float attenuation = calcAttenuation(spotLights[i].attenuationQuadratic,
		spotLights[i].attenuationLinear, spotLights[i].attenuationConstant, position.xyz,
		spotLights[i].position);

	return attenuation * cutoffCoef * brightness * spotLights[i].color;
}

vec3 calcSpecularSpotLight(int i, vec3 viewVector)
{
	vec3 lightVector = normalize(spotLights[i].position - position.xyz);

	float cutoffCoef = calcCutoffCoef(spotLights[i].cutoffInnerRad, spotLights[i].cutoffOuterRad,
		lightVector, spotLights[i].direction);
	if (cutoffCoef < EPS)
	{
		return vec3(0, 0, 0);
	}

	float brightness = calcSpecularBrightness(viewVector, lightVector);
	float attenuation = calcAttenuation(spotLights[i].attenuationQuadratic,
		spotLights[i].attenuationLinear, spotLights[i].attenuationConstant, position.xyz,
		spotLights[i].position);

	return attenuation * cutoffCoef * brightness * spotLights[i].color;
}

float calcDiffuseBrightness(vec3 lightVector)
{
	float cosNormalLight = dot(normalVector.xyz, lightVector);

	if (cosNormalLight < 0)
	{
		cosNormalLight = 0;
	}

	return material.diffuse * cosNormalLight;
}

float calcSpecularBrightness(vec3 viewVector, vec3 lightVector)
{
	float cosNormalLight = dot(normalVector.xyz, lightVector);
	vec3 reflectionVector = normalize(2 * cosNormalLight * normalVector.xyz - lightVector);
	float cosViewReflection = dot(viewVector, reflectionVector);

	if (cosViewReflection < 0)
	{
		cosViewReflection = 0;
	}

	return material.specular * pow(cosViewReflection, material.shininess);
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
