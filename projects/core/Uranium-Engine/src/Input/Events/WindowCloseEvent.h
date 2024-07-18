#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowCloseEvent final : public Event {
	public:
		/*
		* Creates a new close event when the window request to be closed
		*/
		explicit WindowCloseEvent() noexcept :
			Event(EventType::WINDOW_CLOSE)
		{

		}

		~WindowCloseEvent() = default;
	};
}