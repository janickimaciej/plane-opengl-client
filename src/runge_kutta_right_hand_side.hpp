#ifndef RUNGE_KUTTA_RIGHT_HAND_SIDE
#define RUNGE_KUTTA_RIGHT_HAND_SIDE

class RungeKuttaRightHandSide {
public:
	virtual void rightHandSide(float time, const float state[], float result[]) const = 0;
	virtual ~RungeKuttaRightHandSide() = default;
};

#endif
