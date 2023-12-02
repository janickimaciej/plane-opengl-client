#pragma once

#include "common/sync/user_info.hpp"
#include "physics/scene.hpp"

#include <memory>
#include <mutex>
#include <unordered_map>

namespace Physics
{
	struct SimulationBufferElement
	{
		std::unique_ptr<Scene> scene;
		std::mutex mutex;
		std::unordered_map<int, Common::UserInfo> userInfos;
		bool hasStateFrame{};
	};
};