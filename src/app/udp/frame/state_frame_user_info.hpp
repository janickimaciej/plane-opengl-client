#pragma once

#include "common/state.hpp"

#include <bitsery/traits/array.h>

#include <array>
#include <cstddef>

namespace App
{
	inline constexpr std::size_t stateFrameUserInfoSerializedSize = 60;

	struct StateFrameUserInfo
	{
		unsigned char userId{};
		signed char pitch{};
		signed char yaw{};
		signed char roll{};
		unsigned char thrust{};
		bool trigger{};
		unsigned char airplaneType{};
		unsigned char hp{};
		std::array<float, Common::State::stateLength> state{};
	};

	template <typename T>
	void serialize(T& t, StateFrameUserInfo& userInfo)
	{
		t.value1b(userInfo.userId);
		t.value1b(userInfo.pitch);
		t.value1b(userInfo.yaw);
		t.value1b(userInfo.roll);
		t.value1b(userInfo.thrust);
		t.value1b(userInfo.trigger);
		t.value1b(userInfo.airplaneType);
		t.value1b(userInfo.hp);
		t.container4b(userInfo.state);
	}
};
