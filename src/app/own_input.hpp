#pragma once

#include "physics/user_input.hpp"

#include <mutex>

namespace App
{
	class OwnInput
	{
	public:
		void setOwnInput(const Physics::UserInput& ownInput);
		Physics::UserInput getOwnInput() const;

	private:
		Physics::UserInput m_ownInput{};
		mutable std::mutex m_mutex{};
	};
};
