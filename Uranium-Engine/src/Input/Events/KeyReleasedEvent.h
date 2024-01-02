#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class KeyboardCallback;
}

namespace Uranium::Input::Events {

	class KeyReleasedEvent final : public Event {
	public:
		friend Callbacks::KeyboardCallback;

		/*
		* Creates a new key release event holding the key character and scancode
		*/
		explicit KeyReleasedEvent(int keyChar, int scancode) noexcept :
			Event(EventType::KEYBOARD_KEY_RELEASED),
			keyChar(keyChar),
			scancode(scancode)
		{

		}

		~KeyReleasedEvent() = default;

	public:
		int getKey() const {
			return keyChar;
		}

		int getScancode() const {
			return scancode;
		}

	private:
		int keyChar;
		int scancode;
	};
}