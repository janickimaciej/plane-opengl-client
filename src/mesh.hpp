#ifndef MESH_HPP
#define MESH_HPP

#include "shader_program.hpp"
#include "structs/material.hpp"
#include "structs/vertex.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

class Mesh
{
public:
	Mesh(const ShaderProgram& shaderProgram, const std::string& objPath, const Material& material,
		const std::string& texturePath = "");
	void render(const glm::mat4& modelMeshMatrix) const;
	const ShaderProgram& getShaderProgram() const;
	~Mesh();
	
private:
	const ShaderProgram& m_shaderProgram;
	std::size_t m_vertexCount {};
	Material m_material;
	unsigned int m_VBO {};
	unsigned int m_VAO {};
	bool m_isTextureEnabled = false;
	unsigned int m_texture {};

	void createBuffers(const std::vector<Vertex>& vertices);
	void createTextureBuffer();
	void loadTexture(const std::string& texturePath);
	void updateShaderValues(const glm::mat4& modelMeshMatrix) const;
};

#endif
