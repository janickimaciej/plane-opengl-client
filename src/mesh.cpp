#include "mesh.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../dep/stb_image.h"
#include "obj_parser.hpp"

void Mesh::createBuffers(const std::vector<Vertex>& vertices) {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texturePosition));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normalVector));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Mesh::createTextureBuffer() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Mesh::loadTexture(std::string texturePath) {
	int width;
	int height;
	int nrOfChannels;
	unsigned char* textureData = stbi_load(texturePath.c_str(), &width, &height, &nrOfChannels, STBI_rgb);
	if(textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		isTextureEnabled = true;
	} else {
		std::cerr << "Error loading texture: " << texturePath << std::endl;
	}
	stbi_image_free(textureData);
}

void Mesh::updateShaderValues() const {
	shaderProgram.setUniform3f("material.color", material.color);
	shaderProgram.setUniform1f("material.diffuse", material.diffuse);
	shaderProgram.setUniform1f("material.specular", material.specular);
	shaderProgram.setUniform1f("material.shininess", material.shininess);
	shaderProgram.setUniform1b("isTextureEnabled", isTextureEnabled);
}

Mesh::Mesh(const ShaderProgram& shaderProgram, std::string objPath, Material material,
	std::string texturePath) :
	shaderProgram(shaderProgram), material(material) {
	std::vector<Vertex> vertices;
	ObjParser::parse(objPath, vertices);
	vertexCount = vertices.size();
	createBuffers(vertices);
	if(texturePath != "") {
		createTextureBuffer();
		loadTexture(texturePath);
	}
}

void Mesh::render() const {
	updateShaderValues();
	if(isTextureEnabled) {
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}

const ShaderProgram& Mesh::getShaderProgram() const {
	return shaderProgram;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture);
}
