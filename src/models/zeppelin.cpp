#include "zeppelin.hpp"

void Zeppelin::updateShaderLightModelMatrix() const { }

void Zeppelin::renderSurfaces() const {
	body.render();
}

void Zeppelin::renderLights() const { }

Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	Mesh& bodyMesh) : Model(surfaceShaderProgram, lightShaderProgram), body(bodyMesh) {
	scale(57);
	updateShaderLightModelMatrix();
}
