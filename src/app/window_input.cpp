#include "app/window_input.hpp"

#include "common/user_input.hpp"

#include <glfw/glfw3.h>

namespace App
{
	WindowInput::WindowInput(GLFWwindow*& window, ControllerType controller) :
		m_window{window},
		m_controller{controller}
	{ }

	const Common::UserInput& WindowInput::getCurrentInput()
	{
		switch (m_controller)
		{
		case ControllerType::keyboard:
			return getCurrentInputKeyboard();
		default:
			return getCurrentInputKeyboard();
		}
	}

	const Common::UserInput& WindowInput::getCurrentInputKeyboard()
	{
		int ctrlYawNegative = glfwGetKey(m_window, GLFW_KEY_A);
		int ctrlYawPositive = glfwGetKey(m_window, GLFW_KEY_D);
		m_ownInput.yaw = static_cast<float>(ctrlYawPositive - ctrlYawNegative);
	
		int ctrlPitchNegative = glfwGetKey(m_window, GLFW_KEY_UP);
		int ctrlPitchPositive = glfwGetKey(m_window, GLFW_KEY_DOWN);
		m_ownInput.pitch = static_cast<float>(ctrlPitchPositive - ctrlPitchNegative);
	
		int ctrlRollNegative = glfwGetKey(m_window, GLFW_KEY_LEFT);
		int ctrlRollPositive = glfwGetKey(m_window, GLFW_KEY_RIGHT);
		m_ownInput.roll = static_cast<float>(ctrlRollPositive - ctrlRollNegative);
	
		if (glfwGetKey(m_window, GLFW_KEY_0) == GLFW_PRESS ||
		glfwGetKey(m_window, GLFW_KEY_KP_0) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_1) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.1f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_2) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.2f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_3) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.3f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_4) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_4) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.4f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_5) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_5) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.5f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_6) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_6) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.6f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_7) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_7) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.7f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_8) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_8) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.8f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_9) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_9) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0.9f;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_MINUS) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		{
			m_ownInput.thrust = 1;
		}

		return m_ownInput;
	}
};
