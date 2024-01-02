#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class CursorCallback;
}

namespace Uranium::Input::Events {

	class CursorMovedEvent final : public Event {
	public:
		friend Callbacks::CursorCallback;

		/*
		* 
		*/
		explicit CursorMovedEvent(double x_position, double y_position) noexcept :
			Event(EventType::CURSOR_MOVED),
			x_position(x_position),
			y_position(y_position),
			x_normalPosition(),
			y_normalPosition()
		{

		}

		~CursorMovedEvent() = default;

	public:
		double getXPosition() const {
			return x_position;
		}

		double getYPosition() const {
			return y_position;
		}

		double getNormalXPosition() const {
			return x_normalPosition;
		}

		double getNormalYPosition() const {
			return y_normalPosition;
		}

	private:
		double x_position;
		double y_position;
		double x_normalPosition;
		double y_normalPosition;
	};

}