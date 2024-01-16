#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include <stdexcept>
#include "Core/Logger.h"

#include "Monitor.h"
#include "Input/Callbacks/MonitorCallback.h"

namespace Uranium::Platform::Interface {

	Input::Callbacks::MonitorCallback* Monitor::callback = nullptr;

	void Monitor::init() {
		UR_ASSERT(Monitor::callback != nullptr, "[Monitor]", "Monitor instance cannot be initialized more than once!");

		// Create new monitor callback and avaliable monitor list.
		Monitor::callback = new Input::Callbacks::MonitorCallback();
		//Monitor::availableMonitors = new std::vector<MonitorRef>();
	}

	void Monitor::dispose() noexcept {
		//Monitor::availableMonitors->clear();

		//delete Monitor::availableMonitors;
		delete Monitor::callback;
	}

	void Monitor::fetchAvailableMonitors(const EventCallbackFn& callbackEvent) {
		UR_ASSERT(Monitor::callback == nullptr, "[Monitor]", "Monitor instance has to be initailized before use!");

		// Clear before fetching
		//Monitor::availableMonitors->clear(); 
		
		int monitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		//for (int i = 0; i < monitorCount; i++)
		//	Monitor::availableMonitors->push_back(std::make_shared<Monitor>(monitors[i], callbackEvent));

		if (monitorCount == 0)
			throw std::runtime_error("No monitors were available.");
	}

	Monitor::MonitorRef Monitor::getPrimary() noexcept {
		//if (Monitor::availableMonitors->empty())
		//	return nullptr;
		//return Monitor::availableMonitors->at(0);
		return nullptr;
	}

	const std::vector<Monitor::MonitorRef>& Monitor::getConnectedMonitors() noexcept {
		//return *Monitor::availableMonitors;
		return {};
	}

	Monitor::Monitor(GLFWmonitor* monitor, const Input::Events::Event::EventCallbackFn& callbackEvent) noexcept :
		monitor(monitor),
		vidmode(nullptr),
		connected(true),
		callbackFunction(callbackEvent)
	{
		glfwSetMonitorUserPointer(monitor, this);

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
		return connected;
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