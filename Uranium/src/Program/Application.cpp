#define GLEW_STATIC
#include <iostream>
#include <GLFW/glfw3.h>

import Uranium.Program.Context;
import Uranium.Program.Application;

namespace Uranium::Program {

	Application* Application::instanceReference = nullptr;

	Application& Application::instance() {
		return *instanceReference;
	}

	void Application::build(int argc, char* argv[], std::unique_ptr<Application> application) {

		// Pass all the arguments from the terminal
		// to the application
		for (int i = 0; i < argc; i++)
			application->addArgument(argv[i]);

		try {
			// Run the application
			application->run();
		}
		catch (const std::exception& e) {
			e.what();
		}

		// Free application after it goes out of scope
	}

	void Application::diagnosticErrors(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		std::printf("Error [%i]: %s\n", error, description);
	}

	Application::~Application() {
		contexts.clear();
		arguments.clear();
	}

	void Application::exit() {
		exitRequested = true;
	}

	void Application::addArgument(const std::string& arg) {
		arguments.push_back(arg);
	}

	void Application::run() {

		// Initialize GLFW and check it did it correctly
		// If the application doesn't initiate, exit the application
		if (glfwInit() == GLFW_FALSE)
			throw std::exception("Application could not initiate GLFW.");

		// Set the custom error callback
		// to diagnostic any possible error in 
		// the lifetime of the glfw application
		glfwSetErrorCallback(&Application::diagnosticErrors);

		volatile unsigned int points = 0;

		while (!(contexts.empty() && exitRequested) && points < 1000) {
			// Update glfw callbacks
			glfwPollEvents();
			points++;
		}

		// End all the active contexts before ending application
		for (const auto& context : contexts)
			context->endContext();

		// Terminate the glfw application
		// after all contexts are ended correctly
		glfwTerminate();
	}
}