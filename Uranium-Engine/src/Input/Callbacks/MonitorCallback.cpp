#include <GLFW/glfw3.h>
#include "Core/Logger.h"

#include "MonitorCallback.h"
#include "Platform/Interface/Monitor.h"
#include "Input/Events/MonitorConnectionEvent.h"

namespace Uranium::Input::Callbacks {

	MonitorCallback::MonitorCallback() noexcept {
        // Set the monitor callback        
        glfwSetMonitorCallback(MonitorCallback::monitor_callback);
        Core::UR_INFO("[Monitor Callback]", "Monitor callback created");
	}

    void MonitorCallback::monitor_callback(GLFWmonitor* glfwMonitor, int event) noexcept {
		using namespace Events;
		using namespace Platform::Interface;
		Monitor& monitor = *(Monitor*)glfwGetMonitorUserPointer(glfwMonitor);

		switch (event) {
		case GLFW_CONNECTED:
			{
				// The monitor was connected
				Core::UR_TRACE("[Monitor Callback]", "Monitor Connected");
				monitor.connected = true;
				MonitorConnectionEvent event(true, monitor);
				monitor.callbackFunction(event);
				break;
			}
		case GLFW_DISCONNECTED:
			{
				// The monitor was disconnected
				Core::UR_TRACE("[Monitor Callback]", "Monitor Disconnected");
				monitor.connected = false;
				MonitorConnectionEvent event(false, monitor);
				monitor.callbackFunction(event);
				break;
			}
		}
    }
}