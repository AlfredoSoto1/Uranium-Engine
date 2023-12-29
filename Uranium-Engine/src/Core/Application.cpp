#include <GL/glfw3.h>

#include "Core/Application.h"
#include "Platform/Monitor/MonitorHandler.h"

namespace Uranium::Core {

	std::unique_ptr<Application> Application::application = nullptr;

	void Application::diagnosticErrors(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		std::printf("Error [%i]: %s\n", error, description);
	}

	Application::Application() noexcept :
		isRunning(true),
		terminalArguments()
	{
		if (application != nullptr)
			__debugbreak(); // REMOVE

		// Initialize GLFW and check it did it correctly
		// If the application doesn't initiate, exit the application
		if (glfwInit() == GLFW_FALSE)
			__debugbreak(); // REMOVE // throw std::exception("Application could not initiate GLFW.");

		// Set the custom error callback
		// to diagnostic any possible error in 
		// the lifetime of the glfw application
		glfwSetErrorCallback(&Application::diagnosticErrors);

		// Initiate the monitor handler
		Platform::Monitor::MonitorHandler::initMonitors();
	}

	Application::~Application() {
		using namespace Platform::Monitor;

		// Dispose all window instances
		MonitorHandler::disposeMonitors();

		// Terminate GLFW after initializing
		glfwTerminate();
		terminalArguments.clear();
	}

	void Application::start() noexcept {

		while (isRunning) {

		}
	}
}