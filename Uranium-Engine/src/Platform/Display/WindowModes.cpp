#include <GL/glfw3.h>

#include "Window.h"
#include "WindowModes.h"

namespace Uranium::Platform::Display {

	WindowModes::WindowModes(Window* window) noexcept :
		window(window),
		visible(true),
		resizable(true),
		decorated(true),
		alwaysOnTop(false)
	{
		
	}

	auto WindowModes::isVisible()     const -> bool {
		return visible;
	}

	auto WindowModes::isResizable()   const -> bool {
		return resizable;
	}

	auto WindowModes::isDecorated()   const -> bool {
		return decorated;
	}

	auto WindowModes::isAlwaysOnTop() const -> bool {
		return alwaysOnTop;
	}

	void WindowModes::setVisible(bool visible) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// Update visibility flag
		this->visible = visible;

		if (visible)
			glfwShowWindow(window->glWindow);
		else
			glfwHideWindow(window->glWindow);
	}

	void WindowModes::setResizable(bool resizable) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// Update resize mode flag
		this->resizable = resizable;

		glfwSetWindowAttrib(window->glWindow, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
	}

	void WindowModes::setDecorated(bool decorated) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// Update decorated flag
		this->decorated = decorated;
		
		glfwSetWindowAttrib(window->glWindow, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
	}

	void WindowModes::setAlwaysOnTop(bool alwaysOnTop) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// Update always on top flag
		this->alwaysOnTop = alwaysOnTop;

		glfwSetWindowAttrib(window->glWindow, GLFW_FLOATING, alwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
	}

}