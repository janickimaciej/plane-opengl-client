#include "graphics/rendering_buffer.hpp"

#include "common/sync/airplane_info.hpp"
#include "graphics/rendering_buffer_element.hpp"
#include "graphics/scene.hpp"

#include <array>
#include <mutex>
#include <unordered_map>
#include <iostream> //tmp

namespace Graphics
{
	RenderingBuffer::RenderingBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void RenderingBuffer::initialize(Common::AirplaneTypeName ownAirplaneTypeName, MapName mapName)
	{
		m_scene = std::make_unique<Scene>(m_ownId, ownAirplaneTypeName, mapName);
	}

	void RenderingBuffer::updateBuffer(
		const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos)
	{
		m_mutex.lock();

		unsigned int index = (m_lastUpdated + 1) % 3 == m_beingRendered ?
			(m_beingRendered + 1) % 3 : (m_lastUpdated + 1) % 3;
		//std::cout << index << " UPDATE" << std::endl; //tmp

		m_mutex.unlock();

		m_buffer[index].airplaneInfos = airplaneInfos;

		m_mutex.lock();

		m_lastUpdated = index;

		m_mutex.unlock();
	}

	void RenderingBuffer::updateAndRenderScene(float aspectRatio)
	{
		m_mutex.lock();

		unsigned int index = m_lastUpdated;
		m_beingRendered = index;
		//std::cout << index << "\t RENDER " << std::endl;//tmp

		m_mutex.unlock();

		m_scene->update(m_buffer[index].airplaneInfos, m_buffer[index].day,
			m_buffer[index].timeOfDay);
		m_scene->updateShaders(aspectRatio);
		m_scene->render();
	}
};
