#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowMinimizedEvent final : public Event {
	public:
		/*
		* Creates a minimize event when the window gets iconified
		*/
		explicit WindowMinimizedEvent(bool minimized) noexcept :
			Event(EventType::WINDOW_MINIMIZE),
			minimized(minimized)
		{

		}

		~WindowMinimizedEvent() = default;

	public:
		/*
		* Returns true if the window is minimized, false otherwise
		*/
		bool isMinimized() const {
			return minimized;
		}

	private:
		bool minimized;
	};
}