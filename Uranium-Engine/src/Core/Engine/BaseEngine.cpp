#include <GL/glfw3.h>

#include "BaseEngine.h"

#include "Platform/Display/Window.h"

#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MonitorCallback.h"
#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Core::Engine {

	using namespace Platform::Display;
	using namespace Uranium::Input::Callbacks;

	BaseEngine::BaseEngine() noexcept :
		mouseCallback(nullptr),
		cursorCallback(nullptr),
		windowCallback(nullptr),
		monitorCallback(nullptr),
		keyboardCallback(nullptr)
	{
	}

	BaseEngine::~BaseEngine() {

	}

	void BaseEngine::run() {
		auto display1 = std::make_shared<Window>();
		auto display2 = std::make_shared<Window>();

		
		while (!display1->getEvents().shouldClose() && !display2->getEvents().shouldClose()) {

			glfwMakeContextCurrent(*display1);

			// check if window has resized
			int width, height;
			glfwGetFramebufferSize(*display1, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, 0.0, 0.0, 1.0);

			// TODO: fix when multi-threaded
			glfwSwapBuffers(*display1);


			glfwMakeContextCurrent(*display2);

			glfwGetFramebufferSize(*display2, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0, 1.0, 0.0, 1.0);

			// TODO: fix when multi-threaded
			glfwSwapBuffers(*display2);

			glfwPollEvents();
		}
		
		// release the window reference
		display1.reset();
		display2.reset();
	}

	void BaseEngine::initManagers() {
		// Create and initiate all the callbacks
		mouseCallback    = new MouseCallback();
		cursorCallback   = new CursorCallback();
		windowCallback   = new WindowCallback();
		monitorCallback  = new MonitorCallback();
		keyboardCallback = new KeyboardCallback();
	}

	void BaseEngine::disposeManagers() {
		// free all the created callbacks
		delete mouseCallback;
		delete cursorCallback;
		delete windowCallback;
		delete monitorCallback;
		delete keyboardCallback;
	}
}