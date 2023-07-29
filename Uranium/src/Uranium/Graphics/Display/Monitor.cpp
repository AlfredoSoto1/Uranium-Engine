#include <GLFW/glfw3.h>

#include "Monitor.h"
#include "Uranium/Utils/Dimension.h"

namespace Uranium::Graphics::Display {

	std::vector<Monitor> Monitor::getConnectedMonitors() {
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

	Monitor Monitor::getPrimaryMonitor() {
		// Returns a new Monitor object containing
		// all data from the primary monitor
		return Monitor(glfwGetPrimaryMonitor());
	}

	Monitor::Monitor(GLFWmonitor* monitor) :
		monitor(monitor),
		vidmode(nullptr)
	{
		if (monitor != nullptr)
			vidmode = glfwGetVideoMode(monitor);
	}

	Monitor::operator GLFWmonitor* () const {
		return monitor;
	}

	bool Monitor::isConnected() const {
		return monitor != nullptr;
	}

	Monitor::Dimension Monitor::getResolution() const {
		if (vidmode == nullptr)
			return Dimension(GLFW_DONT_CARE, GLFW_DONT_CARE);
		return Dimension(vidmode->width, vidmode->height);
	}

	int Monitor::getRefreshRate() const {
		if (vidmode == nullptr)
			return GLFW_DONT_CARE;
		return vidmode->refreshRate;
	}
}
