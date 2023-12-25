#include <GL/glfw3.h>

#include "Core/Application.h"
#include "Engine/BaseEngine.h"
#include "Platform/Monitor/MonitorHandler.h"

namespace Uranium::Core {

	Application* Application::application = nullptr;

	Application& Application::instance() {
		return *application;
	}

	Engine::BaseEngine& Application::getBaseEngine() {
		return *baseEngine;
	}

	void Application::diagnosticErrors(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		std::printf("Error [%i]: %s\n", error, description);
	}

	Application::Application() noexcept :
		baseEngine(),
		terminalArguments()
	{
		using namespace Platform::Monitor;

		// Initialize GLFW and check it did it correctly
		// If the application doesn't initiate, exit the application
		if (glfwInit() == GLFW_FALSE)
			throw std::exception("Application could not initiate GLFW.");

		// Set the custom error callback
		// to diagnostic any possible error in 
		// the lifetime of the glfw application
		glfwSetErrorCallback(&Application::diagnosticErrors);

		// Initiate the monitor handler
		MonitorHandler::initMonitors();
	}

	Application::~Application() {
		using namespace Platform::Monitor;

		// Dispose all window instances
		MonitorHandler::disposeMonitors();

		terminalArguments.clear();
		
		// Terminate GLFW after initializing
		glfwTerminate();
	}

	void Application::start() noexcept {
		
		// Create display and prepare the context
		baseEngine->createDisplayContext();

		// Initiate the engine members and managers
		baseEngine->init();

		// Run and update engine
		baseEngine->run();

		// Dispose all engine content initiated
		baseEngine->dispose();
	}
}