#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "WindowHint.h"
#include "WindowMode.h"
#include "WindowProps.h"
#include "Uranium/Utils/Dimension.h"
#include "Uranium/Core/EngineTools.h"
#include "Uranium/Core/Application.h"

namespace Uranium::Graphics::Display {

	// 
	// Window - private defined error messages
	// 
	constexpr const char* NO_CONTEXT_ERROR = "'this' window has no GLFW context.";
	constexpr const char* FAILED_GLEW_INIT = "Failed to initiate GLEW.";
	constexpr const char* FAILED_WINDOW_CREATION = "Window could not be created.";
	constexpr const char* OUT_OF_APPLICATION_SCOPE = "Window must be created inside the application.";

	// 
	// Window class implementation
	// 

	Window::Window(const WindowProps& windowProps, const WindowMode& windowMode, const Monitor& monitor) :
		glWindow(nullptr),
		monitor(monitor),
		windowMode(windowMode),
		windowProps(windowProps),

		resized(false)
	{
		// 
		// Prepare default window hints
		// 
		debug_break(not Core::Application::isGLFWActive(), OUT_OF_APPLICATION_SCOPE);

		glfwDefaultWindowHints();

		// Set OpenGL version (optional, but recommended)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowProps.mayorGLVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowProps.minorGLVersion);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		// Prepare window explicit hints before creation
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_VISIBLE,   windowMode.visible     ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_DECORATED, windowMode.decorated   ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_FLOATING,  windowMode.alwaysOnTop ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, windowMode.maximized   ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, windowMode.resizable   ? GL_TRUE : GL_FALSE);
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparency < 100 ? GL_TRUE : GL_FALSE);
		//glfwWindowHint(GLFW_CENTER_CURSOR,				is_CursorCentered				? GL_TRUE : GL_FALSE);
	}

	Window::~Window() {
		dispose();
	}

	void Window::create() {
		// Create a GLFW window with the given parameters
		glWindow = glfwCreateWindow(windowProps.dimension.width, windowProps.dimension.height, windowProps.title.c_str(), nullptr, nullptr);

		if (not glWindow)
			throw std::exception(FAILED_WINDOW_CREATION);

		// 
		// Provide the corresponding values to the hints
		// declared before window creation after the window
		// has initialized correctly.
		//

		// set resize window limits if and only if its resizable
		if (windowMode.resizable)
			glfwSetWindowSizeLimits(glWindow, WindowProps::MIN_WIDTH, WindowProps::MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

		// set window minimized / maximized if it was a Property setted before
		//if (windowProps.minimized)
		//	minimize();
		//else if (windowProps.maximized)
		//	maximize();

		// set window transparency if it was a Property setted before
		//if (windowProps.opacity < 100)
		//	windowProps->setWindowTransparency(windowProps->getWindowTransparency());

		glfwMakeContextCurrent(glWindow);
		
		glfwShowWindow(glWindow);

		glfwSwapInterval(0); // No g-sync

		if (glewInit() != GLEW_OK) {
			dispose();
			throw std::exception(FAILED_GLEW_INIT);
		}

		print_status(glGetString(GL_VERSION));

		glViewport(0, 0, windowProps.dimension.width, windowProps.dimension.height);
	}

	void Window::dispose() {
		glfwDestroyWindow(glWindow);
	}

	void Window::setHint(const WindowHint& hint) {

	}

	void Window::restore() {
		windowMode.maximized = false;
		windowMode.minimized = false;
		if (glWindow) glfwRestoreWindow(glWindow);
	}

	void Window::maximize() {
		windowMode.maximized = true;
		windowMode.minimized = false;
		if (glWindow) glfwMaximizeWindow(glWindow);
	}

	void Window::minimize() {
		windowMode.maximized = false;
		windowMode.minimized = true;
		if (glWindow) glfwIconifyWindow(glWindow);
	}

	void Window::fullscreen() {
		// Set the window mode flag to fullscreen
		windowMode.fullscreen = true;
		
		if (not glWindow)
			return;

		int xpos;
		int ypos;
		glfwGetWindowPos(glWindow, &xpos, &ypos);

		windowProps.position.x = xpos;
		windowProps.position.y = ypos;

		if (windowMode.fullscreen && monitor != nullptr)
			// make window fullscreen with:
			glfwSetWindowMonitor(
				glWindow,
				monitor,                       // current active monitor
				0, 0,                          // position of the extended window
				windowProps.resolution.width,  // width of the window
				windowProps.resolution.height, // height of the window
				GLFW_DONT_CARE                 // refreshrate in Hz
			);
		else
			// return window to its default dimensions:
			glfwSetWindowMonitor(
				glWindow,
				nullptr,                       // current active monitor
				xpos, ypos,                    // position of the extended window
				windowProps.dimension.width,   // width of the window
				windowProps.dimension.height,  // height of the window
				GLFW_DONT_CARE                 // refreshrate in Hz
			);

		// Update resized flag
		resized = true;
	}

	bool Window::hasResized() {
		return resized;
	}

	void Window::close() {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
	}

	void Window::focus() {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		glfwFocusWindow(glWindow);
	}

	void Window::centerWindow() {

		if (not glWindow)
			debug_break(not glWindow, NO_CONTEXT_ERROR);

		// If no monitor is present, or is maximized or minimized
		// there is no need to update the window position since
		// there is not going to be visible if any of these conditions happen
		if (monitor == nullptr or windowMode.maximized or windowMode.minimized)
			return;

		const Utils::Dimension& windowDimensions = windowProps.dimension;
		const Utils::Dimension& monitorDimensions = monitor.getDimensions();

		// calculate relative position retlative to center
		int newPositionX = (monitorDimensions.width - windowDimensions.width) / 2;
		int newPositionY = (monitorDimensions.height - windowDimensions.height) / 2;

		// set new position to Props. and update GLFW window
		windowProps.position.x = newPositionX;
		windowProps.position.y = newPositionY;
		glfwSetWindowPos(glWindow, newPositionX, newPositionY);
	}

	void Window::requestAttention() {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		glfwRequestWindowAttention(glWindow);
	}
}