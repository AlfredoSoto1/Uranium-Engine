#include <GL/glfw3.h>
#include <iostream>

#include "Core/Application.h"
#include "Platform/Display/Window.h"
#include "Input/Events/KeyEvents.h"
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

		using namespace Platform::Monitor;
		// Initiate the monitor handler
		Platform::Monitor::MonitorHandler::initMonitors();
	}

	Application::~Application() {
		using namespace Platform::Monitor;
		// Dispose all window instances
		MonitorHandler::disposeMonitors();

		glfwTerminate();
		terminalArguments.clear();
	}

	void Application::start() noexcept {
		windowDisplay = createWindow();

		windowDisplay->createCallbacks();
		windowDisplay->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		while (!windowDisplay->shouldClose()) {

			windowDisplay->onUpdate();
		}

		windowDisplay->disposeCallbacks();

		delete windowDisplay.release();
	}

	void Application::onEvent(Input::Events::Event& e) {
		// This gets called when an event happens

		using namespace Input::Events;

		switch (e.getEventType()) {
		case Event::EventType::KEYBOARD_KEY_PRESSED:
		{
			KeyPressedEvent& pressed = *static_cast<KeyPressedEvent*>(&e);
			std::cout << "Pressed: " << glfwGetKeyName(pressed.getKey(), pressed.getScancode()) << std::endl;
		}
			break;
		case Event::EventType::KEYBOARD_KEY_RELEASED:
		{
			KeyReleasedEvent& pressed = *static_cast<KeyReleasedEvent*>(&e);
			std::cout << "Released: " << glfwGetKeyName(pressed.getKey(), pressed.getScancode()) << std::endl;
		}
			break;
		}
	}
}