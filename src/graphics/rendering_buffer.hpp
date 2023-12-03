#pragma once

#include "common/airplane_type_name.hpp"
#include "common/sync/airplane_info.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/rendering_buffer_element.hpp"
#include "graphics/scene.hpp"

#include <array>
#include <mutex>
#include <unordered_map>

namespace Graphics
{
	class RenderingBuffer
	{
	public:
		RenderingBuffer(int ownId, Common::AirplaneTypeName ownAirplaneTypeName, MapName mapName);

		void updateBuffer(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);

		void updateAndRenderScene(float aspectRatio);

	private:
		static const int bufferSize = 3;
		std::array<RenderingBufferElement, bufferSize> m_buffer;
		Scene m_scene;

		int m_lastUpdated{};
		int m_rendered{};
		std::mutex m_mutex;
	};
};
