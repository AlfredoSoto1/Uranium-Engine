#pragma once

namespace Uranium::Callbacks {

	class MonitorCallback {
	public:
		/*
		* Delete the move/copy constructors
		* since we dont want the client to instantiate this class
		*/
		MonitorCallback(MonitorCallback& copy) = delete;
		MonitorCallback(MonitorCallback&& move) = delete;
		MonitorCallback(const MonitorCallback& copy) = delete;
		MonitorCallback(const MonitorCallback&& move) = delete;

	private:
		/*
		* Private static methods
		*/
		static void monitorCallback(GLFWmonitor* monitor, int event);

	private:
		/*
		* Private modifiers
		*/
		explicit MonitorCallback();
	};
}