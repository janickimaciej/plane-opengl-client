#ifndef MESH
#define MESH

#include <string>
#include <vector>
#include "structs/vertex.hpp"
#include "shader_program.hpp"
#include "structs/material.hpp"

class Mesh {
	const ShaderProgram& shaderProgram;
	std::vector<Vertex> vertices;
	Material material;
	unsigned int VAO;
	bool isTextureEnabled = false;
	unsigned int texture;

	void createBuffers();
	void createTextureBuffer();
	void loadTexture(std::string texturePath);
	void updateShaderValues() const;
public:
	Mesh(const ShaderProgram& shaderProgram, std::string objPath, Material material,
		std::string texturePath = "");
	void render() const;
	const ShaderProgram& getShaderProgram() const;

	virtual ~Mesh() { }
};

#endif
