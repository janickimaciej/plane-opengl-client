#ifndef CONTROL_SURFACES_CONSTRAINTS
#define CONTROL_SURFACES_CONSTRAINTS

struct ControlSurfacesConstraints {
	float elevatorMinAngleDeg;
	float elevatorMaxAngleDeg;
	float rudderMinAngleDeg;
	float rudderMaxAngleDeg;
	float aileronsMinMaxAngleDeg;
};

#endif
