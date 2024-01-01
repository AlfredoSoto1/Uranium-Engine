#include <GL/glew.h>
#include <GL/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

#include "Window.h"

#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Platform::Display {

	Window::Window() noexcept :
		glWindow(nullptr),
		vSyncEnabled(false)
	{
		modes.visible = true;
		modes.resizable = true;
		modes.decorated = true;
		modes.alwaysOnTop = true;

		operation.restored = false;
		operation.maximized = false;
		operation.minimized = false;
		operation.fullscreen = false;

		props.title = "Uranium Engine";
		props.position = glm::ivec2(0, 0);
		props.dimension = glm::ivec2(MIN_WIDTH, MIN_HEIGHT);
		props.resolution = glm::ivec2(MIN_WIDTH, MIN_HEIGHT);
		props.opacity = 100;

		// Prepare default window hints before creation
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

		// Create a GLFWwindow
		glWindow = glfwCreateWindow(props.dimension.x, props.dimension.y, props.title.c_str(), nullptr, nullptr);

		// Make the window be the main context and set *this* as reference to window
		glfwMakeContextCurrent(glWindow);
		glfwSetWindowUserPointer(glWindow, this);

		glfwSetWindowSizeLimits(glWindow, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwShowWindow(glWindow);

		if (glewInit() != GLEW_OK)
			throw std::exception("GLEW could not initiate correctly!");
		
#ifdef UR_DEBUG
		std::cout << glGetString(GL_VERSION) << std::endl;
#endif // UR_DEBUG
	}

	Window::~Window() {
		glfwHideWindow(glWindow);
		glfwDestroyWindow(glWindow);
	}

	Window::operator GLFWwindow* () const {
		return glWindow;
	}

	void Window::onUpdate() const {
		glfwSwapBuffers(glWindow);
		glfwPollEvents();
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(glWindow);
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
		vSyncEnabled = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void Window::createCallbacks() {
		windowCallback = std::make_unique<WindowCallback>(this);
		mouseCallback = std::make_unique<MouseCallback>(this);
		cursorCallback = std::make_unique<CursorCallback>(this);
		keyboardCallback = std::make_unique<KeyboardCallback>(this);
	}

	void Window::disposeCallbacks() {
		delete windowCallback.release();
		delete mouseCallback.release();
		delete cursorCallback.release();
		delete keyboardCallback.release();
	}

	void Window::setEventCallback(const Event::EventCallbackFn& callbackEvent) {
		this->callbackFunction = callbackEvent;
	}

}