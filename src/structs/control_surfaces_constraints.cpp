#include "structs/control_surfaces_constraints.hpp"

ControlSurfacesConstraints::ControlSurfacesConstraints(float elevatorMinAngleDeg,
	float elevatorMaxAngleDeg, float rudderMaxAngleDeg, float aileronsMaxAngleDeg) :
	elevatorMinAngleDeg { elevatorMinAngleDeg },
	elevatorMaxAngleDeg { elevatorMaxAngleDeg },
	rudderMaxAngleDeg { rudderMaxAngleDeg },
	aileronsMaxAngleDeg { aileronsMaxAngleDeg }
{ }
