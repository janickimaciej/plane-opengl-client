#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include "physics/runge_kutta_right_hand_side.hpp"

#include <array>
#include <cstddef>

template <std::size_t stateLength>
class RungeKutta
{
public:
	RungeKutta() = delete;
	static void RK4(float oldTime, float deltaTime, const std::array<float, stateLength>& oldState,
		const RungeKuttaRightHandSide<stateLength>& rightHandSide,
		std::array<float, stateLength>& newState);
	~RungeKutta() = delete;
};

template <std::size_t stateLength>
void RungeKutta<stateLength>::RK4(float oldTime, float deltaTime,
	const std::array<float, stateLength>& oldState,
	const RungeKuttaRightHandSide<stateLength>& rightHandSide, std::array<float,
	stateLength>& newState)
{
	std::array<std::array<float, stateLength>, 4> k{};

	float time{};
	std::array<float, stateLength> state{};
	
	rightHandSide.rightHandSide(oldTime, oldState, k[0]);

	time = oldTime + deltaTime / 2;
	for (std::size_t i = 0; i < stateLength; ++i)
	{
		state[i] = oldState[i] + deltaTime / 2 * k[0][i];
	}
	rightHandSide.rightHandSide(time, state, k[1]);

	time = oldTime + deltaTime / 2;
	for (std::size_t i = 0; i < stateLength; ++i)
	{
		state[i] = oldState[i] + deltaTime / 2 * k[1][i];
	}
	rightHandSide.rightHandSide(time, state, k[2]);

	time = oldTime + deltaTime;
	for (std::size_t i = 0; i < stateLength; ++i)
	{
		state[i] = oldState[i] + deltaTime * k[2][i];
	}
	rightHandSide.rightHandSide(time, state, k[3]);

	for (std::size_t i = 0; i < stateLength; ++i)
	{
		newState[i] = oldState[i] + deltaTime / 6 * (k[0][i] + 2 * k[1][i] + 2 * k[2][i] + k[3][i]);
	}
}

#endif
