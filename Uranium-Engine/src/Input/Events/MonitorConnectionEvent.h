#pragma once

#include "Event.h"
#include "Core/CoreMacros.h"

namespace Uranium::Platform::Interface {
	UR_DECLARE Monitor;
}

namespace Uranium::Input::Callbacks {
	UR_DECLARE MonitorCallback;
}

namespace Uranium::Input::Events {

	URANIUM_API class MonitorConnectionEvent final : UR_EXTENDS Event {
	public:
		friend Callbacks::MonitorCallback;

		/*
		* @brief
		* Creates a new event when any of the mouse button are pressed
		* 
		* @param connected
		*/
		explicit MonitorConnectionEvent(bool connected, const Platform::Interface::Monitor& monitor) noexcept :
			Event(EventType::MONITOR_CONNECTION),
			connected(connected),
			monitor(monitor)
		{

		}

		~MonitorConnectionEvent() noexcept = default;

	public:
		bool isConnected() const noexcept {
			return connected;
		}

		const Platform::Interface::Monitor& getMonitor() const {
			return monitor;
		}

	private:
		bool connected;
		const Platform::Interface::Monitor& monitor;
	};
}