#include "app/own_input.hpp"

namespace App
{
	void OwnInput::setOwnInput(const Common::UserInput& ownInput)
	{
		m_mutex.lock();

		m_ownInput = ownInput;

		m_mutex.unlock();
	}

	Common::UserInput OwnInput::getOwnInput() const
	{
		m_mutex.lock();

		Common::UserInput ownInput = m_ownInput;

		m_mutex.unlock();

		return ownInput;
	}
};
