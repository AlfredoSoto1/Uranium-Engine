#include <GLFW/glfw3.h>
#include <stdexcept>

#include "UWindow.h"
#include "Core/Logger.h"

#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Platform::Interface {
	
	using namespace Core;

	void UWindow::initWindowAPI() {
		if (glfwInit() == GLFW_FALSE)
			throw std::runtime_error("Could not initiate. Application cannot start.");

		glfwSetErrorCallback(&UWindow::displayGLFWErrors);
	}

	void UWindow::shutdownWindowAPI() noexcept {
		glfwTerminate();
	}

	void UWindow::displayGLFWErrors(int error, const char* description) noexcept {
		char errorMessage[256];
		std::sprintf(errorMessage, "[GLFW : %d]", error);
		Core::UR_ERROR(errorMessage, description);
	}

	UWindow::UWindow(
		const std::string& title = "Uranium-Window", // 
		uint32_t width  = MIN_WIDTH,				 // default values are set if no arguments are provided
		uint32_t height = MIN_HEIGHT				 // 
	) noexcept :
		dimension(width, height)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, this);

		glfwSetWindowSizeLimits(glfwWindow, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwShowWindow(glfwWindow);
	}

	UWindow::~UWindow() noexcept {
		glfwHideWindow(glfwWindow);
		glfwDestroyWindow(glfwWindow);
	}

	UWindow::operator GLFWwindow* () const noexcept {
		return glfwWindow;
	}

	void UWindow::onUpdate() const {
		glfwPollEvents();
	}

	bool UWindow::shouldClose() const noexcept {
		return glfwWindowShouldClose(glfwWindow);
	}

	void UWindow::setTitle(const std::string& title) {
		this->title = title;
		glfwSetWindowTitle(glfwWindow, title.c_str());
	}

	void UWindow::setPosition(const glm::ivec2& position) {
		this->position = position;
		glfwSetWindowPos(glfwWindow, position.x, position.y);
	}

	void UWindow::setDimension(const glm::ivec2& dimension) {
		this->dimension = dimension;
		glfwSetWindowSize(glfwWindow, dimension.x, dimension.y);
	}

	void UWindow::setResolution(const glm::ivec2& resolution) {
		this->resolution = resolution;
	}

	void UWindow::setVSync(bool enabled) {
		vSyncEnabled = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void UWindow::createCallbacks() noexcept {
		windowCallback   = std::make_unique<WindowCallback>(this);
		mouseCallback    = std::make_unique<MouseCallback>(this);
		cursorCallback   = std::make_unique<CursorCallback>(this);
		keyboardCallback = std::make_unique<KeyboardCallback>(this);
	}

	void UWindow::disposeCallbacks() noexcept {
		delete windowCallback.release();
		delete mouseCallback.release();
		delete cursorCallback.release();
		delete keyboardCallback.release();
	}

	void UWindow::setEventCallback(const Event::EventCallbackFn& callbackEvent) {
		this->callbackFunction = callbackEvent;
	}
}