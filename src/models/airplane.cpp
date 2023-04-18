#include "airplane.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

constexpr float rotateLightsConstraintDeg = 30;
constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor = glm::vec3(1, 1, 1);
constexpr float lightsCutoffInnerDeg = 8;
constexpr float lightsCutoffOuterDeg = 10;
constexpr glm::vec3 leftLightPosition = glm::vec3(2.14, -0.448, -1.096);
constexpr glm::vec3 rightLightPosition = glm::vec3(-2.14, -0.448, -1.096);

void Airplane::updateShaderLightModelMatrix() const {
	leftLight.updateShaderLightModelMatrix(matrix);
	rightLight.updateShaderLightModelMatrix(matrix);
}

void Airplane::renderSurfaces() const {
	cap.render();
	propeller.render();
	body.render();
	joins.render();
	tires.render();
}

void Airplane::renderLights() const {
	leftLight.render();
	rightLight.render();
}

Airplane::Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Mesh& capMesh, const Mesh& propellerMesh, const Mesh& bodyMesh, const Mesh& joinsMesh,
	const Mesh& tiresMesh, const Mesh& lightMesh) :
	Model(surfaceShaderProgram, lightShaderProgram), cap(capMesh), propeller(propellerMesh), body(bodyMesh),
	joins(joinsMesh), tires(tiresMesh),
	leftLight(surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg),
	rightLight(surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg) {
	leftLight.translate(leftLightPosition);
	rightLight.translate(rightLightPosition);
	updateShaderLightModelMatrix();
}

void Airplane::rotatePropeller(float angleDeg) {
	propeller.roll(angleDeg);
}
