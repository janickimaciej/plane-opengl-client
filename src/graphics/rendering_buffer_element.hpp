#pragma once

#include "common/scene_info.hpp"

#include <unordered_map>

namespace Graphics
{
	struct RenderingBufferElement
	{
		Common::SceneInfo sceneInfo{};
		int day{};
		float timeOfDay{};
	};
};
