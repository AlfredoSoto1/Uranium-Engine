#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowRefreshEvent final : public Event {
	public:
		/*
		* Creates a new refresh event when the window gets refreshed
		*/
		explicit WindowRefreshEvent() noexcept :
			Event(EventType::WINDOW_REFRESH)
		{

		}

		~WindowRefreshEvent() = default;
	};
}
