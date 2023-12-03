#include <GL/glfw3.h>

#include "Window.h"
#include "WindowStates.h"

namespace Uranium::Display {

	explicit WindowStates::WindowStates(Window* window) noexcept :
		window(window),
		restored(false),
		maximized(false),
		minimized(false),
		fullscreen(false)
	{

	}

	void WindowStates::restore() {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		restored = true;
		maximized = false;
		minimized = false;

		// Update resize callback
		//window.getCallback().setHasResized(true);

		// if the window is not in fullscreen mode, we
		// can restore the window manually
		if (!fullscreen) {
			glfwRestoreWindow(window->glWindow);
			return;
		}

		// if the window is on fullscreen mode, we need to
		// handle it in a different way...
		fullscreen = false;

		// Get the current position of the window
		// and keep track of the corresponding values
		int xpos;
		int ypos;
		glfwGetWindowPos(window->glWindow, &xpos, &ypos);

		// Update position without setting a new
		// position with glfw internally
		window->props.position.x = xpos;
		window->props.position.y = ypos;

		// return window to its default dimensions:
		glfwSetWindowMonitor(
			window->glWindow,
			nullptr,                        // current active monitor
			xpos, ypos,                     // position of the extended window
			window->props.dimension.x,      // width of the window
			window->props.dimension.y,      // height of the window
			GLFW_DONT_CARE                  // refreshrate in Hz
		);
	}

	void WindowStates::maximize() {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// if the window is already in fullscreen
		// we don't need to maximize it
		if (fullscreen)
			return;

		restored = false;
		maximized = true;
		minimized = false;

		glfwMaximizeWindow(window->glWindow);

		// Update resize callback
		//window.getCallback().setHasResized(true);
	}

	void WindowStates::minimize() {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// if the window is on fullscreen we don't need
		// to minimize it because the fullscreen mode takes
		// posession of the entire display.
		if (fullscreen)
			return;

		maximized = false;
		minimized = true;

		glfwIconifyWindow(window->glWindow);

		// Update resize callback
		//window.getCallback().setHasResized(true);
	}

	void WindowStates::setFullscreen(bool fullscreen) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// Set the window mode flag to fullscreen
		fullscreen = true;

		if (not monitor.isConnected())
			throw std::invalid_argument(NO_MONITOR_CONNECTED);
		
		// Update resize callback
		//window.getCallback().setHasResized(true);

		// make window fullscreen with:
		glfwSetWindowMonitor(
			window->glWindow,
			monitor,                                  // current active monitor
			0, 0,                                     // position of the extended window
			window->props.resolution.x,               // width of the window
			window->props.resolution.y,               // height of the window
			GLFW_DONT_CARE                            // refreshrate in Hz
		);
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

	bool WindowStates::isFullscreen() const {
		return fullscreen;
	}
}