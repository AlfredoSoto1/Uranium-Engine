#include <GL/glfw3.h>

#include "BaseEngine.h"
#include "Display/Window.h"
#include "Events/Callbacks/WindowCallback.h"
#include "Events/Callbacks/MonitorCallback.h"
#include "Events/Callbacks/MouseCallback.h"
#include "Events/Callbacks/CursorCallback.h"
#include "Events/Callbacks/KeyboardCallback.h"

namespace Uranium::Core {

	BaseEngine::BaseEngine() noexcept :
		display(nullptr),
		mouseCallback(nullptr),
		cursorCallback(nullptr),
		windowCallback(nullptr),
		monitorCallback(nullptr),
		keyboardCallback(nullptr)
	{
	}

	BaseEngine::~BaseEngine() {

	}

	std::shared_ptr<Display::Window> BaseEngine::getWindow() const {
		return display;
	}

	void BaseEngine::run() {
		display = createWindow();

		if (display == nullptr)
			throw std::exception("Engine could not start due to an error generating the GLFW window.");

		// Set the default context for 'this' thread.
		glfwMakeContextCurrent(*display);
		
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
		
		// release the window reference
		display.reset();
	}

	void BaseEngine::createCallbacks() {
		using namespace Events::Callbacks;

		// Create and initiate all the callbacks
		mouseCallback    = new MouseCallback();
		cursorCallback   = new CursorCallback();
		windowCallback   = new WindowCallback();
		monitorCallback  = new MonitorCallback();
		keyboardCallback = new KeyboardCallback();
	}

	void BaseEngine::disposeCallbacks() {
		// free all the created callbacks
		delete mouseCallback;
		delete cursorCallback;
		delete windowCallback;
		delete monitorCallback;
		delete keyboardCallback;
	}
}