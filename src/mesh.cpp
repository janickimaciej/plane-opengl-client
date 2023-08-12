#include "mesh.hpp"

#include "obj_parser.hpp"
#include "shader_program.hpp"
#include "structs/material.hpp"
#include "structs/vertex.hpp"

#include <stb_image.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

Mesh::Mesh(const ShaderProgram& shaderProgram, const std::string& objPath,
	const Material& material, const std::string& texturePath) :
	m_shaderProgram { shaderProgram },
	m_material { material }
{
	std::vector<Vertex> vertices {};
	ObjParser::parse(objPath, vertices);
	m_vertexCount = vertices.size();
	createBuffers(vertices);
	if (texturePath != "")
	{
		createTextureBuffer();
		loadTexture(texturePath);
	}
}

void Mesh::render(const glm::mat4& modelMeshMatrix) const
{
	updateShaderValues(modelMeshMatrix);
	if (m_isTextureEnabled)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertexCount);
	glBindVertexArray(0);
}

const ShaderProgram& Mesh::getShaderProgram() const
{
	return m_shaderProgram;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteTextures(1, &m_texture);
}

void Mesh::createBuffers(const std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(Vertex)), &vertices[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, texturePosition));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, normalVector));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Mesh::createTextureBuffer()
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Mesh::loadTexture(const std::string& texturePath)
{
	int width {};
	int height {};
	int nrOfChannels {};
	unsigned char* textureData = stbi_load(texturePath.c_str(), &width, &height, &nrOfChannels,
		STBI_rgb);
	if (textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
			textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		m_isTextureEnabled = true;
	}
	else
	{
		std::cerr << "Error loading texture: \n" << texturePath;
	}
	stbi_image_free(textureData);
}

void Mesh::updateShaderValues(const glm::mat4& modelMeshMatrix) const
{
	m_shaderProgram.setUniformMatrix4f("modelMeshMatrix", modelMeshMatrix);
	m_shaderProgram.setUniform3f("material.color", m_material.color);
	m_shaderProgram.setUniform1f("material.diffuse", m_material.diffuse);
	m_shaderProgram.setUniform1f("material.specular", m_material.specular);
	m_shaderProgram.setUniform1f("material.shininess", m_material.shininess);
	m_shaderProgram.setUniform1b("isTextureEnabled", m_isTextureEnabled);
}
