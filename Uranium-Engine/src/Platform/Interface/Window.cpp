#include <GLFW/glfw3.h>

#include <stdexcept>
#include "Core/Logger.h"

#include "Window.h"

#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Platform::Interface {
	
	void Window::init() {
		if (glfwInit() == GLFW_FALSE)
			throw std::runtime_error("Could not initiate. Application cannot start.");

		glfwSetErrorCallback(&Window::displayGLFWErrors);
	}

	void Window::dispose() noexcept {
		glfwTerminate();
		Core::UR_INFO("[GLFW]", "Terminated successfully.");
	}

	void Window::displayGLFWErrors(int error, const char* description) noexcept {
		Core::UR_ERROR("[GLFW]", "ERROR %d: %s", error, description);
	}

	Window::Window(const std::string& title, uint32_t width, uint32_t height) :
		glfwWindow(nullptr),

		title(title),

		position(0, 0),
		dimension(width, height),
		resolution(width, height),

		visible(true),
		resizable(true),
		decorated(true),
		alwaysOnTop(false),

		restored(false),
		maximized(false),
		minimized(false),
		fullscreen(false),

		vSyncEnabled(false)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, this);

		glfwSetWindowSizeLimits(glfwWindow, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwShowWindow(glfwWindow);
	}

	Window::~Window() noexcept {
		if (glfwWindow == nullptr)
			return;
		glfwHideWindow(glfwWindow);
		glfwDestroyWindow(glfwWindow);
	}

	Window::operator GLFWwindow* () const noexcept {
		return glfwWindow;
	}

	void Window::onUpdate() const {
		glfwPollEvents();
	}

	bool Window::shouldClose() const noexcept {
		return glfwWindowShouldClose(glfwWindow);
	}

	void Window::setTitle(const std::string& title) {
		this->title = title;
		glfwSetWindowTitle(glfwWindow, title.c_str());
	}

	void Window::setPosition(const glm::ivec2& position) {
		this->position = position;
		glfwSetWindowPos(glfwWindow, position.x, position.y);
	}

	void Window::setDimension(const glm::ivec2& dimension) {
		this->dimension = dimension;
		glfwSetWindowSize(glfwWindow, dimension.x, dimension.y);
	}

	void Window::setResolution(const glm::ivec2& resolution) {
		this->resolution = resolution;
	}

	void Window::setVSync(bool enabled) {
		vSyncEnabled = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void Window::createCallbacks() {
		//windowCallback = std::make_unique<WindowCallback>(this);
		//mouseCallback = std::make_unique<MouseCallback>(this);
		//cursorCallback = std::make_unique<CursorCallback>(this);
		//keyboardCallback = std::make_unique<KeyboardCallback>(this);
	}

	void Window::disposeCallbacks() noexcept {
		delete windowCallback.release();
		delete mouseCallback.release();
		delete cursorCallback.release();
		delete keyboardCallback.release();
	}

	void Window::setEventCallback(const Event::EventCallbackFn& callbackEvent) noexcept {
		this->callbackFunction = callbackEvent;
	}
}