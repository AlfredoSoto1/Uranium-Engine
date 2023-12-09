#include <GL/glew.h>
#include <GL/glfw3.h>

#include "Window.h"

namespace Uranium::Display {

	Window::Window() noexcept :
		glWindow(nullptr),

		glMajor(3),
		glMinor(3),

		modes(this),
		props(this),
		states(this),
		events(this)
	{
		// Prepare default GLFW window hints before creating
		glfwDefaultWindowHints();

		// Set OpenGL version (optional, but recommended)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		// Prepare the custom default window hints before creation
		glfwWindowHint(GLFW_VISIBLE,   GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_FLOATING,  GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

		// Create a GLFW window with the given parameters
		glWindow = glfwCreateWindow(props.getDimension().x, props.getDimension().y, props.getTitle().c_str(), nullptr, nullptr);

		if (!glWindow)
			throw std::exception("[Exception]: Failed to create window display");

		glfwSetWindowUserPointer(glWindow, this);

		// Set resize window limits if and only if its resizable
		if (modes.isResizable())
			glfwSetWindowSizeLimits(glWindow, WindowProps::MIN_WIDTH, WindowProps::MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

		glfwShowWindow(glWindow);
	}

	Window::~Window() {
		if (!glWindow)
			return;
		// Hide the current visible window
		// and free all resources used for
		// generating *this* window instance
		glfwHideWindow(glWindow);
		glfwDestroyWindow(glWindow);
	}

	Window::operator GLFWwindow* () const {
		return glWindow;
	}

	bool Window::isCurrent() const {
#ifdef UR_DEBUG
		if (!glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		return glfwGetCurrentContext() == glWindow;
	}

	auto Window::getModes() -> WindowModes& {
		return modes;
	}

	auto Window::getStates() -> WindowStates& {
		return states;
	}

	auto Window::getEvents() -> WindowEvents& {
		return events;
	}

	auto Window::getProperties() -> WindowProps& {
		return props;
	}
}