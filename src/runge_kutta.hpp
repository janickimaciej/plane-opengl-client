#ifndef RUNGE_KUTTA
#define RUNGE_KUTTA

#include "runge_kutta_right_hand_side.hpp"

class RungeKutta {
public:
	RungeKutta() = delete;
	static void RK4(unsigned int stateLength, float oldTime, float deltaTime, const float oldState[],
		const RungeKuttaRightHandSide& rightHandSide, float newState[]);
	~RungeKutta() = delete;
};

#endif
