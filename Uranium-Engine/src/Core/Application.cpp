#include <GLFW/glfw3.h>
#include <iostream>

#include "Core/Application.h"
#include "Platform/Display/Window.h"
#include "Platform/Monitor/MonitorHandler.h"

namespace Uranium::Core {

	std::unique_ptr<Application> Application::application = nullptr;

	Application::Application() noexcept :
		isRunning(true)
	{
		if (Application::application != nullptr)
			throw std::runtime_error("Application has already started!!");

		using namespace Platform::Monitor;
		// Initiate the monitor handler
		Platform::Monitor::MonitorHandler::initMonitors();
	}

	Application::~Application() noexcept {
		using namespace Platform::Monitor;
		// Dispose all window instances
		MonitorHandler::disposeMonitors();
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

	}
}