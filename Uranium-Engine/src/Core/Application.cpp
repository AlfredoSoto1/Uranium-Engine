#include <stdexcept>
#include <stdexcept>

#include "Logger.h"
#include "Application.h"

#include "Platform/Interface/Window.h"
#include "Platform/Interface/Monitor.h"
#include "Platform/Interface/GraphicsAPI.h"

namespace Uranium::Core {

	using namespace Platform::Interface;

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

		// Initialize windowing and monitor
		Window::init();
		Monitor::init();
	}

	Application::~Application() noexcept {
		// Dispose monitor and all windowing
		Monitor::dispose();
		Window::dispose();
	}

	Application::Window& Application::getWindow() {
		return *window;
	}

	void Application::start() noexcept {

		// Fetch the available monitors and bind the event function
		// to react whenever an event happens during callback.
		Monitor::fetchAvailableMonitors(UR_BIND_FUNC(Application::onEvent, std::placeholders::_1));

		// Initialize and prepare the Graphics API.
		// The desired API is provided by the client who will
		// choose which API to use.
		graphicsAPI = prepareGraphicsAPI();

		window = createWindow();

		window->createCallbacks();
		window->setEventCallback(UR_BIND_FUNC(Application::onEvent, std::placeholders::_1));

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