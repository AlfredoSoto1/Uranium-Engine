#include <GL/glfw3.h>

#include "Window.h"
#include "WindowManager.h"

namespace Uranium::Platform::Display {

	WindowManager::WindowManager() noexcept :
		windows()
	{

	}

	WindowManager::~WindowManager() {
		windows.clear();
	}

	bool WindowManager::allWindowsClosed() const {
		return false;
	}

	void WindowManager::update() {
		
		//glfwMakeContextCurrent(window);

		//// check if window has resized
		//int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);

		//// render scene here
		//glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(1.0, 0.0, 0.0, 1.0);

		//// TODO: fix when multi-threaded
		//glfwSwapBuffers(window);
	}
}