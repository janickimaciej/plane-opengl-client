#include "app/window_input.hpp"

#include "physics/player_input.hpp"

#include <glfw/glfw3.h>

namespace App
{
	WindowInput::WindowInput(GLFWwindow*& window, ControllerType controller) :
		m_window{window},
		m_controller{controller}
	{ }

	const Physics::PlayerInput& WindowInput::getCurrentInput()
	{
		switch (m_controller)
		{
		case ControllerType::keyboard:
			return getCurrentInputKeyboard();

		case ControllerType::gamepad:
			return getCurrentInputGamepad();

		default:
			return getCurrentInputKeyboard();
		}
	}

	const Physics::PlayerInput& WindowInput::getCurrentInputKeyboard()
	{
		int ctrlPitchNegative = glfwGetKey(m_window, GLFW_KEY_UP);
		int ctrlPitchPositive = glfwGetKey(m_window, GLFW_KEY_DOWN);
		m_ownInput.pitch = static_cast<float>(ctrlPitchPositive - ctrlPitchNegative);

		int ctrlYawNegative = glfwGetKey(m_window, GLFW_KEY_A);
		int ctrlYawPositive = glfwGetKey(m_window, GLFW_KEY_D);
		m_ownInput.yaw = static_cast<float>(ctrlYawPositive - ctrlYawNegative);
	
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

	const Physics::PlayerInput& WindowInput::getCurrentInputGamepad()
	{
		GLFWgamepadstate gamepad{};
		glfwGetGamepadState(GLFW_JOYSTICK_1, &gamepad);

		m_ownInput.pitch = gamepad.axes[3];

		m_ownInput.yaw = (gamepad.axes[5] - gamepad.axes[4]) / 2;

		m_ownInput.roll = gamepad.axes[2];

		static bool wasDecreaseThrustPressed = false;
		if (gamepad.buttons[0] == GLFW_PRESS)
		{
			if (!wasDecreaseThrustPressed)
			{
				m_ownInput.thrust -= 0.1f;
			}
			wasDecreaseThrustPressed = true;
		}
		else
		{
			wasDecreaseThrustPressed = false;
		}
		if (m_ownInput.thrust < 0)
		{
			m_ownInput.thrust = 0;
		}

		static bool wasIncreaseThrustPressed = false;
		if (gamepad.buttons[3] == GLFW_PRESS)
		{
			if (!wasIncreaseThrustPressed)
			{
				m_ownInput.thrust += 0.1f;
			}
			wasIncreaseThrustPressed = true;
		}
		else
		{
			wasIncreaseThrustPressed = false;
		}
		if (m_ownInput.thrust > 1)
		{
			m_ownInput.thrust = 1;
		}

		return m_ownInput;
	}
};
