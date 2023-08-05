#ifndef MODEL_HPP
#define MODEL_HPP

#include "movable.hpp"
#include "shader_program.hpp"
#include "structs/state.hpp"

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

	virtual void pitch(float angleDeg) override; // locally
	virtual void yaw(float angleDeg) override; // locally
	virtual void roll(float angleDeg) override; // locally
	virtual void moveAlongZ(float distance) override; // locally

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
