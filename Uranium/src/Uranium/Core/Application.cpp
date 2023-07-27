#include <memory>
#include <thread>
#include <functional>

#include <GLFW/glfw3.h>

#include "EngineTools.h"

#include "WorkingUnit.h"
#include "Application.h"

#include "Uranium/Graphics/Display/Monitor.h"

#include "Uranium/Callbacks/MonitorCallback.h"

namespace Uranium::Core {

	volatile bool Application::glfwInitiated = false;
	volatile bool Application::applicationStarted = false;

	volatile bool Application::isGLFWActive() {
		return glfwInitiated;
	}

	volatile bool Application::hasAppStarted() {
		return applicationStarted;
	}

	Application::Application() {
		if (glfwInit() == GLFW_FALSE)
			throw std::exception("GLFW could not initialize correctly.");

		// Initiated successfully
		glfwInitiated = true;

		glfwSetErrorCallback(&Application::errorCallbackReceive);
	}

	Application::~Application() {
		if (not glfwInitiated)
			return;

		delete monitorCallback;

		glfwTerminate();
	}
	
	void Application::errorCallbackReceive(int error, const char* description) {
		// Print the error to the console. We dont use the built-in
		// print_status() macro because we want to detect errors even
		// on release. (Could change in the future)
		fprintf(stderr, "Error: %s\n", description);
	}

	Graphics::Display::Monitor Application::getPrimaryMonitor() {
		// Returns a new Monitor object containing
		// all data from the primary monitor
		return Monitor(glfwGetPrimaryMonitor());
	}

	std::vector<Graphics::Display::Monitor> Application::getConnectedMonitors() {
		// Obtain the monitor count that GLFW provides
		int monitorCount;
		// Retrieve a C array from GLFW 
		// with the returned monitor count
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		// Store the monitors obtained by GLFW
		// into an std::vector
		std::vector<Monitor> connectedMonitors;
		for (int i = 0; i < monitorCount; i++)
			connectedMonitors.push_back(Monitor(monitors[i]));
		return connectedMonitors;
	}

	void Application::run() {

		// Start application flag
		applicationStarted = true;

		createCallbacks();

		while (glfwInitiated) {
			// update application here
		}
	}

	void Application::createCallbacks() {
		monitorCallback = new Callbacks::MonitorCallback();
	}
}