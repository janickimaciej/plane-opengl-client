#include "graphics/rendering_buffer.hpp"

#include "common/scene_info.hpp"
#include "graphics/rendering_buffer_element.hpp"
#include "graphics/scene.hpp"

#include <array>
#include <mutex>

namespace Graphics
{
	RenderingBuffer::RenderingBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void RenderingBuffer::initialize(Common::AirplaneTypeName ownAirplaneTypeName, MapName mapName)
	{
		m_scene = std::make_unique<Scene>(m_ownId, ownAirplaneTypeName, mapName);
	}

	void RenderingBuffer::updateBuffer(const Common::SceneInfo& sceneInfo)
	{
		m_mutex.lock();

		unsigned int index = (m_lastUpdated + 1) % 3 == m_beingRendered ?
			(m_beingRendered + 1) % 3 : (m_lastUpdated + 1) % 3;

		m_mutex.unlock();

		m_buffer[index].sceneInfo = sceneInfo;

		m_mutex.lock();

		m_lastUpdated = index;

		m_mutex.unlock();
	}

	void RenderingBuffer::updateAndRenderScene(float aspectRatio)
	{
		m_mutex.lock();

		unsigned int index = m_lastUpdated;
		m_beingRendered = index;

		m_mutex.unlock();

		m_scene->update(m_buffer[index].sceneInfo);
		m_scene->updateShaders(aspectRatio);
		m_scene->render();
	}
};
