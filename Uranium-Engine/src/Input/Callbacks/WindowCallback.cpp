#include <GL/glfw3.h>

#include <memory>
#include "WindowCallback.h"
#include "Platform/Display/Window.h"

#include "Input/Events/WindowEvents.h"

namespace Uranium::Input::Callbacks {

	using namespace Platform::Display;

	WindowCallback::WindowCallback(Window* window) noexcept {	
		// On position and size callbacks
		glfwSetWindowPosCallback(*window,       WindowCallback::movedEvent);
		glfwSetWindowSizeCallback(*window,      WindowCallback::resizedEvent);
		
		// On window mode callbacks
		glfwSetWindowFocusCallback(*window,     WindowCallback::focusEvent);
		glfwSetWindowIconifyCallback(*window,   WindowCallback::minimizeEvent);
		glfwSetWindowMaximizeCallback(*window,  WindowCallback::maximizeEvent);
		
		// On refresh buffer callbacks
		glfwSetWindowRefreshCallback(*window,   WindowCallback::refreshEvent);
		glfwSetFramebufferSizeCallback(*window, WindowCallback::frameBufferSizeEvent);
		
		// On window closing event
		glfwSetWindowCloseCallback(*window,     WindowCallback::closeEvent);
	}

	void WindowCallback::closeEvent(GLFWwindow* glWindow) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		// Create a new event with the new updated size
		WindowCloseEvent event = WindowCloseEvent();

		// Set the new event
		window.getEventFunction() (event);
	}

	void WindowCallback::resizedEvent(GLFWwindow* glWindow, int width, int height) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		// Create a new event with the new updated size
		WindowResizeEvent event(width, height);

		// Set the new event
		window.getEventFunction() (event);
	}

	void WindowCallback::movedEvent(GLFWwindow* glWindow, int xpos, int ypos) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		
		// Create a new event with the new updated position
		WindowPositionEvent event(xpos, ypos);

		// Set the new event
		window.getEventFunction() (event);
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