#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include "Core/Logger.h"

#include "Monitor.h"

namespace Uranium::Platform::Interface {

	Monitor::Monitor(GLFWmonitor* monitor) noexcept :
		monitor(monitor),
		vidmode(nullptr)
	{
		// set the video mode after the monitor instance
		// has already reserved space in memory to avoid
		// missbehavior when getting the video mode.
		vidmode = glfwGetVideoMode(monitor);

		UR_ASSERT(vidmode == nullptr, "[Monitor]", "Video mode is null!");
	}

	Monitor::operator GLFWmonitor* () const noexcept {
		return monitor;
	}

	bool Monitor::isConnected() const noexcept {
		return monitor != nullptr;
	}

	unsigned int Monitor::gerRefreshRate() const noexcept {
		return vidmode == nullptr ? GLFW_DONT_CARE : vidmode->refreshRate;
	}

	glm::ivec2 Monitor::getResolution() const noexcept {
		if (vidmode == nullptr)
			return glm::ivec2(GLFW_DONT_CARE, GLFW_DONT_CARE);
		return glm::ivec2(vidmode->width, vidmode->height);
	}
}