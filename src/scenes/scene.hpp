#ifndef SCENE_HPP
#define SCENE_HPP

#include "cameras/camera.hpp"
#include "shader_program.hpp"

class Scene
{
public:
	Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void setAspectRatio(float aspectRatio) = 0;
	virtual void setActiveCamera(unsigned int cameraId) = 0;

	virtual void ctrlMoveAlongZNegative() = 0;
	virtual void ctrlMoveAlongZPositive() = 0;
	virtual void ctrlYawNegative() = 0;
	virtual void ctrlYawPositive() = 0;
	virtual void ctrlPitchNegative() = 0;
	virtual void ctrlPitchPositive() = 0;
	virtual void ctrlRollNegative() = 0;
	virtual void ctrlRollPositive() = 0;

	virtual ~Scene() = default;
protected:
	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;

	Camera* m_activeCamera {};
};

#endif
