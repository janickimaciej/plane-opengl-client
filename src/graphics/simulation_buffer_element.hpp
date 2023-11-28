#pragma once

#include "common/sync/airplane_info.hpp"
#include "graphics/scene.hpp"

#include <memory>
#include <unordered_map>

namespace Graphics
{
	struct SimulationBufferElement
	{
		std::unique_ptr<Scene> scene;
		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos;
	};
};
