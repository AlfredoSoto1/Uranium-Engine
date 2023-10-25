import Uranium.Core.Context;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Uranium::Core {

	Context::Context(ThreadType type) noexcept :
		type(type),
		exitRequested(false),
		contextActive(false),
		contextThread(&Context::startContext, this)
	{
		std::cout << "Context Created" << std::endl;
	}

	Context::~Context() {
		std::cout << "Context Destroyed" << std::endl;
	}

	bool Context::isActive() const {
		return contextActive;
	}

	bool Context::isExitRequested() const {
		return exitRequested;
	}

	void Context::exit() const {
		exitRequested = true;
	}

	void Context::endContext() const {
		// Join the thread and update
		// contextActive flag to false to tell
		// the client that the context has ended
		contextThread.join();
		contextActive = false;
	}

	void Context::startContext() {
		// Context thread starts to be active
		// when the thread starts running
		contextActive = true;

		// Set the default context for 'this' thread.
		//glfwMakeContextCurrent(*window);

		// Run context here
		//while (!window->shouldClose() && !exitRequested) {
		//	//// check if window has resized
		//	//int width, height;
		//	//glfwGetFramebufferSize(*window, &width, &height);
		//	//glViewport(0, 0, width, height);

		//	// render scene here
		//	glClear(GL_COLOR_BUFFER_BIT);
		//	glClearColor(1.0, 0.0, 0.0, 1.0);

		//	// TODO - Make swap buffers only
		//	// if its focused.. also make it so
		//	// that a thread finishes, it joins it automatically
		//	//if (window->getCallback().hasFocused()) {
		//	//	// Swap front and back buffers
		//	//	glfwSwapBuffers(*window);
		//	//}

		//	// TODO: fix when multi-threaded
		//	glfwSwapBuffers(*window);
		//}
	}
}