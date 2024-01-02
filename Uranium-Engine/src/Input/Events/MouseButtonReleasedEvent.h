#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class MouseCallback;
}

namespace Uranium::Input::Events {

	class MouseButtonReleasedEvent final : public Event {
	public:
		friend Callbacks::MouseCallback;

		/*
		* Creates a new event when any of the mouse button are released
		*/
		explicit MouseButtonReleasedEvent(int mouseButton) noexcept :
			Event(EventType::MOUSE_RELEASED),
			mouseButton(mouseButton)
		{

		}

		~MouseButtonReleasedEvent() = default;

	public:
		int getButton() const {
			return mouseButton;
		}

	private:
		int mouseButton;
	};
}