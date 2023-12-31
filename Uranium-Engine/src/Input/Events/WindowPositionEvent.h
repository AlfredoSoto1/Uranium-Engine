#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowPositionEvent final : public Event {
	public:
		int getXPosition() const;
		int getYPosition() const;

	private:
		int x_position;
		int y_position;
	};
}