#pragma once

struct GLFWmonitor;

namespace Uranium::Callbacks {

	class MonitorCallback {
	public:
		explicit MonitorCallback();

	private:
		/*
		* private members
		*/
		void monitorResponse(GLFWmonitor* monitor, int event);
	};
}