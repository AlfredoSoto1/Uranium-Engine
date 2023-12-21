#include <GL/glfw3.h>

#include <memory>
#include "WindowCallback.h"

#include "Core/Application.h"
#include "Engine/BaseEngine.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	WindowCallback::WindowCallback() noexcept {	
		// Obtain the window reference from the application's engine
		//std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		//// On position and size callbacks
		//glfwSetWindowPosCallback(*window,       WindowCallback::movedEvent);
		//glfwSetWindowSizeCallback(*window,      WindowCallback::resizedEvent);
		//
		//// On window mode callbacks
		//glfwSetWindowFocusCallback(*window,     WindowCallback::focusEvent);
		//glfwSetWindowIconifyCallback(*window,   WindowCallback::minimizeEvent);
		//glfwSetWindowMaximizeCallback(*window,  WindowCallback::maximizeEvent);
		//
		//// On refresh buffer callbacks
		//glfwSetWindowRefreshCallback(*window,   WindowCallback::refreshEvent);
		//glfwSetFramebufferSizeCallback(*window, WindowCallback::frameBufferSizeEvent);
		//
		//// On window closing event
		//glfwSetWindowCloseCallback(*window,     WindowCallback::closeEvent);
	}

	WindowCallback::~WindowCallback() {
		// Obtain the window reference from the application's engine
		//std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		//glfwSetWindowPosCallback(*window,       nullptr);
		//glfwSetWindowSizeCallback(*window,      nullptr);
		//glfwSetWindowCloseCallback(*window,     nullptr);
		//glfwSetWindowFocusCallback(*window,     nullptr);
		//glfwSetWindowIconifyCallback(*window,   nullptr);
		//glfwSetWindowRefreshCallback(*window,   nullptr);
		//glfwSetWindowMaximizeCallback(*window,  nullptr);
		//glfwSetFramebufferSizeCallback(*window, nullptr);
	}

	void WindowCallback::closeEvent(GLFWwindow* glWindow) {
	}

	void WindowCallback::resizedEvent(GLFWwindow* glWindow, int width, int height) {
		// set resize flag to true and update the window size
	}

	void WindowCallback::movedEvent(GLFWwindow* glWindow, int xpos, int ypos) {
		// update the window position
	}

	void WindowCallback::focusEvent(GLFWwindow* glWindow, int isFocused) {
		// update the window focused flag
	}

	void WindowCallback::minimizeEvent(GLFWwindow* glWindow, int isMinimized) {
	}

	void WindowCallback::maximizeEvent(GLFWwindow* glWindow, int isMaximized) {
	}

	void WindowCallback::refreshEvent(GLFWwindow* glWindow) {
	}

	void WindowCallback::frameBufferSizeEvent(GLFWwindow* glWindow, int width, int height) {
		// update the buffer size
	}
}