#include <GL/glfw3.h>

#include "BaseEngine.h"
#include "Display/Window.h"
#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MonitorCallback.h"
#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Services {

	BaseEngine::BaseEngine() noexcept :
		display(nullptr)
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

		using namespace Input::Callbacks;

		mouseCallback    = new MouseCallback();
		cursorCallback   = new CursorCallback();
		windowCallback   = new WindowCallback();
		monitorCallback  = new MonitorCallback();
		keyboardCallback = new KeyboardCallback();
	}

	void BaseEngine::disposeCallbacks() {
		delete mouseCallback;
		delete cursorCallback;
		delete windowCallback;
		delete monitorCallback;
		delete keyboardCallback;
	}
}