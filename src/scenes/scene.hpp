#ifndef SCENE_HPP
#define SCENE_HPP

#include "graphics/cameras/camera.hpp"
#include "graphics/shader_program.hpp"

class Scene
{
public:
	Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void setAspectRatio(float aspectRatio) = 0;
	virtual void setActiveCamera(unsigned int cameraId) = 0;
	
	virtual void ctrlPitch(float relative) = 0;
	virtual void ctrlYaw(float relative) = 0;
	virtual void ctrlRoll(float relative) = 0;
	virtual void ctrlThrust(float relative) = 0;

	virtual ~Scene() = default;
protected:
	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;

	Camera* m_activeCamera{};
};

#endif
