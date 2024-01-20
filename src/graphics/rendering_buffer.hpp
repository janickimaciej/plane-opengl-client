#pragma once

#include "common/airplane_type_name.hpp"
#include "common/map_name.hpp"
#include "common/scene_info.hpp"
#include "graphics/scene.hpp"

#include <array>
#include <memory>
#include <mutex>

namespace Graphics
{
	class RenderingBuffer
	{
	public:
		RenderingBuffer(int ownId);
		void initialize(Common::AirplaneTypeName ownAirplaneTypeName, Common::MapName mapName);
		void updateBuffer(const Common::SceneInfo& sceneInfo);
		void updateAndRenderScene(float aspectRatio);

	private:
		static const int bufferSize = 3;
		std::array<Common::SceneInfo, bufferSize> m_buffer{};
		int m_ownId{};
		std::unique_ptr<Scene> m_scene{};

		unsigned int m_lastUpdated{};
		unsigned int m_beingRendered{};
		std::mutex m_mutex{};
	};
};
