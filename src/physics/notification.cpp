#include "physics/notification.hpp"

#include "physics/timestep.hpp"

namespace Physics
{
	void Notification::forceGetNotification(Timestep& timestep)
	{
		m_mutex.lock();

		timestep = m_timestep;
		m_unread = false;

		m_mutex.unlock();
	}

	void Notification::getNotification(Timestep& timestep)
	{
		m_mutex.lock();

		if (m_unread && m_timestep < timestep)
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
