#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class WindowBufferResizeEvent final : public Event {
	public:
		/*
		* Creates a new frame buffer event when it updates the viewport
		*/
		explicit WindowBufferResizeEvent(int width, int height) noexcept :
			Event(EventType::WINDOW_BUFFER_RESIZE),
			width(width),
			height(height)
		{

		}

		~WindowBufferResizeEvent() = default;

	public:
		/*
		* Returns the updated size of the framebuffer
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