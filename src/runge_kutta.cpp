#include "runge_kutta.hpp"

void RungeKutta::RK4(unsigned int stateLength, double oldTime, double deltaTime, const double oldState[],
	double (*rightSide)(double time, const double state[], double result[]), double newState[]) {
	double* k[4] { };
	for(int i = 0; i < 4; i++) {
		k[i] = new double[stateLength];
	}

	double time;
	double* state = new double[stateLength];
	
	(*rightSide)(oldTime, oldState, k[0]);

	time = oldTime + deltaTime/2;
	for(unsigned int i = 0; i < stateLength; i++) {
		state[i] = oldState[i] + deltaTime/2*k[0][i];
	}
	(*rightSide)(time, state, k[1]);

	time = oldTime + deltaTime/2;
	for(unsigned int i = 0; i < stateLength; i++) {
		state[i] = oldState[i] + deltaTime/2*k[1][i];
	}
	(*rightSide)(time, state, k[2]);

	time = oldTime + deltaTime;
	for(unsigned int i = 0; i < stateLength; i++) {
		state[i] = oldState[i] + deltaTime*k[2][i];
	}
	(*rightSide)(time, state, k[3]);

	for(unsigned int i = 0; i < stateLength; i++) {
		newState[i] = oldState[i] + deltaTime/6*(k[0][i] + 2*k[1][i] + 2*k[2][i] + k[3][i]);
	}

	for(int i = 0; i < 4; i++) {
		delete [] k[i];
	}
	delete [] state;
}
