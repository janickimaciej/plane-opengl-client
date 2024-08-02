#include "graphics/meshes/mesh.hpp"

#include "graphics/meshes/meshGenerator.hpp"
#include "graphics/meshes/objParser.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glad/glad.h>

#include <string>
#include <vector>

namespace Graphics
{
	Mesh::Mesh(const std::string& path)
	{
		std::vector<Vertex> vertices = ObjParser::parse(path);
		m_vertexCount = vertices.size();
		createBuffers(vertices);
	}

	Mesh::Mesh(ProceduralMeshName name)
	{
		std::vector<Vertex> vertices = MeshGenerator::generate(name);
		m_vertexCount = vertices.size();
		createBuffers(vertices);
	}

	void Mesh::render() const
	{
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertexCount));
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::createBuffers(const std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &m_VBO);
		glGenVertexArrays(1, &m_VAO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
			vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, texturePosition)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, normalVector)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}
};
