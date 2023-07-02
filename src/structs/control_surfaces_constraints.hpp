#ifndef CONTROL_SURFACES_CONSTRAINTS
#define CONTROL_SURFACES_CONSTRAINTS

struct ControlSurfacesConstraints {
	float elevatorMinAngleDeg;
	float elevatorMaxAngleDeg;
	float rudderMaxAngleDeg;
	float aileronsMaxAngleDeg;

	ControlSurfacesConstraints(float elevatorMinAngleDeg, float elevatorMaxAngleDeg,
		float rudderMaxAngleDeg, float aileronsMaxAngleDeg);
};

#endif
