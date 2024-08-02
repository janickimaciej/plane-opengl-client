#pragma once

#include "app/controllerType.hpp"
#include "physics/playerInput.hpp"

#include <glfw/glfw3.h>

namespace App
{
	class WindowInput
	{
	public:
		WindowInput(GLFWwindow*& window, ControllerType controller);
		const Physics::PlayerInput& getCurrentInput();

	private:
		Physics::PlayerInput m_ownInput{};
		GLFWwindow*& m_window;
		ControllerType m_controller{};

		const Physics::PlayerInput& getCurrentInputKeyboard();
		const Physics::PlayerInput& getCurrentInputGamepad();
	};
};
