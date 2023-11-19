#pragma once

#include "maps/map.hpp"
#include "scenes/scene.hpp"
#include "sync/user_info.hpp"

#include <memory>
#include <unordered_map>

struct CircularBufferElement
{
	std::unique_ptr<Scene> scene;
	std::unordered_map<int, UserInfo> userInfos;
	int ownId;
	MapName mapName;
	bool hasStateFrame{};
};
