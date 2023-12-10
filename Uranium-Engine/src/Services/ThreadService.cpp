#include <GL/glfw3.h>

#include <algorithm>
#include "ThreadService.h"
#include "Display/Window.h"

namespace Uranium::Services {

	volatile int ThreadService::threadCount = 0;

	volatile int ThreadService::activeThreadCount() {
		return threadCount;
	}

	ThreadService::ThreadService() noexcept :
		thread(),
		active(false),
		display(nullptr)
	{
	}

	ThreadService::~ThreadService() {
		prune();
	}

	bool ThreadService::isActive() const {
		return thread.joinable() && active;
	}
	
	void ThreadService::init() {
		if (thread.joinable())
			return;
		// Create the window in default thread
		// this way you can tell OpenGL to poll
		// events from main thread always
		display = createWindow();

		// Increase thread active thread count
		ThreadService::threadCount++;

		// Create virtual thread
		thread = std::thread(&ThreadService::start, this);
	}

	void ThreadService::prune() {
		if (thread.joinable()) {
			thread.join();
			//delete display.release
		}
		if(active)
			ThreadService::threadCount--;
		active = false;
	}

	void ThreadService::start() {
		active = true;

		if (display == nullptr) {
			// do something else
		}

		// Set the default context for 'this' thread.
		glfwMakeContextCurrent(*display);

		// Run context here
		while (!display->getEvents().shouldClose() && active) {
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
		}

		// Deactivate the current thread
		active = false;
		ThreadService::threadCount--;
	}
}