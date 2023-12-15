#include <GL/glfw3.h>

#include "Core/Application.h"
#include "Core/Engine/BaseEngine.h"
#include "Platform/Monitor/MonitorHandler.h"

namespace Uranium::Core {

	using namespace Engine;
	using namespace Platform::Display;
	using namespace Platform::Monitor;

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

	/*
	* Initiate the application
	*/
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
		MonitorHandler::initMonitors();
	}

	/*
	* Run the application
	*/
	void Application::run() {

		// Start running the base engine
		baseEngine->run();
	}

	/*
	* Delete the application
	*/
	Application::~Application() {

		MonitorHandler::disposeMonitors();

		arguments.clear();
		baseEngine.reset();

		glfwTerminate();
	}

	BaseEngine& Application::getBaseEngine() {
		return *baseEngine;
	}

	void Application::addArgument(const std::string& arg) {
		arguments.push_back(arg);
	}
}