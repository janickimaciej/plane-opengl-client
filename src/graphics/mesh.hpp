#ifndef MESH_HPP
#define MESH_HPP

#include "graphics/vertex.hpp"

#include <cstddef>
#include <string>
#include <vector>

class Mesh
{
public:
	Mesh(const std::string& path);
	void render() const;
	~Mesh();
	
private:
	std::size_t m_vertexCount{};
	unsigned int m_VBO{};
	unsigned int m_VAO{};

	void createBuffers(const std::vector<Vertex>& vertices);
};

#endif
