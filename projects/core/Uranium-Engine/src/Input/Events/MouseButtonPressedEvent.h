#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class MouseCallback;
}

namespace Uranium::Input::Events {

	class MouseButtonPressedEvent final : public Event {
	public:
		friend Callbacks::MouseCallback;

		/*
		* Creates a new event when any of the mouse button are pressed
		*/
		explicit MouseButtonPressedEvent(int mouseButton) noexcept :
			Event(EventType::MOUSE_PRESSED),
			mouseButton(mouseButton)
		{

		}

		~MouseButtonPressedEvent() = default;

	public:
		int getButton() const {
			return mouseButton;
		}

	private:
		int mouseButton;
	};
}