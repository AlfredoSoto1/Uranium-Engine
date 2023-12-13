#include <GL/glfw3.h>

#include <memory>
#include "WindowCallback.h"

#include "Display/Window.h"
#include "Core/BaseEngine.h"
#include "Services/Application.h"

using namespace Uranium::Core;
using namespace Uranium::Display;
using namespace Uranium::Services;

namespace Uranium::Events::Callbacks {
	
	WindowCallback::WindowCallback() noexcept {	
		// Obtain the window reference from the application's engine
		std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

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

	WindowCallback::~WindowCallback() {
		// Obtain the window reference from the application's engine
		std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		glfwSetWindowPosCallback(*window,       nullptr);
		glfwSetWindowSizeCallback(*window,      nullptr);
		glfwSetWindowCloseCallback(*window,     nullptr);
		glfwSetWindowFocusCallback(*window,     nullptr);
		glfwSetWindowIconifyCallback(*window,   nullptr);
		glfwSetWindowRefreshCallback(*window,   nullptr);
		glfwSetWindowMaximizeCallback(*window,  nullptr);
		glfwSetFramebufferSizeCallback(*window, nullptr);
	}

	void WindowCallback::closeEvent(GLFWwindow* glWindow) {
		BaseEngine& engine = Application::instance().getBaseEngine();
	}

	void WindowCallback::resizedEvent(GLFWwindow* glWindow, int width, int height) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		// set resize flag to true and update the window size
	}

	void WindowCallback::movedEvent(GLFWwindow* glWindow, int xpos, int ypos) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		// update the window position
	}

	void WindowCallback::focusEvent(GLFWwindow* glWindow, int isFocused) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		// update the window focused flag
	}

	void WindowCallback::minimizeEvent(GLFWwindow* glWindow, int isMinimized) {
		BaseEngine& engine = Application::instance().getBaseEngine();
	}

	void WindowCallback::maximizeEvent(GLFWwindow* glWindow, int isMaximized) {
		BaseEngine& engine = Application::instance().getBaseEngine();
	}

	void WindowCallback::refreshEvent(GLFWwindow* glWindow) {
		BaseEngine& engine = Application::instance().getBaseEngine();
	}

	void WindowCallback::frameBufferSizeEvent(GLFWwindow* glWindow, int width, int height) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		// update the buffer size
	}
}