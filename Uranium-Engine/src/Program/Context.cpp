
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>

#include "Context.h"
#include "Display/Window.h"

namespace Uranium::Program {

	Context::Context() noexcept :
		/*
		* Parameters
		*/
		display(nullptr),

		/*
		* Context-members
		*/
		contextActive(false),
		hasExitRequested(false),
		contextThread(&Context::start, this)
	{
		std::cout << "Context Created" << std::endl;
	}

	Context::~Context() {
		std::cout << "Context Destroyed" << std::endl;
	}

	bool Context::isActive() const {
		return contextActive;
	}

	bool Context::exitRequested() const {
		return hasExitRequested;
	}

	void Context::exit() const {
		hasExitRequested = true;
	}

	void Context::end() {
		// Join the thread and update
		// contextActive flag to false to tell
		// the client that the context has ended
		contextThread.join();
		contextActive = false;
	}

	void Context::start() {
		// Context thread starts to be active
		// when the thread starts running
		contextActive = true;

		// Run in context (thread)

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