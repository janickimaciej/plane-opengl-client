// ... – vector in global coordinate system

in vec2 texturePosition;

uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
	vec3 color = texture(textureSampler, texturePosition).xyz;
	float threshold = 0.01;
	if (color.x > threshold || color.y > threshold || color.z > threshold)
	{
		discard;
	}

	outColor = vec4(0, 0.68, 0.05, 1);
}
