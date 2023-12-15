#include "app/own_input.hpp"

#include "physics/user_input.hpp"

namespace App
{
	void OwnInput::setOwnInput(const Physics::UserInput& ownInput)
	{
		m_mutex.lock();

		m_ownInput = ownInput;

		m_mutex.unlock();
	}

	Physics::UserInput OwnInput::getOwnInput() const
	{
		m_mutex.lock();

		Physics::UserInput ownInput = m_ownInput;

		m_mutex.unlock();

		return ownInput;
	}
};
