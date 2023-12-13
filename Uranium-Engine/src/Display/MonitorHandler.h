#pragma once

#include <memory>
#include <vector>

namespace Uranium::Services {
	extern class Application;
}

namespace Uranium::Display {

	class Monitor;

	class MonitorHandler final {
	public:
		/*
		* Friends with other classes
		*/
		friend Services::Application;

	public:
		/*
		* Returns the primary connected monitor.
		* If monitor is not connected it will return nullptr.
		*/
		static std::shared_ptr<Monitor> getPrimary();

		/*
		* Returns a vector of unique references to
		* all the monitors that are connected.
		*/
		static std::vector<std::shared_ptr<Monitor>> getConnectedMonitors();

	private:
		/*
		* Initializes and creates all avaliable monitors
		*/
		static void initMonitors();

		/*
		* Disposes all created monitors
		*/
		static void disposeMonitors();

		/*
		* list of all available monitors connected
		*/
		static std::unique_ptr<std::vector<std::shared_ptr<Monitor>>> availableMonitors;

	private:
		/*
		* Creates a new monitor-handler instance
		*/
		MonitorHandler() = default;

		/*
		* Prepare the default monitor-handler destructor
		*/
		~MonitorHandler() = default;
	};
}