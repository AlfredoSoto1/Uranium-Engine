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
		/*
		* Returns the key code and the repeated ammount of times the key was pressed(on hold)
		*/
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

	class KeyReleasedEvent final : public Event {
	public:
		friend Callbacks::KeyboardCallback;

		/*
		*/
		explicit KeyReleasedEvent(int keyChar, int scancode) noexcept :
			Event(EventType::KEYBOARD_KEY_RELEASED),
			keyChar(keyChar),
			scancode(scancode)
		{

		}

		~KeyReleasedEvent() = default;

	public:
		/*
		* Returns the key code and the repeated ammount of times the key was pressed(on hold)
		*/
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