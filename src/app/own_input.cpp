#include "app/own_input.hpp"

#include "physics/player_input.hpp"

namespace App
{
	void OwnInput::setOwnInput(const Physics::PlayerInput& ownInput)
	{
		m_mutex.lock();

		m_ownInput = ownInput;

		m_mutex.unlock();
	}

	Physics::PlayerInput OwnInput::getOwnInput() const
	{
		m_mutex.lock();

		Physics::PlayerInput ownInput = m_ownInput;

		m_mutex.unlock();

		return ownInput;
	}
};
