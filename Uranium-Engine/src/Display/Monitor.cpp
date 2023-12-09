#include <GL/glfw3.h>

#include "Monitor.h"

namespace Uranium::Display {

	std::vector<std::unique_ptr<Monitor>> Monitor::getConnectedMonitors() {
		// Obtain the monitor count that GLFW provides
		int monitorCount;
		// Retrieve a C array from GLFW 
		// with the returned monitor count
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		// Store the monitors obtained by GLFW
		// into an std::vector
		std::vector<std::unique_ptr<Monitor>> connectedMonitors;
		for (int i = 0; i < monitorCount; i++)
			if(monitors[i] != nullptr)
				connectedMonitors.push_back(std::make_unique<Monitor>(monitors[i]));
		return connectedMonitors;
	}

	std::unique_ptr<Monitor> Monitor::getPrimary() {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		if(monitor != nullptr)
			return std::make_unique<Monitor>(monitor);
		return nullptr;
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

	Monitor::Monitor(GLFWmonitor* monitor) noexcept :
		monitor(monitor),
		vidmode(nullptr)
	{
		// set the video mode after the monitor instance
		// has already reserved space in memory to avoid
		// missbehavior when getting the video mode.
		vidmode = glfwGetVideoMode(monitor);
	}
}