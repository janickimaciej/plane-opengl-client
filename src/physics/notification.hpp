#pragma once

#include "physics/timestep.hpp"

#include <mutex>

namespace Physics
{
	class Notification
	{
	public:
		void forceGetNotification(Timestep& timestep);
		void getNotification(Timestep& timestep);
		void setNotification(const Timestep& timestep, bool isStateFrame);

	private:
		Timestep m_timestep{};
		bool m_unread{};
		std::mutex m_mutex{};
	};
};
