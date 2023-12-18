#include "app/exit_signal.hpp"

#include "app/exit_code.hpp"

#include <atomic>
#include <mutex>
#include <semaphore>

namespace App
{
	bool ExitSignal::shouldStop() const
	{
		return m_exiting;
	}

	void ExitSignal::exit(ExitCode exitCode)
	{
		m_mutex.lock();

		if (!m_exiting)
		{
			m_exiting = true;
			m_renderingThreadSemaphore.release();
			m_networkThreadSemaphore.release();
			m_exitCode = exitCode;
		}

		m_mutex.unlock();
	}

	ExitCode ExitSignal::getExitCode() const
	{
		return m_exitCode;
	}

	void ExitSignal::acquireRenderingThreadSemaphore()
	{
		m_renderingThreadSemaphore.acquire();
	}

	void ExitSignal::releaseRenderingThreadSemaphore()
	{
		m_renderingThreadSemaphore.release();
	}

	void ExitSignal::acquireNetworkThreadSemaphore()
	{
		m_networkThreadSemaphore.acquire();
	}
};
