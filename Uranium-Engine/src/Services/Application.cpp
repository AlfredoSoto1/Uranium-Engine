#include <GL/glfw3.h>

#include "Services/BaseEngine.h"
#include "Services/Application.h"

namespace Uranium::Services {

	std::unique_ptr<Application> Application::application = nullptr;

	Application& Application::instance() {
		return *application;
	}

	void Application::build(int argc, char* argv[], std::unique_ptr<BaseEngine> baseEngine) {

		Application::application = std::make_unique<Application>();

		application->baseEngine = std::move(baseEngine);

		// Pass all the arguments from the terminal to the application
		for (int i = 0; i < argc; i++)
			application->addArgument(argv[i]);

		// Run the application
		application->run();

		// move the staic application reference
		// to local scope to free from memory once the application ends
		std::unique_ptr<Application> lastReference = std::move(application);
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
		
		baseEngine->run();

		// Terminates the GLFW content
		glfwTerminate();
	}
}