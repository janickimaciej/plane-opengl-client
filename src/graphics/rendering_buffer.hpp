#pragma once

#include "common/airplane_info.hpp"
#include "common/airplane_type_name.hpp"
#include "common/map_name.hpp"
#include "graphics/rendering_buffer_element.hpp"
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
		std::array<RenderingBufferElement, bufferSize> m_buffer{};
		int m_ownId{};
		std::unique_ptr<Scene> m_scene{};

		unsigned int m_lastUpdated{};
		unsigned int m_beingRendered{};
		std::mutex m_mutex{};
	};
};
