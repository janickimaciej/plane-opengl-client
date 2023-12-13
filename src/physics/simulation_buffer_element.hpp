#pragma once

#include "physics/scene.hpp"
#include "physics/simulation_buffer_user.hpp"

#include <mutex>
#include <unordered_map>

namespace Physics
{
	struct SimulationBufferElement
	{
		Scene scene{};
		std::mutex mutex{};
		std::unordered_map<int, SimulationBufferUser> users{};
		bool hasStateFrame{};
	};
};
