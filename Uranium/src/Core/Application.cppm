import Uranium.Core.Context;
import Uranium.Core.Application;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>

namespace Uranium::Core {

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
		} catch (const std::exception& e) {
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

	Application::Application() noexcept :
		exitRequested(false),
		arguments(),
		contexts()
	{
		// These types of if statements that
		// serve to check conditions that should not
		// happen ever, need to be later in the future
		// turned into a macro so that in release this doesnt get evaluated
#ifdef _DEBUG
		if (instanceReference != nullptr)
			throw std::runtime_error("Instance of application already exists!");
#endif // _DEBUG
		// if the the application has not been created,
		// make it remember that an instance of it already exist
		instanceReference = this;
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
		
		// Create a virtual thread context if and only if
		// there is no context existing context before running the application
		if (contexts.empty())
			contexts.emplace_back(
				std::make_unique<Context>(Context::ThreadType::VIRTUAL_THREAD)
			);

		// Initialize GLFW and check it did it correctly
		// If the application doesn't initiate, exit the application
		if (glfwInit() == GLFW_FALSE)
			throw std::exception("Application could not initiate GLFW.");

		// Set the custom error callback
		// to diagnostic any possible error in 
		// the lifetime of the glfw application
		glfwSetErrorCallback(&Application::diagnosticErrors);

		while (!contexts.empty() && exitRequested) {
			// Update glfw callbacks
			glfwPollEvents();
		}

		// End all the active contexts before ending application
		for (const auto& context : contexts)
			context->endContext();

		// Terminate the glfw application
		// after all contexts are ended correctly
		glfwTerminate();
	}
}