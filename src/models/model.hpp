#ifndef MODEL_HPP
#define MODEL_HPP

#include "graphics/shader_program.hpp"
#include "movable.hpp"
#include "state.hpp"

#include <glm/glm.hpp>

class Model : public Movable
{
public:
	void render() const;
	glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;

	virtual void setState(const State& newState) override;

	virtual void scale(float scaleRatio) override; // locally
	virtual void rotate(const glm::vec3& axis, float angleDeg) override; // locally
	virtual void resetRotation() override; // locally
	virtual void translate(const glm::vec3& translation) override;

	virtual void rotatePitch(float angleDeg) override; // locally
	virtual void rotateYaw(float angleDeg) override; // locally
	virtual void rotateRoll(float angleDeg) override; // locally
	virtual void moveZ(float distance) override; // locally

protected:
	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;
	
	Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);
	virtual void updateShaderLightMatrix() const = 0;
	virtual void renderSurfaces() const = 0;
	virtual void renderLights() const = 0;
	virtual ~Model() = default;
};

#endif
