#pragma once

#include "app/exitSignal.hpp"
#include "app/gameMode.hpp"
#include "app/ownInput.hpp"
#include "app/udp/udpCommunication.hpp"
#include "graphics/renderingBuffer.hpp"
#include "physics/notification.hpp"
#include "physics/simulationBuffer.hpp"
#include "physics/simulationClock.hpp"
#include "physics/timestep.hpp"

#include <memory>
#include <semaphore>
#include <thread>

namespace App
{
	class PhysicsThread
	{
	public:
		PhysicsThread(ExitSignal& exitSignal, GameMode gameMode,
			const Physics::SimulationClock& simulationClock,
			Physics::SimulationBuffer& simulationBuffer, int ownId,
			Physics::Notification& notification, Graphics::RenderingBuffer& renderingBuffer,
			OwnInput& ownInput, UDPCommunication* udpCommunication,
			const std::shared_ptr<std::binary_semaphore>& renderingThreadSemaphore);
		void join();

	private:
		std::thread m_thread{};
		ExitSignal& m_exitSignal;

		GameMode m_gameMode;

		const Physics::SimulationClock& m_simulationClock;
		Physics::SimulationBuffer& m_simulationBuffer;
		Physics::Notification& m_notification;
		int m_ownId{};

		Graphics::RenderingBuffer& m_renderingBuffer;
		OwnInput& m_ownInput;
		Physics::Timestep m_newestStateFrameTimestep{};

		UDPCommunication* m_udpCommunication;

		void start(std::shared_ptr<std::binary_semaphore> renderingThreadSemaphore);
		void mainLoop(const Physics::Timestep& initialTimestep);
		void sleepIfFuture(const Physics::Timestep& timestep);
	};
};
