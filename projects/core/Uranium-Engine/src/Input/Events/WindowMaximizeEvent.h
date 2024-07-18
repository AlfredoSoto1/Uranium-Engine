#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowMaximizedEvent final : public Event {
	public:
		/*
		* Creates a maximize event when the window gets maximized
		*/
		explicit WindowMaximizedEvent(bool maximized) noexcept :
			Event(EventType::WINDOW_MAXIMIZE),
			maximized(maximized)
		{

		}

		~WindowMaximizedEvent() = default;

	public:
		/*
		* Returns true if the window is maximized, false otherwise
		*/
		bool isMaximized() const {
			return maximized;
		}

	private:
		bool maximized;
	};
}