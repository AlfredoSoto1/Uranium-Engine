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

	class KeyHoldEvent final : public Event {
	public:
		friend Callbacks::KeyboardCallback;

		/*
		*/
		explicit KeyHoldEvent(int keyChar, int count, int scancode) noexcept :
			Event(EventType::KEYBOARD_KEY_HOLD),
			keyChar(keyChar),
			count(count),
			scancode(scancode)
		{

		}

		~KeyHoldEvent() = default;

	public:
		// TODO SEPARATE INTO DIFFERENT FILES :)
	private:
		int count;
		int keyChar;
		int scancode;
	};
}