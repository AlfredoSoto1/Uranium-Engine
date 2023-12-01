#include <GL/glfw3.h>

#include "Window.h"
#include "WindowStates.h"

namespace Uranium::Display {

	explicit WindowStates::WindowStates(Window* window) noexcept :
		window(window),
		restored(false),
		maximized(false),
		minimized(false)
	{

	}

	void WindowStates::restore() {
		restored = true;
		maximized = false;
		minimized = false;

		// if glwindow is not valid, do nothing
		if (!window->glWindow)
			return;

		// update resize var
		//window.getCallback().setHasResized(true);

		if (!window->modes.isFullscreen()) {
			glfwRestoreWindow(window->glWindow);
			return;
		}

		window->modes.setFullscreen(false);

		// Get the current position of the window
		// and keep track of the corresponding values
		int xpos;
		int ypos;
		glfwGetWindowPos(window->glWindow, &xpos, &ypos);

		// Update position without setting a new
		// position with glfw internally
		window->props.getPosition().x = xpos;
		window->props.getPosition().y = ypos;

		// return window to its default dimensions:
		glfwSetWindowMonitor(
			window->glWindow,
			nullptr,                        // current active monitor
			xpos, ypos,                     // position of the extended window
			window->props.getDimension().x, // width of the window
			window->props.getDimension().y, // height of the window
			GLFW_DONT_CARE                  // refreshrate in Hz
		);
	}

	void WindowStates::maximize() {
		if (fullscreen)
			return;

		restored = false;
		maximized = true;
		minimized = false;

		if (!window->glWindow)
			return;
		glfwMaximizeWindow(window->glWindow);

		// update callback
		//window.getCallback().setHasResized(true);
	}

	void WindowStates::minimize() {
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

	bool WindowStates::isRestored()  const {
		return restored;
	}

	bool WindowStates::isMaximized() const {
		return maximized;
	}

	bool WindowStates::isMinimized() const {
		return minimized;
	}
}