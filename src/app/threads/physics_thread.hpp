#pragma once

#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/udp/udp_connection.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/notification.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"
#include "physics/timestep.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <thread>

namespace App
{
	class PhysicsThread
	{
	public:
		PhysicsThread(ExitSignal& exitSignal, GameMode gameMode,
			std::binary_semaphore& renderingSemaphore,
			const Physics::SimulationClock& simulationClock,
			Physics::SimulationBuffer& simulationBuffer, int ownId,
			Physics::Notification& notification, Graphics::RenderingBuffer& renderingBuffer,
			OwnInput& ownInput, UDPConnection* udpConnection);
		void join();

	private:
		std::thread m_thread;
		ExitSignal& m_exitSignal;

		GameMode m_gameMode;

		const Physics::SimulationClock& m_simulationClock;
		Physics::SimulationBuffer& m_simulationBuffer;
		Physics::Notification& m_notification;
		int m_ownId{};

		Graphics::RenderingBuffer& m_renderingBuffer;
		OwnInput& m_ownInput;

		UDPConnection* m_udpConnection;

		void start(std::binary_semaphore& renderingSemaphore);
		void mainLoop(const Physics::Timestep& initialTimestep);
		void sleepIfFuture(const Physics::Timestep& timestep);
	};
};
