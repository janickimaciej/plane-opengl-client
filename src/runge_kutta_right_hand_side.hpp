#ifndef RUNGE_KUTTA_RIGHT_HAND_SIDE_HPP
#define RUNGE_KUTTA_RIGHT_HAND_SIDE_HPP

#include <array>

template <size_t stateLength>
class RungeKuttaRightHandSide
{
public:
	virtual void rightHandSide(float time, const std::array<float, stateLength>& state,
		std::array<float, stateLength>& stateDerivative) const = 0;
	virtual ~RungeKuttaRightHandSide() = default;
};

#endif
