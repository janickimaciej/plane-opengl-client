#pragma once

#include "common/sync/user_input.hpp"

#include <mutex>

namespace App
{
	class OwnInput
	{
	public:
		void setOwnInput(const Common::UserInput& ownInput);
		Common::UserInput getOwnInput() const;

	private:
		Common::UserInput m_ownInput{};
		mutable std::mutex m_mutex{};
	};
};
