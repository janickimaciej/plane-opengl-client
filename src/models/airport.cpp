#include "airport.hpp"

#define LIGHT_TRANSLATE glm::vec3(-49 + 14*i, 7, 250)

constexpr int hangarsCount = 3;
constexpr int lightsCount = 8;
constexpr float lightsAttenuationQuadratic = 0.0001;
constexpr float lightsAttenuationLinear = 0.0005;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor = glm::vec3(1, 1, 0.6);
constexpr float lightsCutoffInnerDeg = 25;
constexpr float lightsCutoffOuterDeg = 35;
constexpr glm::vec3 lampColor = glm::vec3(1, 1, 0.6);

void Airport::updateShaderLightModelMatrix() const {
	for(int i = 0; i < lightsCount; i++) {
		lights[i].updateShaderLightModelMatrix(matrix);
	}
}

void Airport::renderSurfaces() const {
	ground.render();
	runway.render();
	apron.render();
	tower.render();
	for(int i = 0; i < hangarsCount; i++) {
		hangars[i].render();
	}
	for(int i = 0; i < lightsCount; i++) {
		lightBodies[i].render();
	}
}

void Airport::renderLights() const {
	for(int i = 0; i < lightsCount; i++) {
		lights[i].render();
	}
}

Airport::Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	Mesh& groundMesh, Mesh& runwayMesh, Mesh& apronMesh, Mesh& towerMesh, Mesh& hangarMesh,
	Mesh& lightBodyMesh, Mesh& lightMesh) : Model(surfaceShaderProgram, lightShaderProgram),
	ground(groundMesh), runway(runwayMesh), apron(apronMesh), tower(towerMesh) {
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
			lightsCutoffOuterDeg));
		lights[i].translate(LIGHT_TRANSLATE);
		lights[i].yaw(180);
		lights[i].pitch(15);
	}
	updateShaderLightModelMatrix();
}
