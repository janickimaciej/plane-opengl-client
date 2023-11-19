#pragma once

#include "circular_buffer_element.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <array>

class Simulation
{
private:
	static constexpr int circularBufferSize = 100;
	std::array<CircularBufferElement, circularBufferSize> circularBuffer;

	const ShaderProgram surfaceShaderProgram{SH_SURFACE_VERTEX, SH_SURFACE_FRAGMENT};
	const ShaderProgram lightShaderProgram{SH_LIGHT_VERTEX, SH_LIGHT_FRAGMENT};

	AssetManager<const Mesh> meshManager;
	AssetManager<const Texture> textureManager;
};
