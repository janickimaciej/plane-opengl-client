#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/simulation_buffer_element.hpp"

#include <array>

namespace Graphics
{
	class SimulationBuffer
	{
	private:
		static const int bufferSize = 3;
		std::array<SimulationBufferElement, bufferSize> buffer;

		const ShaderProgram surfaceShaderProgram{SH_SURFACE_VERTEX, SH_SURFACE_FRAGMENT};
		const ShaderProgram lightShaderProgram{SH_LIGHT_VERTEX, SH_LIGHT_FRAGMENT};

		AssetManager<const Mesh> meshManager;
		AssetManager<const Texture> textureManager;
	};
};
