#pragma once

#include "app/exit_code.hpp"

#include <atomic>
#include <mutex>
#include <semaphore>

namespace App
{
	class ExitSignal
	{
	public:
		bool shouldStop() const;
		void exit(ExitCode exitCode);
		ExitCode getExitCode() const;
		void acquireRenderingThreadSemaphore();
		void releaseRenderingThreadSemaphore();
		void acquireNetworkThreadSemaphore();

	private:
		std::atomic<bool> m_exiting = false;
		std::binary_semaphore m_renderingThreadSemaphore{0};
		std::binary_semaphore m_networkThreadSemaphore{0};
		ExitCode m_exitCode{};
		std::mutex m_mutex{};
	};
};
