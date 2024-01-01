#include <GL/glfw3.h>

#include <memory>

#include "WindowCallback.h"
#include "Platform/Display/Window.h"
#include "Input/Events/WindowEvents.h"

namespace Uranium::Input::Callbacks {

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

		WindowCloseEvent event = WindowCloseEvent();
		window.callbackFunction(event);
	}

	void WindowCallback::resizedEvent(GLFWwindow* glWindow, int width, int height) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		window.props.dimension.x = width;
		window.props.dimension.y = height;

		WindowResizeEvent event(width, height);
		window.callbackFunction(event);
	}

	void WindowCallback::movedEvent(GLFWwindow* glWindow, int xpos, int ypos) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		window.props.position.x = xpos;
		window.props.position.y = ypos;

		WindowPositionEvent event(xpos, ypos);
		window.callbackFunction(event);
	}

	void WindowCallback::focusEvent(GLFWwindow* glWindow, int isFocused) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowFocusEvent event(isFocused == GLFW_TRUE);
		window.callbackFunction(event);
	}

	void WindowCallback::minimizeEvent(GLFWwindow* glWindow, int isMinimized) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowMinimizedEvent event(isMinimized == GLFW_TRUE);
		window.callbackFunction(event);
	}

	void WindowCallback::maximizeEvent(GLFWwindow* glWindow, int isMaximized) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowMaximizedEvent event(isMaximized == GLFW_TRUE);
		window.callbackFunction(event);
	}

	void WindowCallback::refreshEvent(GLFWwindow* glWindow) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowRefreshEvent event = WindowRefreshEvent();
		window.callbackFunction(event);
	}

	void WindowCallback::frameBufferSizeEvent(GLFWwindow* glWindow, int width, int height) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		window.props.resolution.x = width;
		window.props.resolution.y = height;

		WindowBufferResizeEvent event(width, height);
		window.callbackFunction(event);
	}
}