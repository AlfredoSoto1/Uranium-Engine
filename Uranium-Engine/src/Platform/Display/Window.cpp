#include <GL/glew.h>
#include <GL/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

#include "Window.h"
#include "Platform/Monitor/Monitor.h"

namespace Uranium::Platform::Display {

	Window::Window() noexcept :
		glWindow(nullptr),

		modes(),
		props(),
		states()
	{
		modes.visible = true;
		modes.resizable = true;
		modes.decorated = true;
		modes.alwaysOnTop = false;
		modes.vSyncEnabled = false;

		states.restored = false;
		states.maximized = false;
		states.minimized = false;
		states.fullscreen = false;

		props.title = "Uranium Engine";
		props.position = glm::ivec2(0, 0);
		props.dimension = glm::ivec2(MIN_WIDTH, MIN_HEIGHT);
		props.resolution = glm::ivec2(MIN_WIDTH, MIN_HEIGHT);
		props.opacity = 100; // MAX

		// Prepare default window hints before creation
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

		// Create a GLFWwindow
		glWindow = glfwCreateWindow(props.dimension.x, props.dimension.y, props.title.c_str(), nullptr, nullptr);

		// Make the window be the main context and set *this* as reference to window
		glfwMakeContextCurrent(glWindow);
		glfwSetWindowUserPointer(glWindow, this);

		// Initiate Glew
		if (glewInit() != GLEW_OK)
			throw std::exception("GLEW could not initiate correctly!");
		std::cout << glGetString(GL_VERSION) << std::endl;

		setVSync(false);

		glfwSetWindowSizeLimits(glWindow, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwShowWindow(glWindow);
	}

	Window::~Window() {
		glfwDestroyWindow(glWindow);
	}

	Window::operator GLFWwindow* () const {
		return glWindow;
	}

	void Window::onUpdate() const {
		glfwSwapBuffers(glWindow);
		glfwPollEvents();
	}

	void Window::restore() {
		states.restored = true;
		states.maximized = false;
		states.minimized = false;

		// if the window is not in fullscreen mode, we
		// can restore the window manually
		if (!states.fullscreen) {
			glfwRestoreWindow(glWindow);
			return;
		}

		// if the window is on fullscreen mode, we need to
		// handle it in a different way...
		states.fullscreen = false;

		// Get the current position of the window
		// and keep track of the corresponding values
		int xpos;
		int ypos;
		glfwGetWindowPos(glWindow, &xpos, &ypos);

		// Update position without setting a new
		// position with glfw internally
		props.position.x = xpos;
		props.position.y = ypos;

		// return window to its default dimensions:
		glfwSetWindowMonitor(
			glWindow,
			nullptr,                // current active monitor
			xpos, ypos,             // position of the extended window
			props.dimension.x,      // width of the window
			props.dimension.y,      // height of the window
			GLFW_DONT_CARE          // refreshrate in Hz
		);
	}

	void Window::maximize() {
		// if the window is already in fullscreen
		// we don't need to maximize it
		if (states.fullscreen)
			return;

		states.restored = false;
		states.maximized = true;
		states.minimized = false;

		glfwMaximizeWindow(glWindow);
	}

	void Window::minimize() {
		// if the window is on fullscreen we don't need
		// to minimize it because the fullscreen mode takes
		// posession of the entire display.
		if (states.fullscreen)
			return;

		states.maximized = false;
		states.minimized = true;

		glfwIconifyWindow(glWindow);
	}

	void Window::close() {
		glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
	}

	void Window::focus() {
		glfwFocusWindow(glWindow);
	}

	void Window::requestAttention() {
		glfwRequestWindowAttention(glWindow);
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(glWindow);
	}

	auto Window::getModes() const -> const WindowModes& {
		return modes;
	}

	auto Window::getStates() const-> const WindowStates& {
		return states;
	}

	auto Window::getProperties() const-> const WindowProps& {
		return props;
	}

	void Window::center(MonitorRef monitor) {
		// if no monitor connected, throw exception
		if (!monitor->isConnected())
			throw std::invalid_argument("Provided monitor is not connected!");

		// If monitor is present but is maximized, minimized or fullscreen
		// there is no need to update the window position since
		// there is not going to be visible if any of these conditions happen
		if (states.maximized || states.minimized || states.fullscreen)
			return;

		// calculate relative position retlative to center
		int newPositionX = (monitor->getResolution().x - props.dimension.x) / 2;
		int newPositionY = (monitor->getResolution().y - props.dimension.y) / 2;

		// set new position to Props. and update GLFW window
		props.position.x = newPositionX;
		props.position.y = newPositionY;
		glfwSetWindowPos(glWindow, newPositionX, newPositionY);
	}

	void Window::setFullscreen(MonitorRef monitor) {
		if (!monitor->isConnected())
			throw std::invalid_argument("Provided monitor is not connected!");

		states.fullscreen = true;

		// Make the window fullscreen with:
		glfwSetWindowMonitor(
			glWindow,
			*monitor,           // current active monitor
			0, 0,               // position of the extended window
			props.resolution.x, // width of the window
			props.resolution.y, // height of the window
			GLFW_DONT_CARE      // refreshrate in Hz
		);
	}

	void Window::setTitle(const std::string& title) {
		props.title = title;
		glfwSetWindowTitle(glWindow, title.c_str());
	}

	void Window::setPosition(const glm::ivec2& position) {
		props.position = position;
		glfwSetWindowPos(glWindow, position.x, position.y);
	}

	void Window::setDimension(const glm::ivec2& dimension) {
		props.dimension = dimension;
		glfwSetWindowSize(glWindow, dimension.x, dimension.y);
	}

	void Window::setResolution(const glm::ivec2& resolution) {
		props.resolution = resolution;
	}

	void Window::setOpacity(unsigned int opacity) {
		props.opacity = opacity >= 100 ? 100 : opacity <= 0 ? 0 : opacity;

		// if max opacity is achieved, dont make
		// the window transparent
		if (opacity == 100) return;

		glfwSetWindowAttrib(
			// Establish window attribute to be -> frame buffer
			glWindow, GLFW_TRANSPARENT_FRAMEBUFFER,
			// Tell the frame buffer to become transparent
			// if and only if the opacity is lower than 100%
			opacity != 100 ? GLFW_TRUE : GLFW_FALSE
		);

		// Set the opacity of the window to be in a scale of [0, 100]
		glfwSetWindowOpacity(glWindow, opacity / 100.0f);
	}

	void Window::setVSync(bool enabled) {
		modes.vSyncEnabled = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void Window::setVisible(bool visible) {
		modes.visible = visible;
		if (visible)
			glfwShowWindow(glWindow);
		else
			glfwHideWindow(glWindow);
	}

	void Window::setResizable(bool resizable) {
		modes.resizable = resizable;
		glfwSetWindowAttrib(glWindow, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
	}

	void Window::setDecorated(bool decorated) {
		modes.decorated = decorated;
		glfwSetWindowAttrib(glWindow, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
	}

	void Window::setAlwaysOnTop(bool alwaysOnTop) {
		modes.alwaysOnTop = alwaysOnTop;
		glfwSetWindowAttrib(glWindow, GLFW_FLOATING, alwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
	}
}