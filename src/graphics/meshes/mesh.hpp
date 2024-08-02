#pragma once

#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/meshes/vertex.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	class Mesh
	{
	public:
		Mesh(const std::string& path);
		Mesh(ProceduralMeshName name);
		void render() const;
		~Mesh();
	
	private:
		std::size_t m_vertexCount{};
		unsigned int m_VBO{};
		unsigned int m_VAO{};

		void createBuffers(const std::vector<Vertex>& vertices);
	};
};
