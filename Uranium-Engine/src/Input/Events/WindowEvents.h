#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowPositionEvent final : public Event {
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

	class WindowResizeEvent final : public Event {
	public:
		/*
		*/
		explicit WindowResizeEvent(int width, int height) noexcept :
			Event(EventType::WINDOW_RESIZE),
			width(width),
			height(height)
		{

		}

		~WindowResizeEvent() = default;

	public:
		/*
		* Returns the updated size of the window
		*/
		int getWidth() const {
			return  width;
		}

		int getHeight() const {
			return  height;
		}

	private:
		int width;
		int height;
	};

	class WindowCloseEvent final : public Event {
	public:
		/*
		*/
		explicit WindowCloseEvent() noexcept :
			Event(EventType::WINDOW_CLOSE)
		{

		}

		~WindowCloseEvent() = default;
	};
}