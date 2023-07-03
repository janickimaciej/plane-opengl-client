#include "airplane.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor = glm::vec3(1, 1, 1);
constexpr float lightsCutoffInnerDeg = 8;
constexpr float lightsCutoffOuterDeg = 10;
constexpr glm::vec3 leftLightPosition = glm::vec3(2.14, -0.448, -1.096);
constexpr glm::vec3 rightLightPosition = glm::vec3(-2.14, -0.448, -1.096);

void Airplane::updateShaderLightMatrix() const {
	leftLight.updateShaderLightTranslation(matrix);
	rightLight.updateShaderLightTranslation(matrix);
}

void Airplane::renderSurfaces() const {
	cap.render(matrix);
	propeller.render(matrix);
	body.render(matrix);
	joins.render(matrix);
	tires.render(matrix);
}

void Airplane::renderLights() const {
	leftLight.render(matrix);
	rightLight.render(matrix);
}

Airplane::Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Mesh& capMesh, const Mesh& propellerMesh, const Mesh& bodyMesh, const Mesh& joinsMesh,
	const Mesh& tiresMesh, const Mesh& lightMesh) :
	Model(surfaceShaderProgram, lightShaderProgram), cap(capMesh), propeller(propellerMesh), body(bodyMesh),
	joins(joinsMesh), tires(tiresMesh),
	leftLight(surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg, matrix),
	rightLight(surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg, matrix) {
	leftLight.translate(leftLightPosition, matrix);
	rightLight.translate(rightLightPosition, matrix);
	updateShaderLightMatrix();
}

void Airplane::rotatePropeller(float angleDeg) {
	propeller.roll(angleDeg);
}
