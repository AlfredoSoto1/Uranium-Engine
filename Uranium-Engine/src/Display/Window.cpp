#include <GL/glew.h>
#include <GL/glfw3.h>

#include "Window.h"

namespace Uranium::Display {

	Window::Window() noexcept :
		glWindow(nullptr),
		hasCreated(false),

		glMajor(3),
		glMinor(3),

		modes(this),
		props(this),
		states(this),
		events(this)
	{
		// Prepare default GLFW window hints before creating
		glfwDefaultWindowHints();

		// First prepare the GLFW hints before
		// creating a window context.
		// This is so the window to be created,
		// can adopt all hints given before its creation

		// Set OpenGL version (optional, but recommended)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
		glfwWindowHint(GLFW_DECORATED, GL_TRUE);
		glfwWindowHint(GLFW_FLOATING, GL_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		glfwWindowHint(GLFW_CENTER_CURSOR, GL_TRUE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		// Create a GLFW window with the given parameters
		//glWindow = glfwCreateWindow(dimension.x, dimension.y, title.c_str(), nullptr, nullptr);

		if (!glWindow)
			throw std::exception("[Exception]: Failed to create window display");

		hasCreated = true;

		//glfwSetWindowUserPointer(glWindow, this);

		// Provide the corresponding values to the hints
		// declared before window creation after the window
		// has initialized correctly.

		// set resize window limits if and only if its resizable
		//if (resizable)
		//	glfwSetWindowSizeLimits(glWindow, Window::MIN_WIDTH, Window::MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

		// set window minimized / maximized if it was a Property setted before
		if (minimized)
			minimize();
		else if (maximized)
			maximize();

		// Update the window Opacity with the established
		// value before window context creation
		setOpacity(opacity);

		// Display the window
		//glfwShowWindow(glWindow);
	}

	Window::~Window() {
#ifdef UR_DEBUG
		if (!glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
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

	Window::operator GLFWwindow* () const {
		return glWindow;
	}

}