#include "app/windowInput.hpp"

#include "physics/playerInput.hpp"

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
		int ctrlPitchNegative = glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS;
		int ctrlPitchPositive = glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS;
		m_ownInput.pitch = static_cast<float>(ctrlPitchPositive - ctrlPitchNegative);

		int ctrlYawNegative = glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS;
		int ctrlYawPositive = glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS;
		m_ownInput.yaw = static_cast<float>(ctrlYawPositive - ctrlYawNegative);
	
		int ctrlRollNegative = glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS;
		int ctrlRollPositive = glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS;
		m_ownInput.roll = static_cast<float>(ctrlRollPositive - ctrlRollNegative);
	
		static bool wasDecreaseThrustPressed = false;
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
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
		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
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

		if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			m_ownInput.thrust = 0;
		}

		if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
		{
			m_ownInput.thrust = 1;
		}

		m_ownInput.trigger = glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS;

		return m_ownInput;
	}

	const Physics::PlayerInput& WindowInput::getCurrentInputGamepad()
	{
		GLFWgamepadstate gamepad{};
		glfwGetGamepadState(GLFW_JOYSTICK_1, &gamepad);

		m_ownInput.pitch = gamepad.axes[1];

		m_ownInput.yaw = (gamepad.axes[5] - gamepad.axes[4]) / 2;

		m_ownInput.roll = gamepad.axes[0];

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

		if (gamepad.buttons[2] == GLFW_PRESS)
		{
			m_ownInput.thrust = 0;
		}

		if (gamepad.buttons[1] == GLFW_PRESS)
		{
			m_ownInput.thrust = 1;
		}

		m_ownInput.trigger = gamepad.buttons[5] == GLFW_PRESS;

		return m_ownInput;
	}
};
