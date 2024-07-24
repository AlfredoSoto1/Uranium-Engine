module uranium.core;

import uranium.services;

//#include <stdexcept>
//#include "Logger.h"
//#include "Application.h"

//#include "Platform/Interface/Window.h"
//#include "Platform/Interface/Monitor.h"
//#include "Platform/Interface/GraphicsAPI.h"

namespace uranium::core {

	std::unique_ptr<Application> Application::application = nullptr;

	Application& Application::instance() {
		return *application;
	}

	Application::Application() noexcept :
		logger(),
		isRunning(true)
	{
		//UR_ASSERT(Application::application != nullptr, "[Application]", "Already instantiated!");
	}

	services::Logger& Application::log() noexcept {
		return logger;
	}

	int Application::start(std::unique_ptr<Application> application) {
		// Assert here if application is started more than once
		// Set up singleton
		Application::application = std::move(application);
		
		// Boot up services
		

		// Handle application life-time
		Application::application->init();
		//Application::application->shutdown();

		// Query for application errors
		// Display all the errors and return error code

		// Free application
		Application::application.reset();

		return 0; // Success error code
	}
	
	void Application::init() noexcept {

	}
	
	void Application::shutdown() noexcept {

	}

	void Application::interrupt() noexcept {

	}

	void Application::exit(int code) noexcept {

	}

	std::vector<int> Application::queryErrors() noexcept {
		return {};
	}

	//void Application::start() noexcept {

		//try {
		//	// Initialize windowing and monitor
		//	Window::init();
		//	Monitor::init();
		//}
		//catch (const std::runtime_error& error) {
		//	Core::UR_ERROR("[Application : Initiation]", error.what());
		//	return;
		//}

		//try {
		//	// Fetch the available monitors and bind the event function
		//	// to react whenever an event happens during callback.
		//	Monitor::fetchAvailableMonitors(UR_BIND_FUNC(Application::onEvent, std::placeholders::_1));
		//}
		//catch (const std::runtime_error& error) {
		//	Core::UR_ERROR("[Application : Monitor fetch]", error.what());
		//	return;
		//}

		// Initialize and prepare the Graphics API.
		// The desired API is provided by the client who will
		// choose which API to use.
		//graphicsAPI = prepareGraphicsAPI(); // TODO

	/*	window = createWindow();

		window->createCallbacks();
		window->setEventCallback(UR_BIND_FUNC(Application::onEvent, std::placeholders::_1));

		while (!window->shouldClose()) {
			window->onUpdate();
		}

		window->disposeCallbacks();

		delete window.release();*/

		// Dispose monitor and all windowing
		//Monitor::dispose();
		//Window::dispose();
	//}
}
