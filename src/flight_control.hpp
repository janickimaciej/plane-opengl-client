#ifndef FLIGHT_CONTROL
#define FLIGHT_CONTROL

#include "mesh_instance.hpp"
#include "structs/control_surfaces_constraints.hpp"

class FlightControl {
	//MeshInstance& elevator;
	//MeshInstance& rudder;
	//MeshInstance& leftAileron;
	//MeshInstance& rightAileron;

	const ControlSurfacesConstraints& controlSurfacesConstraints;
	float elevatorAngleDeg;
	float rudderAngleDeg;
	float aileronsAngleDeg;
	float thrustRelative;
public:
	FlightControl(/*MeshInstance& elevator, MeshInstance& rudder, MeshInstance& leftAileron,
		MeshInstance& rightAileron, */const ControlSurfacesConstraints& controlSurfacesConstraints);
	float getElevatorAngleDeg() const;
	void setElevatorAngleRelative(float angleRelative);
	float getRudderAngleDeg() const;
	void setRudderAngleRelative(float angleRelative);
	float getAileronsAngleDeg() const;
	void setAileronsAngleRelative(float angleRelative);
	float getThrustRelative() const;
	void setThrustRelative(float relative);
};

#endif
