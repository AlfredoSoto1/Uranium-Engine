#pragma once

#include <memory>
#include <vector>

#include "Core/CoreMacros.h"

namespace Uranium::Core {
	UR_DECLARE Application;
}

namespace Uranium::Input::Callbacks {
	UR_DECLARE MonitorCallback;
}

namespace Uranium::Platform::Interface {

	UR_DECLARE Monitor;

	URANIUM_API class MonitorHandler final {
	public:
		static void initMonitorAPI();              // Initializes the monitor API and fetches for all monitors that are connected.
		static void shutdownMonitorAPI() noexcept; // Shutsdown the monitor API.

	public:
		/*
		* If monitor is not connected it will return nullptr.
		* 
		* @return primary monitor connected.
		*/
		static std::shared_ptr<Monitor> getPrimary();

		/*
		* If no monitor connected, vector will be empty.
		* First element of the vector is the primary monitor.
		* 
		* @return vector containing all the references of the connected monitors.
		*/
		static std::vector<std::shared_ptr<Monitor>> getConnectedMonitors();

	private:
		friend Core::Application;
		/*
		* list of all available monitors connected
		*/
		static std::unique_ptr<std::vector<std::shared_ptr<Monitor>>> availableMonitors;

	private:
		MonitorHandler()  noexcept;
		~MonitorHandler() noexcept = default;

	private:
		std::unique_ptr<Input::Callbacks::MonitorCallback> monitorCallback;
	};
}