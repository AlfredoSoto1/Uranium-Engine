#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Window.h"
#include "WindowMode.h"
#include "WindowProps.h"

#include "Monitor.h"

#include "Utils/Dimension.h"
#include "Input/Callbacks/WindowCallback.h"

#include "Core/EngineTools.h"
#include "Core/Application.h"

namespace Uranium::Graphics::Display {

	// 
	// Window - private defined error messages
	// 
	constexpr const char* DISPOSED_ALREADY = "'this' window has been disposed already.";
	constexpr const char* NO_CONTEXT_ERROR = "'this' window has no GLFW context.";
	constexpr const char* NO_MONITOR_CONNECTED = "There should be atleast one monitor connected";
	constexpr const char* FAILED_WINDOW_CREATION = "Window could not be created.";
	constexpr const char* OUT_OF_APPLICATION_SCOPE = "Window must be created inside the application.";

	// 
	// Window class implementation
	// 

	Window::Window() :
		glWindow(nullptr),
		callback(nullptr),
		windowListener(nullptr),

		windowMode(new WindowMode()),
		windowProps(new WindowProps()),

		hasCreated(false),
		hasDisposed(false)
	{
		debug_break(not Core::Application::instance()->isGLFWActive(), OUT_OF_APPLICATION_SCOPE);
		
		// Prepare the default GLFW hints, just in case
		glfwDefaultWindowHints();
	}

	Window::~Window() {
		if (hasDisposed)
			return;
		dispose();
	}

	bool Window::isCurrent() const {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		// Returns true if the current context
		// is the same as 'this' glWindow
		return glfwGetCurrentContext() == glWindow;
	}

	bool Window::shouldClose() const {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		return glfwWindowShouldClose(glWindow);
	}

	Window::operator GLFWwindow* () const {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		return glWindow;
	}

	auto Window::getModes() -> WindowMode& {
		return *windowMode;
	}

	auto Window::getProps() -> WindowProps& {
		return *windowProps;
	}

	auto Window::getCallback() -> WindowCallback& {
		return *callback;
	}

	auto Window::getWindowListener() const -> WindowListener* {
		return windowListener;
	}

	void Window::setWindowListener(WindowListener* windowListener) {
		this->windowListener = windowListener;
	}

	void Window::build() {

		// First prepare the GLFW hints before
		// creating a window context.
		// This is so the window to be created,
		// can adopt all hints given before its creation
		
		// Set OpenGL version (optional, but recommended)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowProps->mayorGLVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowProps->minorGLVersion);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		windowMode->initDefault();
		windowProps->initDefault();

		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		// Create a GLFW window with the given parameters
		glWindow = glfwCreateWindow(
			windowProps->dimension.width,
			windowProps->dimension.height,
			windowProps->title.c_str(), 
			nullptr, nullptr
		);

		if (not glWindow)
			throw std::exception(FAILED_WINDOW_CREATION);

		// Make sure the window props know the newly
		// created glWindow context
		windowMode->glWindow = this->glWindow;
		windowProps->glWindow = this->glWindow;

		hasCreated = true;

		glfwSetWindowUserPointer(glWindow, this);

		// Prepare and create the window callbacks
		callback = new WindowCallback(this);

		// Provide the corresponding values to the hints
		// declared before window creation after the window
		// has initialized correctly.

		// set resize window limits if and only if its resizable
		if (windowMode->resizable)
			glfwSetWindowSizeLimits(glWindow, WindowProps::MIN_WIDTH, WindowProps::MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

		// set window minimized / maximized if it was a Property setted before
		if (windowMode->minimized)
			windowMode->minimize();
		else if (windowMode->maximized)
			windowMode->maximize();

		// Update the window Opacity with the established
		// value before window context creation
		windowProps->setOpacity(windowProps->opacity);

		// Display the window
		glfwShowWindow(glWindow);
	}

	void Window::dispose() {
		if (hasDisposed)
			throw std::exception(DISPOSED_ALREADY);
		hasDisposed = true;
		
		if (not hasCreated)
			return;

		delete callback;    // Free all allocated memory
		delete windowMode;  // related to callbacks,
		delete windowProps; // Window modes and properties

		glfwHideWindow(glWindow);
		glfwDestroyWindow(glWindow);
	}

	void Window::close() {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
	}

	void Window::focus() {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		glfwFocusWindow(glWindow);
	}

	void Window::requestAttention() {
		debug_break(not glWindow, NO_CONTEXT_ERROR);
		glfwRequestWindowAttention(glWindow);
	}

	void Window::centerWindow(const Monitor& monitor) {

		debug_break(not glWindow, NO_CONTEXT_ERROR);

		if (not monitor.isConnected())
			throw std::invalid_argument(NO_MONITOR_CONNECTED);

		// If no monitor is present, or is maximized or minimized
		// there is no need to update the window position since
		// there is not going to be visible if any of these conditions happen
		if (windowMode->maximized or windowMode->minimized)
			return;

		const Utils::Dimension& windowDimensions = windowProps->dimension;
		const Utils::Dimension& monitorResolution = monitor.getResolution();

		// calculate relative position retlative to center
		int newPositionX = (monitorResolution.width - windowDimensions.width) / 2;
		int newPositionY = (monitorResolution.height - windowDimensions.height) / 2;

		// set new position to Props. and update GLFW window
		windowProps->position.x = newPositionX;
		windowProps->position.y = newPositionY;
		glfwSetWindowPos(glWindow, newPositionX, newPositionY);
	}
}