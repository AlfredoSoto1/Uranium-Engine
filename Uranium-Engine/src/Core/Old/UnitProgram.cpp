#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EngineTools.h"
#include "UnitProgram.h"

#include "Graphics/Display/Window.h"

#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/MonitorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Core {

	UnitProgram::UnitProgram() :
		// Initiate thread; reserve a new unit
		workingUnit(&UnitProgram::reserve, this),

		cursorCallback(nullptr),  // 
		windowCallback(nullptr),  // 
		mouseCallback(nullptr),   // Unit program Callbacks
		monitorCallback(nullptr), // 
		keyboardCallback(nullptr) // 
	{

	}

	UnitProgram::~UnitProgram() {

	}

	auto UnitProgram::getCursorCallback()   -> CursorCallback& {
		return *cursorCallback;
	}

	auto UnitProgram::getWindowCallback()   -> WindowCallback& {
		return *windowCallback;
	}

	auto UnitProgram::getMouseCallback()    -> MouseCallback& {
		return *mouseCallback;
	}

	auto UnitProgram::getMonitorCallback()  -> MonitorCallback& {
		return *monitorCallback;
	}

	auto UnitProgram::getKeyboardCallback() -> KeyboardCallback& {
		return *keyboardCallback;
	}

	void UnitProgram::initCallbacks() {
		// UI callback initialization
		cursorCallback = new CursorCallback(window.get());
		windowCallback = new WindowCallback(window.get());

		// Peripheral callback initialization
		mouseCallback = new MouseCallback(window.get());
		monitorCallback = new MonitorCallback(window.get());
		keyboardCallback = new KeyboardCallback(window.get());
	}

	void UnitProgram::freeCallbacks() {
		delete cursorCallback;
		delete windowCallback;
		delete mouseCallback;
		delete monitorCallback;
		delete keyboardCallback;
	}

	void UnitProgram::initGlew() {

		glfwMakeContextCurrent(*window);

		glfwSwapInterval(0); // No g-sync

		if (glewInit() != GLEW_OK) {
			window->dispose(); // free window memory
			exit();            // force-exit the application
			return;
		}
		print_status(glGetString(GL_VERSION));
		// Prepare view port before rendering
		//glViewport(0, 0, windowProps.dimension.width, windowProps.dimension.height);
	}

	void UnitProgram::update() {

		float another = colorChange += 0.5;

		while (not window->shouldClose() && not exitRequested) {

			//// check if window has resized
			//int width, height;
			//glfwGetFramebufferSize(*window, &width, &height);
			//glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, another, 0.0, 1.0);

			// TODO - Make swap buffers only
			// if its focused.. also make it so
			// that a thread finishes, it joins it automatically
			//if (window->getCallback().hasFocused()) {
			//	// Swap front and back buffers
			//	glfwSwapBuffers(*window);
			//}

			// TODO: fix when multi-threaded
			glfwSwapBuffers(*window);
		}

		// Clean up all memory allocated at the beginning
		window->dispose();
	}

	void UnitProgram::join() {
		// Join the current working unit
		// to the main thread.
		workingUnit.join();
	}

	void UnitProgram::reserve() {
		// Initiate the context
		// Here will be loading and creating
		// all context dependent features.


		// --Do something interesting here--
	}

	void UnitProgram::pollEvents() {

	}
}