#include <GLFW/glfw3.h>

#include "Monitor.h"
#include "Uranium/Utils/Dimension.h"

namespace Uranium::Graphics::Display {

	Monitor::Monitor(GLFWmonitor* monitor) :
		monitor(monitor),
		vidmode(nullptr)
	{
		if (monitor != nullptr)
			vidmode = glfwGetVideoMode(monitor);
	}

	Monitor::operator GLFWmonitor* () {
		return monitor;
	}

	bool Monitor::isConnected() {
		return monitor != nullptr;
	}

	Utils::Dimension Monitor::getDimensions() {
		if (vidmode == nullptr)
			return Dimension(GLFW_DONT_CARE, GLFW_DONT_CARE);
		return Dimension(vidmode->width, vidmode->height);
	}

	int Monitor::getRefreshRate() {
		if (vidmode == nullptr)
			return GLFW_DONT_CARE;
		return vidmode->refreshRate;
	}
}



