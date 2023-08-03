#ifndef RUNGE_KUTTA_RIGHT_HAND_SIDE_HPP
#define RUNGE_KUTTA_RIGHT_HAND_SIDE_HPP

class RungeKuttaRightHandSide
{
public:
	virtual void rightHandSide(float time, const float state[], float result[]) const = 0;
	virtual ~RungeKuttaRightHandSide() = default;
};

#endif
