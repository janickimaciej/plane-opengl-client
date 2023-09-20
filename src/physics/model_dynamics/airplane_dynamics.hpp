#ifndef AIRPLANE_DYNAMICS_HPP
#define AIRPLANE_DYNAMICS_HPP

#include "physics/airplane_params.hpp"
#include "physics/inertia_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/fuselage_params.hpp"
#include "physics/model_dynamics/rigid_body_dynamics.hpp"
#include "physics/propulsion_params.hpp"
#include "physics/surface_params.hpp"
#include "state.hpp"

#include <glm/glm.hpp>

class AirplaneDynamics : public RigidBodyDynamics
{
public:
	AirplaneDynamics(const AirplaneParams& params, const FlightCtrl& flightCtrl);
	virtual ~AirplaneDynamics() = default;

private:
	const AirplaneParams& m_params;
	const FlightCtrl& m_flightCtrl;

	virtual void computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
		glm::vec3& netTorque) const override;

	void addForceAndTorqueInertia(const State& state, glm::vec3& netForce, glm::vec3&)
		const;
	void addForceAndTorqueSurface(const State& state, glm::vec3& netForce, glm::vec3& netTorque)
		const;
	void addForceAndTorqueFuselage(const State& state, glm::vec3& netForce, glm::vec3& netTorque)
		const;
	void addForceAndTorquePropulsion(const State& state, glm::vec3& netForce, glm::vec3& netTorque)
		const;

	glm::vec3 computeAirVelocity(const State& state, const glm::vec3& point) const;
};

#endif
