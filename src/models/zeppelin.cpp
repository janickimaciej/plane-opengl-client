#include "zeppelin.hpp"

void Zeppelin::updateShaderLightMatrix() const { }

void Zeppelin::renderSurfaces() const {
	body.render(matrix);
}

void Zeppelin::renderLights() const { }

Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Mesh& bodyMesh) : Model(surfaceShaderProgram, lightShaderProgram), body(bodyMesh) {
	scale(57);
	updateShaderLightMatrix();
}
