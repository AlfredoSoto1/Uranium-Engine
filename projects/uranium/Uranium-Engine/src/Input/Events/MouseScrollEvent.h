#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class MouseCallback;
}

namespace Uranium::Input::Events {

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