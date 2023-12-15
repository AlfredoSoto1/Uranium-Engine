#include <GL/glfw3.h>

#include "Window.h"
#include "WindowEvents.h"

namespace Uranium::Platform::Display {

	WindowEvents::WindowEvents(Window* window) noexcept :
		window(window)
	{

	}

	void WindowEvents::close() {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		glfwSetWindowShouldClose(window->glWindow, GLFW_TRUE);
	}

	void WindowEvents::focus() {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		glfwFocusWindow(window->glWindow);
	}

	void WindowEvents::requestAttention() {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		glfwRequestWindowAttention(window->glWindow);
	}

	bool WindowEvents::shouldClose() const {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		return glfwWindowShouldClose(window->glWindow);
	}

}