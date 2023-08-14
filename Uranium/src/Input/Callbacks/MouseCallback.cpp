#include <iostream>
#include <GLFW/glfw3.h>

#include "MouseCallback.h"

#include "Graphics/UI/Cursor.h"
#include "Graphics/Display/Window.h"
#include "Graphics/Display/WindowProps.h"

namespace Uranium::Input::Callbacks {

	MouseCallback::MouseCallback(Window* window) :
		window(window), 

		mouseButtons(nullptr)
	{
		// create bool array containing
		// mouse button activation flag
		// for each button when being interacted with
		mouseButtons = new bool[GLFW_MOUSE_BUTTON_LAST];

		glfwSetScrollCallback(*window,      MouseCallback::scrollDetected);
		glfwSetCursorPosCallback(*window,   MouseCallback::positionDetected);
		glfwSetMouseButtonCallback(*window, MouseCallback::clickDetected);
	}

	MouseCallback::~MouseCallback() {
		delete[] mouseButtons;

		glfwSetScrollCallback(*window,      nullptr);
		glfwSetCursorPosCallback(*window,   nullptr);
		glfwSetMouseButtonCallback(*window, nullptr);
	}

	void MouseCallback::clickDetected(GLFWwindow* window, int button, int action, int mods) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update mouse button actions
		//program->getMouseCallback()->mouseButtons[button] = action != GLFW_RELEASE;
	}

	void MouseCallback::scrollDetected(GLFWwindow* window, double xOffset, double yOffset) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;
	}

	void MouseCallback::positionDetected(GLFWwindow* window, double xpos, double ypos) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// save window size for later use
		//unsigned int width = program->getWindow()->getProperties().getWidth();
		//unsigned int height = program->getWindow()->getProperties().getHeight();

		//// change cursor position
		//program->getCursor()->xPosition = xpos;
		//program->getCursor()->yPosition = ypos;

		//// change cursor position in normal coordinates
		//program->getCursor()->setNormPosition((xpos * 2.0) / width - 1.0, -(ypos * 2.0) / height + 1.0);
	}

	bool MouseCallback::isButtonDown(int button) {
		if (button < 0)
			return false;
		return mouseButtons[button] ? true : false;
	}

	int MouseCallback::isMouseToggled(int button) {
		return 0;
	}
}
