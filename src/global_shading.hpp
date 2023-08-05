#ifndef GLOBAL_SHADING_HPP
#define GLOBAL_SHADING_HPP

#include "shader_program.hpp"

#include <glm/glm.hpp>

class GlobalShading {
public:
	static void use(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);

	static void setBackgroundColor(const glm::vec3& backgroundColor);
	static void setAmbient(float ambient);
	static void setFogGradient(float fogGradient);
	static void setFogDensity(float fogDensity);

private:
	static glm::vec3 s_backgroundColor;
	static float s_ambient;
	static float s_fogGradient;
	static float s_fogDensity;
	
	GlobalShading() = delete;
	static void updateShaderGlobalShading(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	~GlobalShading() = delete;
};

#endif
