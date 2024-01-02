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

	class MouseScrollEvent final : public Event {
	public:
		friend Callbacks::MouseCallback;

		/*
		* Creates a new event when the scroll is used
		*/
		explicit MouseScrollEvent(double xOffset, double yOffset) noexcept :
			Event(EventType::MOUSE_SCROLL),
			xOffset(xOffset),
			yOffset(yOffset)
		{

		}

		~MouseScrollEvent() = default;

	public:
		double getXOffset() const {
			return xOffset;
		}

		double getYOffset() const {
			return yOffset;
		}

	private:
		double xOffset;
		double yOffset;
	};
}