#include <iostream>
#include <GL/glfw3.h>

#include "Program/Application.h"
#include "Services/ThreadService.h"

namespace Uranium::Program {

	// Initialize static variable
	std::unique_ptr<Application> Application::application = nullptr;

	Application& Application::instance() {
		return *application;
	}

	void Application::build(int argc, char* argv[], std::unique_ptr<Application> createdApplication) {

		// move the created application to a global space
		application = std::move(createdApplication);

		// Pass all the arguments from the terminal to the application
		for (int i = 0; i < argc; i++)
			application->addArgument(argv[i]);

		// Run the application
		application->run();

		// Move the global application to local scope so that it can get released
		createdApplication = std::move(application);
	}

	void Application::diagnosticErrors(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		std::printf("Error [%i]: %s\n", error, description);
	}

	Application::Application() noexcept :
		arguments(),
		services()
	{
	}

	Application::~Application() {
		services.clear();
		arguments.clear();
	}

	void Application::registerService(std::unique_ptr<Services::ThreadService> service) {
		services.emplace_back(std::move(service));
	}

	void Application::addArgument(const std::string& arg) {
		arguments.push_back(arg);
	}

	void Application::run() {
		// Initialize GLFW and check it did it correctly
		// If the application doesn't initiate, exit the application
		if (glfwInit() == GLFW_FALSE)
			throw std::exception("Application could not initiate GLFW.");

		// Initiate all the services
		for (auto& service : services)
			service->init();

		// Set the custom error callback
		// to diagnostic any possible error in 
		// the lifetime of the glfw application
		glfwSetErrorCallback(&Application::diagnosticErrors);

		while (!services.empty() && Services::ThreadService::activeThreadCount() != 0) {
			// Update glfw callbacks
			glfwPollEvents();
		}

		// End all the active contexts before ending application
		for (auto& service : services)
			service->prune();

		glfwTerminate();
	}
}