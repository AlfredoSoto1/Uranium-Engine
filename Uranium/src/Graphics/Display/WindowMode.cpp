#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>

#include "Window.h"
#include "Monitor.h"

#include "WindowMode.h"
#include "WindowProps.h"

#include "Input/Callbacks/WindowCallback.h"

namespace Uranium::Graphics::Display {

	// 
	// WindowMode - private defined error messages
	//
	constexpr const char* NO_MONITOR_CONNECTED = "There should be atleast one monitor connected";

	// 
	// WindowMode class implementation
	// 
	WindowMode::WindowMode() :
		glWindow(nullptr),

		visible(true),
		resizable(true),
		decorated(true),
		fullscreen(false),
		alwaysOnTop(false),

		maximized(false),
		minimized(false)
	{
	}

	void WindowMode::initDefault() const {
		glfwWindowHint(GLFW_VISIBLE,   visible     ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_DECORATED, decorated   ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_FLOATING,  alwaysOnTop ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, maximized   ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, resizable   ? GL_TRUE : GL_FALSE);
	}

	void WindowMode::setVisible(bool visible) {
		this->visible = visible;
		if (not glWindow) return;

		if (visible)
			glfwShowWindow(glWindow);
		else
			glfwHideWindow(glWindow);
	}

	void WindowMode::setResizable(bool resizable) {
		this->resizable = resizable;
		if (glWindow) glfwSetWindowAttrib(glWindow, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
	}

	void WindowMode::setDecorated(bool decorated) {
		this->decorated = decorated;
		if (glWindow) glfwSetWindowAttrib(glWindow, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
	}
	void WindowMode::setAlwaysOnTop(bool alwaysOnTop) {
		this->alwaysOnTop = alwaysOnTop;
		if (glWindow) glfwSetWindowAttrib(glWindow, GLFW_FLOATING, alwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
	}

	void WindowMode::maximize() {
		if (fullscreen)
			return;

		maximized = true;
		minimized = false;
		if (glWindow == nullptr)
			return;
		glfwMaximizeWindow(glWindow);

		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
		window.getCallback().setHasResized(true);
	}

	void WindowMode::minimize() {
		if (fullscreen)
			return;
		
		maximized = false;
		minimized = true;
		if (glWindow == nullptr)
			return;
		glfwIconifyWindow(glWindow);

		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
		window.getCallback().setHasResized(true);
	}

	void WindowMode::restore() {
		
		maximized = false;
		minimized = false;
		if (glWindow == nullptr)
			return;

		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
		window.getCallback().setHasResized(true);

		if (not fullscreen) {
			glfwRestoreWindow(glWindow);
			return;
		}

		fullscreen = false;

		// Get the current position of the window
		// and keep track of the corresponding values
		int xpos;
		int ypos;
		glfwGetWindowPos(glWindow, &xpos, &ypos);

		// Update position without setting a new
		// position with glfw internally
		window.getProps().getPosition().x = xpos;
		window.getProps().getPosition().y = ypos;

		// return window to its default dimensions:
		glfwSetWindowMonitor(
			glWindow,
			nullptr,                                 // current active monitor
			xpos, ypos,                              // position of the extended window
			window.getProps().getDimension().width,  // width of the window
			window.getProps().getDimension().height, // height of the window
			GLFW_DONT_CARE                           // refreshrate in Hz
		);
	}

	void WindowMode::setFullscreen(const Monitor& monitor) {
		// Set the window mode flag to fullscreen
		fullscreen = true;

		if (glWindow == nullptr)
			return;

		if (not monitor.isConnected())
			throw std::invalid_argument(NO_MONITOR_CONNECTED);

		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
		window.getCallback().setHasResized(true);

		// make window fullscreen with:
		glfwSetWindowMonitor(
			glWindow,
			monitor,                                  // current active monitor
			0, 0,                                     // position of the extended window
			window.getProps().getResolution().width,  // width of the window
			window.getProps().getResolution().height, // height of the window
			GLFW_DONT_CARE                            // refreshrate in Hz
		);
	}
}