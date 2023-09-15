#include "flight_ctrl.hpp"

//#include "mesh_instance.hpp"
#include "structs/airplane_params.hpp"

FlightCtrl::FlightCtrl(/*MeshInstance& elevator, MeshInstance& rudder,
	MeshInstance& leftAileron, MeshInstance& rightAileron,
	*/const AirplaneParams& airplaneParams) :
	/*m_elevator{elevator},
	m_rudder{rudder},
	m_leftAileron{leftAileron},
	m_rightAileron{rightAileron},*/
	m_airplaneParams{airplaneParams}
{
	setElevatorAngleRelative(0);
	setRudderAngleRelative(0);
	setAileronsAngleRelative(0);
	setThrustRelative(0);
}

float FlightCtrl::getElevatorAngleDeg() const
{
	return m_elevatorAngleDeg;
}

void FlightCtrl::setElevatorAngleRelative(float angleRelative)
{
	m_elevatorAngleDeg = relativeToAbs(angleRelative, m_airplaneParams.hStab.ctrlMinAngleDeg,
		m_airplaneParams.hStab.ctrlMaxAngleDeg);
	//m_elevator.resetRotation();
	//m_elevator.pitch(-elevatorAngleDeg);
}

float FlightCtrl::getRudderAngleDeg() const
{
	return m_rudderAngleDeg;
}

void FlightCtrl::setRudderAngleRelative(float angleRelative)
{
	m_rudderAngleDeg = relativeToAbs(angleRelative, m_airplaneParams.vStab.ctrlMinAngleDeg,
		m_airplaneParams.vStab.ctrlMaxAngleDeg);
	//m_rudder.resetRotation();
	//m_rudder.yaw(rudderAngleDeg);
}

float FlightCtrl::getAileronsAngleDeg() const
{
	return m_aileronsAngleDeg;
}

void FlightCtrl::setAileronsAngleRelative(float angleRelative)
{
	m_aileronsAngleDeg = relativeToAbs(angleRelative, m_airplaneParams.wings.ctrlMinAngleDeg,
		m_airplaneParams.wings.ctrlMaxAngleDeg);
	//m_leftAileron.resetRotation();
	//m_leftAileron.pitch(aileronsAngleDeg);
	//m_rightAileron.resetRotation();
	//m_rightAileron.pitch(-aileronsAngleDeg);
}

float FlightCtrl::getThrustRelative() const
{
	return m_thrustRelative;
}

void FlightCtrl::setThrustRelative(float relative)
{
	m_thrustRelative = relative;
}

float FlightCtrl::relativeToAbs(float relative, float min, float max) const
{
	return (min + max + relative * (max - min)) / 2;
}
