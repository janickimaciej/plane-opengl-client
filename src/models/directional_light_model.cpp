#include "directional_light_model.hpp"

void DirectionalLightModel::updateShaderLightMatrix() const {
	light.updateShaderLightTranslation(matrix);
}

void DirectionalLightModel::renderSurfaces() const { }

void DirectionalLightModel::renderLights() const { }

DirectionalLightModel::DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, glm::vec3 lightColor) :
	Model(surfaceShaderProgram, lightShaderProgram), light(surfaceShaderProgram, 0, 0, 1, lightColor) {
	updateShaderLightMatrix();
}

void DirectionalLightModel::setLightColor(glm::vec3 color) {
	light.setColor(color);
}
