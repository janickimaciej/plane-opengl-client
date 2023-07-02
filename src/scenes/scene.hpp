#ifndef SCENE
#define SCENE

#include "../shader_program.hpp"
#include "../cameras/camera.hpp"

class Scene {
protected:
	const ShaderProgram& surfaceShaderProgram;
	const ShaderProgram& lightShaderProgram;

	Camera* activeCamera;
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
};

#endif
