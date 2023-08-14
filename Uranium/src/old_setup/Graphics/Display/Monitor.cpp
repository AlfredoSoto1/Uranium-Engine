#include "Monitor.h"

#include <GLFW/glfw3.h>

using namespace Uranium::Graphics::Display;

std::shared_ptr<Monitor> Monitor::getPrimaryMonitor() {
	return std::shared_ptr<Monitor>(new Monitor(glfwGetPrimaryMonitor()));
}

std::vector<std::shared_ptr<Monitor>> Monitor::getConnectedMonitors() {
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);

	std::vector<std::shared_ptr<Monitor>> result;
	for (int i = 0; i < count ;i++)
		result.push_back(std::shared_ptr<Monitor>(new Monitor(monitors[i])));
	return result;
}

Monitor::Monitor(GLFWmonitor* monitor) :
	monitor(monitor),
	vidmode(glfwGetVideoMode(monitor))
{
	
}

Monitor::Monitor() :
	monitor(nullptr),
	vidmode(nullptr)
{

}

Monitor::~Monitor() {

}

Monitor::operator GLFWmonitor* () {
	return monitor;
}

int Monitor::getWidth() {
	if (vidmode == nullptr)
		return 0;
	return vidmode->width;
}

int Monitor::getHeight() {
	if (vidmode == nullptr)
		return 0;
	return vidmode->height;
}

int Monitor::getRefreshRate() {
	if (vidmode == nullptr)
		return 0;
	return vidmode->refreshRate;
}

