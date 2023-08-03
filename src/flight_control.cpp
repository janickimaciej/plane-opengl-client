#include "flight_control.hpp"

//#include "mesh_instance.hpp"
#include "structs/control_surfaces_constraints.hpp"

FlightControl::FlightControl(/*MeshInstance& elevator, MeshInstance& rudder,
	MeshInstance& leftAileron, MeshInstance& rightAileron,
	*/const ControlSurfacesConstraints& controlSurfacesConstraints) :
	/*m_elevator { elevator },
	m_rudder { rudder },
	m_leftAileron { leftAileron },
	m_rightAileron { rightAileron },*/
	m_controlSurfacesConstraints { controlSurfacesConstraints }
{
	setElevatorAngleRelative(0);
	setRudderAngleRelative(0);
	setAileronsAngleRelative(0);
	setThrustRelative(0);
}

float FlightControl::getElevatorAngleDeg() const
{
	return m_elevatorAngleDeg;
}

void FlightControl::setElevatorAngleRelative(float angleRelative)
{
	m_elevatorAngleDeg = (m_controlSurfacesConstraints.elevatorMinAngleDeg +
		m_controlSurfacesConstraints.elevatorMaxAngleDeg + angleRelative *
		(m_controlSurfacesConstraints.elevatorMaxAngleDeg -
		m_controlSurfacesConstraints.elevatorMinAngleDeg)) / 2;
	//m_elevator.resetRotation();
	//m_elevator.pitch(-elevatorAngleDeg);
}

float FlightControl::getRudderAngleDeg() const
{
	return m_rudderAngleDeg;
}

void FlightControl::setRudderAngleRelative(float angleRelative)
{
	m_rudderAngleDeg = angleRelative * m_controlSurfacesConstraints.rudderMaxAngleDeg;
	//m_rudder.resetRotation();
	//m_rudder.yaw(rudderAngleDeg);
}

float FlightControl::getAileronsAngleDeg() const
{
	return m_aileronsAngleDeg;
}

void FlightControl::setAileronsAngleRelative(float angleRelative)
{
	m_aileronsAngleDeg = angleRelative * m_controlSurfacesConstraints.aileronsMaxAngleDeg;
	//m_leftAileron.resetRotation();
	//m_leftAileron.pitch(aileronsAngleDeg);
	//m_rightAileron.resetRotation();
	//m_rightAileron.pitch(-aileronsAngleDeg);
}

float FlightControl::getThrustRelative() const
{
	return m_thrustRelative;
}

void FlightControl::setThrustRelative(float relative)
{
	m_thrustRelative = relative;
}
