#include <GL/glfw3.h>

#include "Core/BaseEngine.h"
#include "Services/Application.h"
#include "Display/MonitorHandler.h"

namespace Uranium::Services {

	Application* Application::application = nullptr;

	Application& Application::instance() {
		return *application;
	}

	void Application::diagnosticErrors(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		std::printf("Error [%i]: %s\n", error, description);
	}

	Application::Application() noexcept :
		arguments(),
		baseEngine(nullptr)
	{
	}

	Application::~Application() {
		arguments.clear();
		baseEngine.reset();
	}

	Core::BaseEngine& Application::getBaseEngine() {
		return *baseEngine;
	}

	void Application::addArgument(const std::string& arg) {
		arguments.push_back(arg);
	}

	void Application::init() const {
		// Initialize GLFW and check it did it correctly
		// If the application doesn't initiate, exit the application
		if (glfwInit() == GLFW_FALSE)
			throw std::exception("Application could not initiate GLFW.");
		
		// Set the custom error callback
		// to diagnostic any possible error in 
		// the lifetime of the glfw application
		glfwSetErrorCallback(&Application::diagnosticErrors);

		// Initiate the monitor handler
		Display::MonitorHandler::initMonitors();
	}

	void Application::run() {

		// Runs the base engine
		baseEngine->run();

		// Dispose all monitors
		Display::MonitorHandler::disposeMonitors();

		// Terminates the GLFW content
		glfwTerminate();

	}
}