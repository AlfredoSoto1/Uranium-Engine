#include <GLFW/glfw3.h>

#include <functional>

#include "MonitorCallback.h"

#include "Uranium/Core/Application.h"

namespace Uranium::Callbacks {

	MonitorCallback::MonitorCallback(const Core::Application& application) {
		
		glfwSetMonitorUserPointer()
		glfwSetMonitorCallback(&MonitorCallback::monitorResponse);
	}

	void MonitorCallback::monitorResponse(GLFWmonitor* monitor, int event) {

	}
}