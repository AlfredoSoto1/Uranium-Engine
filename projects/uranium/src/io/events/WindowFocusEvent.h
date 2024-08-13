#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowFocusEvent final : public Event {
	public:
		/*
		* Creates a new focus event whenever the window
		* detects that it needs to be focused
		*/
		explicit WindowFocusEvent(bool focused) noexcept :
			Event(EventType::WINDOW_FOCUS),
			focused(focused)
		{

		}

		~WindowFocusEvent() = default;

	public:
		/*
		* Returns true if the window is focused, false otherwise
		*/
		bool isFocused() const {
			return focused;
		}

	private:
		bool focused;
	};

}