#include <GLFW/glfw3.h>

#include "MouseCallback.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	MouseCallback::MouseCallback(Window* window) noexcept :
		pressed(GLFW_MOUSE_BUTTON_1),
		released(GLFW_MOUSE_BUTTON_1),
		scroll(0, 0)
	{
		glfwSetScrollCallback(*window,      MouseCallback::scroll_callback);
		glfwSetMouseButtonCallback(*window, MouseCallback::button_callback);
	}

	void MouseCallback::button_callback(GLFWwindow* glWindow, int button, int action, int mods) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		switch (action) {
			case GLFW_PRESS:
			{
				window.mouseCallback->pressed.mouseButton = button;
				window.callbackFunction(window.mouseCallback->pressed);
				break;
			}
			case GLFW_RELEASE:
			{
				window.mouseCallback->released.mouseButton = button;
				window.callbackFunction(window.mouseCallback->released);
				break;
			}
		}
	}

	void MouseCallback::scroll_callback(GLFWwindow* glWindow, double xOffset, double yOffset) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		window.mouseCallback->scroll.xOffset = xOffset;
		window.mouseCallback->scroll.yOffset = yOffset;

		window.callbackFunction(window.mouseCallback->scroll);
	}
}
