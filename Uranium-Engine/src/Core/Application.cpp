#include <stdexcept>

#include "Logger.h"
#include "Application.h"

#include "Platform/Interface/Window.h"
#include "Platform/Interface/GraphicsAPI.h"
#include "Platform/Monitor/MonitorHandler.h"

namespace Uranium::Core {

	std::unique_ptr<Application> Application::application = nullptr;

	Application& Application::instance() {
		return *application;
	}

	Application::Application() noexcept :
		isRunning(true),

		window(nullptr),
		graphicsAPI(nullptr)
	{
		UR_ASSERT(Application::application != nullptr, "[Application]", "Already instantiated!");

		using namespace Platform::Monitor;
		// Initiate the monitor handler
		Platform::Monitor::MonitorHandler::initMonitors();

		Window::initWindowAPI();
	}

	Application::~Application() noexcept {
		using namespace Platform::Monitor;
		// Dispose all window instances
		MonitorHandler::disposeMonitors();

		Window::shutdownWindowAPI();
	}

	Application::Window& Application::getWindow() {
		return *window;
	}

	void Application::start() noexcept {
		graphicsAPI = prepareGraphicsAPI();

		window = createWindow();

		window->createCallbacks();
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		while (!window->shouldClose()) {
			window->onUpdate();
		}

		window->disposeCallbacks();

		delete window.release();
	}

	void Application::onEvent(Input::Events::Event& e) {
		// This gets called when an event happens

	}
}