
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <functional>

#include "EngineTools.h"

#include "WorkingUnit.h"
#include "Application.h"

#include "Uranium/Graphics/Display/Window.h"
#include "Uranium/Graphics/Display/Monitor.h"

namespace Uranium::Core {

	Application* Application::instanceReference = nullptr;
	
	Application* Application::instance() {
		return instanceReference;
	}

	Application::Application() :
		exitRequested(false),
		glfwInitiated(false),
		applicationRunning(false),

		activeContexts(0),

		contextMutex(),
		activeThreads()
	{
		if (instanceReference != nullptr)
			throw std::runtime_error("Application has already started.");

		if (glfwInit() == GLFW_FALSE)
			throw std::exception("GLFW could not initialize correctly.");

		glfwInitiated = true;
		instanceReference = this;

		glfwSetErrorCallback(&Application::errorCallbackReceive);
	}

	Application::~Application() {
		if (not glfwInitiated)
			return;

		// delete callbacks here

		activeThreads.clear();

		// Terminate the GLFW just before
		// the application ends.
		glfwTerminate();
	}
	
	void Application::errorCallbackReceive(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		fprintf(stderr, "Error: %s\n", description);
	}

	volatile bool Application::isGLFWActive() {
		return glfwInitiated;
	}

	volatile bool Application::hasAppStarted() {
		return applicationRunning;
	}

	void Application::exit() {
		// Initiate a forced-exit method for this application instance
		exitRequested = true;
	}

	void Application::run() {
		
		// Set the application running flag
		// to true for this unique application instance
		applicationRunning = true;
		
		while (activeContexts != 0 && not exitRequested) {
			// Update the callback events
			// every time the user interacts with
			// either the window or any other io
			glfwPollEvents();
		}

		// Join all threads after use
		for (const auto& thread : activeThreads)
			thread->join();

		// update application running 
		// status flag to false
		applicationRunning = false;
	}

	void Application::registerWindow(std::shared_ptr<Window> window) {
		
		// Build the window with all
		// modes and properties
		window->build();

		// Create a new heap-allocated thread
		std::shared_ptr<Thread> newThread = std::make_shared<Thread>(
			// Call the update() method from 'this' application.
			// Provide the reference of where the update() is located at
			&Application::update, this,

			// Pass the window as parameter, since its a parameter for the update()
			window
		);

		// Save a copy of the thread created.
		// This copy inside this list will be later
		// used when the application ends, waiting
		// for each thread to join and then free the memory.
		activeThreads.push_back(newThread);
		
		activeContexts++;
	}

	float colorChange = 0.0;

	void Application::update(std::shared_ptr<Window> window) {

		// Set the default context for 'this' thread.
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

		float another = colorChange += 0.5;

		while (not window->shouldClose() && not exitRequested) {
			
			// check if window has resized
			int width, height;
			glfwGetFramebufferSize(*window, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, another, 0.0, 1.0);

			// TODO - Make swap buffers only
			// if its focused.. also make it so
			// that a thread finishes, it joins it automatically
			contextMutex.lock();

			// Swap front and back buffers
			glfwSwapBuffers(*window);

			contextMutex.unlock();
		}

		std::cout << "one out" << std::endl;

		// Clean up all memory allocated at the beginning
		window->dispose();

		activeContexts--;
	}
}