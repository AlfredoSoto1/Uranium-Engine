#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowResizeEvent final : public Event {
	public:
		/*
		* Creates a new resize event for the window.
		* This holds the new dimensions of the window.
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
}