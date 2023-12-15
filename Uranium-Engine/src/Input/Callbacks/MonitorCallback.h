#pragma once

namespace Uranium::Core::Engine {
	class BaseEngine;
}

namespace Uranium::Input::Callbacks {

	class MonitorCallback final {
	private:
		/*
		* Friends with other classes
		*/
		friend Core::Engine::BaseEngine;

	private:
		/*
		* it gets called when a monitor gets created
		*/
		static void monitorEvent(GLFWmonitor* monitor, int event);

	private:
		/*
		* Monitor Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit MonitorCallback() noexcept;

		~MonitorCallback();

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		MonitorCallback(MonitorCallback&) = delete;
		MonitorCallback(MonitorCallback&&) = delete;
		MonitorCallback(const MonitorCallback&) = delete;
		MonitorCallback(const MonitorCallback&&) = delete;
	};
}