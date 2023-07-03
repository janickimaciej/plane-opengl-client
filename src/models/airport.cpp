#include "airport.hpp"

#define LIGHT_TRANSLATE glm::vec3(-49 + 14*i, 7, 250)

constexpr int hangarsCount = 3;
constexpr int lightsCount = 8;
constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor = glm::vec3(1, 1, 0.6);
constexpr float lightsCutoffInnerDeg = 25;
constexpr float lightsCutoffOuterDeg = 35;

void Airport::updateShaderLightMatrix() const {
	for(int i = 0; i < lightsCount; i++) {
		lights[i].updateShaderLightTranslation(matrix);
	}
}

void Airport::renderSurfaces() const {
	ground.render(matrix);
	runway.render(matrix);
	apron.render(matrix);
	tower.render(matrix);
	for(int i = 0; i < hangarsCount; i++) {
		hangars[i].render(matrix);
	}
	for(int i = 0; i < lightsCount; i++) {
		lightBodies[i].render(matrix);
	}
}

void Airport::renderLights() const {
	for(int i = 0; i < lightsCount; i++) {
		lights[i].render(matrix);
	}
}

Airport::Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Mesh& groundMesh, const Mesh& runwayMesh, const Mesh& apronMesh, const Mesh& towerMesh,
	const Mesh& hangarMesh, const Mesh& lightBodyMesh, const Mesh& lightMesh) :
	Model(surfaceShaderProgram, lightShaderProgram), ground(groundMesh), runway(runwayMesh),
	apron(apronMesh), tower(towerMesh) {
	for(int i = 0; i < hangarsCount; i++) {
		hangars.push_back(MeshInstance(hangarMesh));
		hangars[i].translate(glm::vec3(0, 0, -46*i));
	}
	for(int i = 0; i < lightsCount; i++) {
		lightBodies.push_back(MeshInstance(lightBodyMesh));
		lightBodies[i].translate(LIGHT_TRANSLATE);
		lightBodies[i].yaw(180);
		lightBodies[i].pitch(15);
	}
	for(int i = 0; i < lightsCount; i++) {
		lights.push_back(SpotLight(surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
			lightsCutoffOuterDeg, matrix));
		lights[i].translate(LIGHT_TRANSLATE, matrix);
		lights[i].yaw(180, matrix);
		lights[i].pitch(15, matrix);
	}
	updateShaderLightMatrix();
}
