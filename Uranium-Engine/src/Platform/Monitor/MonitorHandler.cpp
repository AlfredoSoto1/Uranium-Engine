#include <GLFW/glfw3.h>

#include "Monitor.h"
#include "MonitorHandler.h"

namespace Uranium::Platform::Monitor {
	
	std::unique_ptr<std::vector<std::shared_ptr<Monitor>>> MonitorHandler::availableMonitors = nullptr;

	void MonitorHandler::initMonitors() {
		// Initialize the vector of available monitors
		MonitorHandler::availableMonitors = std::make_unique<std::vector<std::shared_ptr<Monitor>>>();

		// Obtain the monitor count that GLFW provides
		int monitorCount;

		// Get all the available monitors
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		// Store the monitors obtained by GLFW
		for (int i = 0; i < monitorCount; i++)
			if (monitors[i] != nullptr)
				MonitorHandler::availableMonitors->push_back(std::make_shared<Monitor>(monitors[i]));
	}

	void MonitorHandler::disposeMonitors() {
		// Release the pointer
		std::vector<std::shared_ptr<Monitor>>* allMonitors = MonitorHandler::availableMonitors.release();
		// Clear the vector
		allMonitors->clear();
		// Free all monitors
		delete allMonitors;
	}

	std::shared_ptr<Monitor> MonitorHandler::getPrimary() {
		if (MonitorHandler::availableMonitors->empty())
			return nullptr;
		return MonitorHandler::availableMonitors->at(0);
	}

	std::vector<std::shared_ptr<Monitor>> MonitorHandler::getConnectedMonitors() {
		return *MonitorHandler::availableMonitors;
	}
}