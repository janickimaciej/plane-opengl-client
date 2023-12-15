#pragma once

#include "app/controller_type.hpp"
#include "physics/user_input.hpp"

#include <glfw/glfw3.h>

namespace App
{
	class WindowInput
	{
	public:
		WindowInput(GLFWwindow*& window, ControllerType controller);
		const Physics::UserInput& getCurrentInput();

	private:
		Physics::UserInput m_ownInput{};
		GLFWwindow*& m_window;
		ControllerType m_controller{};

		const Physics::UserInput& getCurrentInputKeyboard();
	};
};
