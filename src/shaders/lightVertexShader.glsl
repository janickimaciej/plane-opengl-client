#version 330 core

// ...Mesh – vector in mesh coordinate system
// ... – vector in global coordinate system

layout (location = 0) in vec3 inPositionMesh;
layout (location = 1) in vec2 inTexturePosition;
layout (location = 2) in vec3 inNormalVectorMesh;

uniform mat4 meshMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 position;

void main() {
	position = modelMatrix*meshMatrix*vec4(inPositionMesh, 1);
	gl_Position = projectionMatrix*viewMatrix*position;
}
