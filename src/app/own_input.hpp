#pragma once

#include "physics/player_input.hpp"

#include <mutex>

namespace App
{
	class OwnInput
	{
	public:
		void setOwnInput(const Physics::PlayerInput& ownInput);
		Physics::PlayerInput getOwnInput() const;

	private:
		Physics::PlayerInput m_ownInput{};
		mutable std::mutex m_mutex{};
	};
};
