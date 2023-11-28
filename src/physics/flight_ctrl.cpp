#include "flight_ctrl.hpp"

//#include "graphics/submodel.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/airplane_params/surface_params.hpp"

namespace Physics
{
	FlightCtrl::FlightCtrl(const AirplaneParams& airplaneParams) :
		m_airplaneParams{airplaneParams}
	{
		ctrlPitch(0);
		ctrlYaw(0);
		ctrlRoll(0);
		ctrlThrust(0);
	}

	float FlightCtrl::getElevatorAngleRad() const
	{
		return m_airplaneCtrl.elevatorAngleRad;
	}

	void FlightCtrl::ctrlPitch(float relative)
	{
		m_airplaneCtrl.elevatorAngleRad = relativeToAbs(relative,
			m_airplaneParams.hStab.ctrlMinAngleRad, m_airplaneParams.hStab.ctrlMaxAngleRad);
	}

	float FlightCtrl::getRudderAngleRad() const
	{
		return m_airplaneCtrl.rudderAngleRad;
	}

	void FlightCtrl::ctrlYaw(float relative)
	{
		m_airplaneCtrl.rudderAngleRad = relativeToAbs(relative,
			m_airplaneParams.vStab.ctrlMinAngleRad, m_airplaneParams.vStab.ctrlMaxAngleRad);
	}

	float FlightCtrl::getAileronsAngleRad() const
	{
		return m_airplaneCtrl.aileronsAngleRad;
	}

	void FlightCtrl::ctrlRoll(float relative)
	{
		m_airplaneCtrl.aileronsAngleRad = relativeToAbs(relative,
			m_airplaneParams.rightWing.ctrlMinAngleRad, m_airplaneParams.rightWing.ctrlMaxAngleRad);
	}

	float FlightCtrl::getThrustRelative() const
	{
		return m_airplaneCtrl.thrustRelative;
	}

	void FlightCtrl::ctrlThrust(float relative)
	{
		m_airplaneCtrl.thrustRelative = relative;
	}

	Common::AirplaneCtrl FlightCtrl::getCtrl() const
	{
		return m_airplaneCtrl;
	}

	float FlightCtrl::relativeToAbs(float relative, float min, float max)
	{
		return (min + max + relative * (max - min)) / 2;
	}
};
