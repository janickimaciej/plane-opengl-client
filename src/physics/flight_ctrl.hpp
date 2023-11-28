#pragma once

#include "common/airplane_ctrl.hpp"
#include "physics/airplane_params/airplane_params.hpp"

namespace Physics
{
	class FlightCtrl
	{
	public:
		FlightCtrl(const AirplaneParams& airplaneParams);
		float getElevatorAngleRad() const;
		void ctrlPitch(float relative);
		float getRudderAngleRad() const;
		void ctrlYaw(float relative);
		float getAileronsAngleRad() const;
		void ctrlRoll(float relative);
		float getThrustRelative() const;
		void ctrlThrust(float relative);
		Common::AirplaneCtrl getCtrl() const;
	
	private:
		const AirplaneParams& m_airplaneParams;
		Common::AirplaneCtrl m_airplaneCtrl;

		// converts linearly from [-1, 1] to [min, max]
		static float relativeToAbs(float relative, float min, float max);
	};
};
