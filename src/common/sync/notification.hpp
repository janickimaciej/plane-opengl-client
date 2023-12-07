#pragma once

#include <mutex>

namespace Common
{
	class Notification
	{
	public:
		void forceGetNotification(int& second, unsigned int& frame);
		void getNotification(int& second, unsigned int& frame);
		void setNotification(int second, unsigned int frame, bool isStateFrame);

	private:
		int m_second{};
		unsigned int m_frame{};
		bool m_unread{};
		std::mutex m_mutex{};
	};
};
