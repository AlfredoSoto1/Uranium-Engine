#include <GL/glfw3.h>

#include <memory>

#include "WindowCallback.h"
#include "Platform/Display/Window.h"

#include "Input/Events/WindowResizeEvent.h"
#include "Input/Events/WindowCloseEvent.h"
#include "Input/Events/WindowFocusEvent.h"
#include "Input/Events/WindowRefreshEvent.h"
#include "Input/Events/WindowPositionEvent.h"
#include "Input/Events/WindowMinimizeEvent.h"
#include "Input/Events/WindowMaximizeEvent.h"
#include "Input/Events/WindowBufferResizeEvent.h"

namespace Uranium::Input::Callbacks {

	WindowCallback::WindowCallback(Window* window) noexcept {	
		// On position and size callbacks
		glfwSetWindowPosCallback(*window,       WindowCallback::position_callback);
		glfwSetWindowSizeCallback(*window,      WindowCallback::resized_callback);
		
		// On window mode callbacks
		glfwSetWindowFocusCallback(*window,     WindowCallback::focus_callback);
		glfwSetWindowIconifyCallback(*window,   WindowCallback::minimize_callback);
		glfwSetWindowMaximizeCallback(*window,  WindowCallback::maximize_callback);
		
		// On refresh buffer callbacks
		glfwSetWindowRefreshCallback(*window,   WindowCallback::refresh_callback);
		glfwSetFramebufferSizeCallback(*window, WindowCallback::framebuffer_resize_callback);
		
		// On window closing event
		glfwSetWindowCloseCallback(*window,     WindowCallback::close_callback);
	}

	void WindowCallback::close_callback(GLFWwindow* glWindow) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowCloseEvent event = WindowCloseEvent();
		window.callbackFunction(event);
	}

	void WindowCallback::resized_callback(GLFWwindow* glWindow, int width, int height) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		window.props.dimension.x = width;
		window.props.dimension.y = height;

		WindowResizeEvent event(width, height);
		window.callbackFunction(event);
	}

	void WindowCallback::position_callback(GLFWwindow* glWindow, int xpos, int ypos) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		window.props.position.x = xpos;
		window.props.position.y = ypos;

		WindowPositionEvent event(xpos, ypos);
		window.callbackFunction(event);
	}

	void WindowCallback::focus_callback(GLFWwindow* glWindow, int isFocused) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowFocusEvent event(isFocused == GLFW_TRUE);
		window.callbackFunction(event);
	}

	void WindowCallback::minimize_callback(GLFWwindow* glWindow, int isMinimized) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowMinimizedEvent event(isMinimized == GLFW_TRUE);
		window.callbackFunction(event);
	}

	void WindowCallback::maximize_callback(GLFWwindow* glWindow, int isMaximized) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowMaximizedEvent event(isMaximized == GLFW_TRUE);
		window.callbackFunction(event);
	}

	void WindowCallback::refresh_callback(GLFWwindow* glWindow) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		WindowRefreshEvent event = WindowRefreshEvent();
		window.callbackFunction(event);
	}

	void WindowCallback::framebuffer_resize_callback(GLFWwindow* glWindow, int width, int height) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		window.props.resolution.x = width;
		window.props.resolution.y = height;

		WindowBufferResizeEvent event(width, height);
		window.callbackFunction(event);
	}
}