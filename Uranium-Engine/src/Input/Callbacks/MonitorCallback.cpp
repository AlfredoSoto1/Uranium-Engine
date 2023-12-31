#include <GL/glfw3.h>

#include "MonitorCallback.h"

namespace Uranium::Input::Callbacks {

	MonitorCallback::MonitorCallback() noexcept {
        // Set the monitor callback        
        glfwSetMonitorCallback(MonitorCallback::monitorEvent);
	}

    void MonitorCallback::monitorEvent(GLFWmonitor* monitor, int event) {

        if (event == GLFW_CONNECTED) {
            // The monitor was connected
        }
        else if (event == GLFW_DISCONNECTED) {
            // The monitor was disconnected
        }
    }
}