#pragma once

#include "common/airplane_info.hpp"
#include "common/airplane_type_name.hpp"
#include "common/user_input.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/model_dynamics/airplane_dynamics.hpp"
#include "physics/models/model.hpp"

#include <memory>

namespace Physics
{
	class Airplane : public Model
	{
	public:
		Airplane(const Common::AirplaneTypeName& airplaneTypeName);
		Airplane(const Airplane& airplane);
		Airplane(Airplane&& airplane) noexcept;
		void update(const Airplane& previousAirplane);
		Common::AirplaneTypeName getAirplaneTypeName() const;
		Common::AirplaneCtrl getCtrl() const;
		void setCtrl(const Common::UserInput& input);
		virtual ~Airplane() = default;

	private:
		Common::AirplaneTypeName m_airplaneTypeName;
		const AirplaneParams& m_airplaneParams;
		FlightCtrl m_flightCtrl;
		AirplaneDynamics m_dynamics;
	};
};
