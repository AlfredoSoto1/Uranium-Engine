#pragma once

#include "core/URAPI.h"
#include "Event.h"

namespace uranium::io::events {

	URANIUM_API class WindowPositionEvent final : UR_EXTENDS Event {
	public:
		/*
		* Creates a new window position event
		* containing the current position of the window
		*/
		explicit WindowPositionEvent(int xpos, int ypos) noexcept :
			Event(EventType::WINDOW_POSITION),
			x_position(xpos),
			y_position(ypos)
		{

		}

		~WindowPositionEvent() = default;

	public:
		/*
		* Returns the updated position of the window
		*/
		int getXPosition() const {
			return  x_position;
		}

		int getYPosition() const {
			return  y_position;
		}

	private:
		int x_position;
		int y_position;
	};
}