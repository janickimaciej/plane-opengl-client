#ifndef RUNGE_KUTTA
#define RUNGE_KUTTA

class RungeKutta {
	RungeKutta() { }
public:
	static void RK4(double oldTime, double deltaTime, const double oldState[], double newState[],
		double (*rightSide[])(double time, const double state[]), unsigned int stateLength);
};

#endif
