#include "app/threads/network_thread.hpp"

#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/threads/physics_thread.hpp"
#include "common/airplane_type_name.hpp"
#include "common/sync/user_info.hpp"
#include "common/sync/user_state.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <string>
#include <thread>
#include <unordered_map>

namespace App
{
	NetworkThread::NetworkThread(std::binary_semaphore& renderingSemaphore, GameMode gameMode,
		const std::string& ipAddress, int port, OwnInput& ownInput,
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer) :
		m_udpServer{ipAddress, port},
		m_thread
		{
			[this, &renderingSemaphore, gameMode, &ownInput, &renderingBuffer]
			{
				this->start(renderingSemaphore, gameMode, ownInput, renderingBuffer);
			}
		}
	{ }

	void NetworkThread::stop()
	{
		m_mainLoopSingleplayer.release();
		m_shouldStop = true;
	}

	void NetworkThread::join()
	{
		m_thread.join();
	}

	void NetworkThread::start(std::binary_semaphore& renderingSemaphore, GameMode gameMode,
		OwnInput& ownInput, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		if (gameMode == GameMode::multiplayer)
		{
			startMultiplayer(renderingBuffer);
		}
		else
		{
			startSingleplayer(renderingBuffer);
		}
		PhysicsThread physicsThread{gameMode, renderingSemaphore, *m_simulationClock,
			*m_simulationBuffer, m_notification, *renderingBuffer, ownInput, m_udpServer};
		if (gameMode == GameMode::multiplayer)
		{
			mainLoopMultiplayer();
		}
		else
		{
			m_mainLoopSingleplayer.acquire();
		}
		physicsThread.stop();
		physicsThread.join();
	}

	void NetworkThread::startMultiplayer(
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		// TODO
	}

	void NetworkThread::startSingleplayer(
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		constexpr int ownId = 0;
		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(ownId);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(ownId);

		m_simulationClock =
			std::make_unique<Physics::SimulationClock>(std::chrono::duration<float>{0});
		int initialSecond{};
		unsigned int initialFrame{};
		m_simulationClock->getTime(initialSecond, initialFrame);
		
		std::unordered_map<int, Common::UserInfo> userInfos;
		Common::UserInfo ownInfo;
		ownInfo.second = initialSecond;
		constexpr int initialHP = 100;
		ownInfo.state.hp = initialHP;
		constexpr glm::vec3 initialPosition{0, 50, 100};
		ownInfo.state.state.position = initialPosition;
		constexpr glm::vec3 initialVelocity{0, 0, -100};
		ownInfo.state.state.velocity = initialVelocity;
		userInfos.insert({ownId, ownInfo});
		m_simulationBuffer->writeStateFrame(initialFrame, userInfos);

		m_notification.setNotification(initialSecond, initialFrame, true);
	}

	void NetworkThread::mainLoopMultiplayer()
	{
		while (!m_shouldStop)
		{
			// TODO
		}
	}
};
