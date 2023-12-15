#include "physics/notification.hpp"

#include "physics/simulation_clock.hpp"
#include "physics/timestep.hpp"

namespace Physics
{
	Notification::Notification(const SimulationClock& simulationClock) :
		m_simulationClock{simulationClock}
	{ }

	void Notification::forceGetNotification(Timestep& timestep)
	{
		m_mutex.lock();

		timestep = m_timestep;
		m_unread = false;

		m_mutex.unlock();
	}

	void Notification::getNotification(Timestep& timestep)
	{
		constexpr Timestep ignoringOffset{0,
			static_cast<unsigned int>(framesPerSecond * 0.9f)};
		if (timestep < m_simulationClock.getTime() - ignoringOffset)
		{
			m_ignoring = true;
		}
		else
		{
			m_ignoring = false;
		}

		m_mutex.lock();

		if (!m_ignoring && m_unread && m_timestep < timestep)
		{
			timestep = m_timestep;
		}
		m_unread = false;

		m_mutex.unlock();
	}

	void Notification::setNotification(const Timestep& timestep, bool isStateFrame)
	{
		m_mutex.lock();

		if (isStateFrame || !m_unread || timestep < m_timestep)
		{
			m_timestep = timestep;
			m_unread = true;
		}

		m_mutex.unlock();
	}
};
