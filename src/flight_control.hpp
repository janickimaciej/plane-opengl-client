#ifndef FLIGHT_CONTROL_HPP
#define FLIGHT_CONTROL_HPP

//#include "mesh_instance.hpp"
#include "structs/control_surfaces_constraints.hpp"

class FlightControl
{
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
	
private:
	//MeshInstance& m_elevator;
	//MeshInstance& m_rudder;
	//MeshInstance& m_leftAileron;
	//MeshInstance& m_rightAileron;

	const ControlSurfacesConstraints& m_controlSurfacesConstraints;
	float m_elevatorAngleDeg {};
	float m_rudderAngleDeg {};
	float m_aileronsAngleDeg {};
	float m_thrustRelative {};
};

#endif
