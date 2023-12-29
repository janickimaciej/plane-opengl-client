// ... – vector in global coordinate system

struct WorldShading
{
	vec3 backgroundColor;
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

in vec4 position;
in vec2 texturePosition;

uniform vec3 cameraPosition;
uniform WorldShading worldShading;
uniform Material material;
uniform bool isTextureEnabled;
uniform sampler2D textureSampler;

out vec4 outColor;

vec3 applyFog(vec3 color);

void main()
{
	vec3 surfaceColor = material.color;
	if (isTextureEnabled)
	{
		surfaceColor = surfaceColor * texture(textureSampler, texturePosition).xyz;
	}

	outColor = vec4(applyFog(surfaceColor), 1);
}

vec3 applyFog(vec3 color)
{
	float distance = length(position.xyz - cameraPosition);
	float fogCoef = exp(-pow((worldShading.fogDensity * distance), worldShading.fogGradient));
	return fogCoef * color + (1 - fogCoef) * worldShading.backgroundColor;
}
