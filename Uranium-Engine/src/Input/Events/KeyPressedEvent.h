#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class KeyboardCallback;
}

namespace Uranium::Input::Events {

	class KeyPressedEvent final : public Event {
	public:
		friend Callbacks::KeyboardCallback;

		/*
		* Creates a new key pressed event holding the
		* key character and the scancode.
		*/
		explicit KeyPressedEvent(int keyChar, int count, int scancode) noexcept :
			Event(EventType::KEYBOARD_KEY_PRESSED),
			keyChar(keyChar),
			count(count),
			scancode(scancode)
		{

		}

		~KeyPressedEvent() = default;

	public:
		int getKey() const {
			return keyChar;
		}

		int getCount() const {
			return count;
		}

		int getScancode() const {
			return scancode;
		}

	private:
		int count;
		int keyChar;
		int scancode;
	};
}