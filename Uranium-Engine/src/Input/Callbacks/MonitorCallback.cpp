#include <GLFW/glfw3.h>
#include "Core/Logger.h"

#include "MonitorCallback.h"
#include "Input/Events/MonitorConnectionEvent.h"

namespace Uranium::Input::Callbacks {

	MonitorCallback::MonitorCallback() noexcept {
        // Set the monitor callback        
        glfwSetMonitorCallback(MonitorCallback::monitor_callback);
        Core::UR_INFO("[Monitor Callback]", "Monitor callback created");
	}

    void MonitorCallback::monitor_callback(GLFWmonitor* monitor, int event) noexcept {
		using namespace Events;
		Monitor& window = *(Monitor*)glfwGetWindowUserPointer(glWindow);

		switch (event) {
		case GLFW_CONNECTED:
			{
				// The monitor was connected
				Core::UR_TRACE("[Monitor Callback]", "Monitor Connected");
				MonitorConnectionEvent event(true);
				window.callbackFunction(event);
				break;
			}
		case GLFW_DISCONNECTED:
			{
				// The monitor was disconnected
				Core::UR_TRACE("[Monitor Callback]", "Monitor Disconnected");
				MonitorConnectionEvent event(true);
				window.callbackFunction(event);
				break;
			}
		}
    }
}