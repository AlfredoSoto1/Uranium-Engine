#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include "Monitor.h"

namespace Uranium::Platform::Monitor {

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