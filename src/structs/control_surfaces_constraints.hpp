#ifndef CONTROL_SURFACES_CONSTRAINTS_HPP
#define CONTROL_SURFACES_CONSTRAINTS_HPP

struct ControlSurfacesConstraints
{
	float elevatorMinAngleDeg{};
	float elevatorMaxAngleDeg{};
	float rudderMaxAngleDeg{};
	float aileronsMaxAngleDeg{};

	ControlSurfacesConstraints(float elevatorMinAngleDeg, float elevatorMaxAngleDeg,
		float rudderMaxAngleDeg, float aileronsMaxAngleDeg);
};

#endif
