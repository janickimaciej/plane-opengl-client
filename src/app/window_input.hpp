#pragma once

#include "app/controller_type.hpp"
#include "common/user_input.hpp"

#include <glfw/glfw3.h>

namespace App
{
	class WindowInput
	{
	public:
		WindowInput(GLFWwindow*& window, ControllerType controller);
		const Common::UserInput& getCurrentInput();

	private:
		Common::UserInput m_ownInput{};
		GLFWwindow*& m_window;
		ControllerType m_controller{};

		const Common::UserInput& getCurrentInputKeyboard();
	};
};
