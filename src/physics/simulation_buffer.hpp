#pragma once

#include "physics/simulation_buffer_element.hpp"

#include <array>

namespace Physics
{
	class SimulationBuffer
	{
	private:
		static constexpr int bufferSize = 100;
		std::array<SimulationBufferElement, bufferSize> buffer;
	};
};
