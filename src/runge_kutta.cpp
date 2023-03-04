#include "runge_kutta.hpp"

void RungeKutta::RK4(double oldTime, double deltaTime, const double oldState[], double newState[],
	double (*rightSide[])(double time, const double state[]), unsigned int stateLength) {
	double* a = new double[stateLength];
	double* b = new double[stateLength];
	double* c = new double[stateLength];
	double* d = new double[stateLength];

	double time;
	double* state = new double[stateLength];

	for(unsigned int i = 0; i < stateLength; i++) {
		a[i] = (*rightSide[i])(oldTime, oldState);
	}

	time = oldTime + deltaTime/2;
	for(unsigned int i = 0; i < stateLength; i++) {
		state[i] = oldState[i] + deltaTime/2*a[i];
	}
	for(unsigned int i = 0; i < stateLength; i++) {
		b[i] = (*rightSide[i])(time, state);
	}

	time = oldTime + deltaTime/2;
	for(unsigned int i = 0; i < stateLength; i++) {
		state[i] = oldState[i] + deltaTime/2*b[i];
	}
	for(unsigned int i = 0; i < stateLength; i++) {
		c[i] = (*rightSide[i])(time, state);
	}

	time = oldTime + deltaTime;
	for(unsigned int i = 0; i < stateLength; i++) {
		state[i] = oldState[i] + deltaTime*c[i];
	}
	for(unsigned int i = 0; i < stateLength; i++) {
		d[i] = (*rightSide[i])(time, state);
	}

	for(unsigned int i = 0; i < stateLength; i++) {
		newState[i] = oldState[i] + deltaTime/6*(a[i] + 2*b[i] + 2*c[i] + d[i]);
	}

	delete [] a;
	delete [] b;
	delete [] c;
	delete [] d;
	delete [] state;
}
