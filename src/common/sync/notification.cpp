#include "common/sync/notification.hpp"

#include "common/frame.hpp"

namespace Common
{
	void Notification::forceGetNotification(int& second, unsigned int& frame)
	{
		m_mutex.lock();

		second = m_second;
		frame = m_frame;
		m_unread = false;

		m_mutex.unlock();
	}

	void Notification::getNotification(int& second, unsigned int& frame)
	{
		m_mutex.lock();

		if (m_unread && earlierThan(m_second, m_frame, second, frame))
		{
			second = m_second;
			frame = m_frame;
		}
		m_unread = false;

		m_mutex.unlock();
	}

	void Notification::setNotification(int second, unsigned int frame, bool isStateFrame)
	{
		m_mutex.lock();

		if (isStateFrame || !m_unread || earlierThan(second, frame, m_second, m_frame))
		{
			m_second = second;
			m_frame = frame;
			m_unread = true;
		}

		m_mutex.unlock();
	}
};
