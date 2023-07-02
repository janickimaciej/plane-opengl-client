#ifndef GLOBAL_SHADING
#define GLOBAL_SHADING

#include <glm/glm.hpp>
#include "shader_program.hpp"

class GlobalShading {
	static glm::vec3 backgroundColor;
	static float ambient;
	static float fogGradient;
	static float fogDensity;
	
	GlobalShading() = delete;
	static void updateShaderGlobalShading(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	~GlobalShading() = delete;
public:
	static void use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);

	static void setBackgroundColor(glm::vec3 backgroundColor);
	static void setAmbient(float ambient);
	static void setFogGradient(float fogGradient);
	static void setFogDensity(float fogDensity);
};

#endif
