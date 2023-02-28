#version 330 core

// ... – vector in global coordinate system

struct GlobalShading {
	vec3 backgroundColor;
	float ambient;
	float fogGradient;
	float fogDensity;
};

struct Material {
	vec3 color;
	float diffuse;
	float specular;
	float shininess;
};

in vec4 position;

uniform vec3 cameraPosition;
uniform GlobalShading globalShading;
uniform Material material;

out vec4 outColor;

vec3 applyFog(vec3 color);

void main() {
	outColor = vec4(applyFog(material.color), 1);
}

vec3 applyFog(vec3 color) {
	float distance = length(position.xyz - cameraPosition);
	float fogCoef = exp(-pow((globalShading.fogDensity*distance), globalShading.fogGradient));
	return fogCoef*color + (1 - fogCoef)*globalShading.backgroundColor;
}
