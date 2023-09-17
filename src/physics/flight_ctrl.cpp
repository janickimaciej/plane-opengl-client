#include "flight_ctrl.hpp"

//#include "graphics/mesh_instance.hpp"
#include "physics/airplane_params.hpp"

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

float FlightCtrl::getElevatorAngleRad() const
{
	return m_elevatorAngleRad;
}

void FlightCtrl::setElevatorAngleRelative(float angleRelative)
{
	m_elevatorAngleRad = relativeToAbs(angleRelative, m_airplaneParams.hStab.ctrlMinAngleRad,
		m_airplaneParams.hStab.ctrlMaxAngleRad);
	//m_elevator.resetRotation();
	//m_elevator.pitch(-elevatorAngleRad);
}

float FlightCtrl::getRudderAngleRad() const
{
	return m_rudderAngleRad;
}

void FlightCtrl::setRudderAngleRelative(float angleRelative)
{
	m_rudderAngleRad = relativeToAbs(angleRelative, m_airplaneParams.vStab.ctrlMinAngleRad,
		m_airplaneParams.vStab.ctrlMaxAngleRad);
	//m_rudder.resetRotation();
	//m_rudder.yaw(rudderAngleRad);
}

float FlightCtrl::getAileronsAngleRad() const
{
	return m_aileronsAngleRad;
}

void FlightCtrl::setAileronsAngleRelative(float angleRelative)
{
	m_aileronsAngleRad = relativeToAbs(angleRelative, m_airplaneParams.rightWing.ctrlMinAngleRad,
		m_airplaneParams.rightWing.ctrlMaxAngleRad);
	//m_leftAileron.resetRotation();
	//m_leftAileron.pitch(aileronsAngleRad);
	//m_rightAileron.resetRotation();
	//m_rightAileron.pitch(-aileronsAngleRad);
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
