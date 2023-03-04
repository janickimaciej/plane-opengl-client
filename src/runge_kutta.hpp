#ifndef RUNGE_KUTTA
#define RUNGE_KUTTA

class RungeKutta {
	RungeKutta() { }
public:
	static void RK4(unsigned int stateLength, double oldTime, double deltaTime, const double oldState[],
		double (*rightSide)(double time, const double state[], double result[]), double newState[]);
};

#endif
