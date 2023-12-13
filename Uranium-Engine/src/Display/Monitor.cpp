#include <GL/glfw3.h>

#include <memory>
#include <vector>
#include "Monitor.h"

namespace Uranium::Display {

	std::unique_ptr<std::vector<std::shared_ptr<Monitor>>> Monitor::availableMonitors = nullptr;

	void Monitor::initMonitors() {
		// Initialize the vector of available monitors
		Monitor::availableMonitors = std::make_unique<std::vector<std::shared_ptr<Monitor>>>();

		// Obtain the monitor count that GLFW provides
		int monitorCount;
		// Retrieve a C array from GLFW 
		// with the returned monitor count
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		// Store the monitors obtained by GLFW
		for (int i = 0; i < monitorCount; i++)
			if (monitors[i] != nullptr)
				Monitor::availableMonitors->push_back(std::make_shared<Monitor>(monitors[i]));
	}

	void Monitor::disposeMonitors() {
		// Release the pointer
		std::vector<std::shared_ptr<Monitor>>* allMonitors = Monitor::availableMonitors.release();
		// Clear the vector
		allMonitors->clear();
		// Free all monitors
		delete allMonitors;
	}

	std::shared_ptr<Monitor> Monitor::getPrimary() {
		if (Monitor::availableMonitors->empty())
			return nullptr;
		return Monitor::availableMonitors->at(0);
	}

	std::vector<std::shared_ptr<Monitor>> Monitor::getConnectedMonitors() {
		return *Monitor::availableMonitors;
	}

	Monitor::Monitor(GLFWmonitor* monitor) noexcept :
		monitor(monitor),
		vidmode(nullptr)
	{
		// set the video mode after the monitor instance
		// has already reserved space in memory to avoid
		// missbehavior when getting the video mode.
		vidmode = glfwGetVideoMode(monitor);
	}

	Monitor::operator GLFWmonitor* () const {
		return monitor;
	}

	bool Monitor::isConnected() const {
		return monitor != nullptr;
	}

	unsigned int Monitor::gerRefreshRate() const {
		return vidmode == nullptr ? GLFW_DONT_CARE : vidmode->refreshRate;
	}

	glm::ivec2 Monitor::getResolution() const {
		if (vidmode == nullptr)
			return glm::ivec2(GLFW_DONT_CARE, GLFW_DONT_CARE);
		return glm::ivec2(vidmode->width, vidmode->height);
	}
}