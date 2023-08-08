#include <GLFW/glfw3.h>

#include "MonitorCallback.h"
#include "Uranium/Graphics/Display/Monitor.h"

namespace Uranium::Callbacks {

	MonitorCallback::MonitorCallback() {

	}

    void MonitorCallback::monitorCallback(GLFWmonitor* monitor, int event) {

        using Graphics::Display::Monitor;


        if (event == GLFW_CONNECTED) {
            // The monitor was connected
        }
        else if (event == GLFW_DISCONNECTED) {
            // The monitor was disconnected
        }
    }
}