#pragma once

#include <string>
#include <vector>
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

	class CursorEnteredEvent final : public Event {
	public:
		friend Callbacks::CursorCallback;

		/*
		*
		*/
		explicit CursorEnteredEvent(bool entered) noexcept :
			Event(EventType::CURSOR_ENTERED),
			entered(entered)
		{

		}

		~CursorEnteredEvent() = default;

	public:
		bool hasEntered() const {
			return entered;
		}

	private:
		bool entered;
	};

	class CursorDroppedEvent final : public Event {
	public:
		friend Callbacks::CursorCallback;

		/*
		*
		*/
		explicit CursorDroppedEvent() noexcept :
			Event(EventType::CURSOR_DROPPED),
			droppedPaths()
		{

		}

		~CursorDroppedEvent() {
			droppedPaths.clear();
		}

	public:
		const std::vector<std::string>& getDroppedPaths() const {
			return droppedPaths;
		}

	private:
		std::vector<std::string> droppedPaths;
	};
}