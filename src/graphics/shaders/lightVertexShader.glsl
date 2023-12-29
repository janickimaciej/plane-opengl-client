// ...Mesh – vector in mesh coordinate system
// ... – vector in global coordinate system

layout (location = 0) in vec3 inPositionMesh;
layout (location = 1) in vec2 inTexturePosition;
layout (location = 2) in vec3 inNormalVectorMesh;

uniform mat4 modelSubmodelMatrix;
uniform mat4 projectionViewMatrix;

out vec4 position;
out vec2 texturePosition;

void main()
{
	position = modelSubmodelMatrix * vec4(inPositionMesh, 1);
	texturePosition = inTexturePosition;
	gl_Position = projectionViewMatrix * position;
}
