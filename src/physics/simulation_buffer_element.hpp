#pragma once

#include "common/sync/user_info.hpp"
#include "physics/scene.hpp"

#include <memory>
#include <unordered_map>

namespace Physics
{
	struct SimulationBufferElement
	{
		std::unique_ptr<Scene> scene;
		std::unordered_map<int, Common::UserInfo> userInfos;
		int ownId;
		bool hasStateFrame{};
	};
};
