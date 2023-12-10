#include <GL/glfw3.h>

#include "BaseEngine.h"
#include "Display/Window.h"

namespace Uranium::Services {

	BaseEngine::BaseEngine() noexcept :
		thread(),
		display(nullptr)
	{
	}

	BaseEngine::~BaseEngine() {

	}

	void BaseEngine::start() {

		display = createWindow();

		if (display == nullptr) {
			// do something else
		}

		// Set the default context for 'this' thread.
		glfwMakeContextCurrent(*display);

		// Run context here
		while (!display->getEvents().shouldClose()) {
			// check if window has resized
			int width, height;
			glfwGetFramebufferSize(*display, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, 0.0, 0.0, 1.0);

			// TODO - Make swap buffers only
			// if its focused.. also make it so
			// that a thread finishes, it joins it automatically
			//if (window->getCallback().hasFocused()) {
				 //Swap front and back buffers
				//glfwSwapBuffers(*display);
			//}

			// TODO: fix when multi-threaded
			glfwSwapBuffers(*display);
			glfwPollEvents();
		}
	}
}