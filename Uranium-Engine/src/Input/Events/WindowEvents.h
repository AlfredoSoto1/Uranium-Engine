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

	class WindowFocusEvent final : public Event {
	public:
		/*
		*/
		explicit WindowFocusEvent(bool focused) noexcept :
			Event(EventType::WINDOW_FOCUS),
			focused(focused)
		{

		}

		~WindowFocusEvent() = default;

	public:
		/*
		* Returns true if the window is focused, false otherwise
		*/
		bool isFocused() const {
			return focused;
		}

	private:
		bool focused;
	};

	class WindowMinimizedEvent final : public Event {
	public:
		/*
		*/
		explicit WindowMinimizedEvent(bool minimized) noexcept :
			Event(EventType::WINDOW_MINIMIZE),
			minimized(minimized)
		{

		}

		~WindowMinimizedEvent() = default;

	public:
		/*
		* Returns true if the window is minimized, false otherwise
		*/
		bool isMinimized() const {
			return minimized;
		}

	private:
		bool minimized;
	};

	class WindowMaximizedEvent final : public Event {
	public:
		/*
		*/
		explicit WindowMaximizedEvent(bool maximized) noexcept :
			Event(EventType::WINDOW_MAXIMIZE),
			maximized(maximized)
		{

		}

		~WindowMaximizedEvent() = default;

	public:
		/*
		* Returns true if the window is maximized, false otherwise
		*/
		bool isMaximized() const {
			return maximized;
		}

	private:
		bool maximized;
	};

	class WindowRefreshEvent final : public Event {
	public:
		/*
		*/
		explicit WindowRefreshEvent() noexcept :
			Event(EventType::WINDOW_REFRESH)
		{

		}

		~WindowRefreshEvent() = default;
	};

	class WindowBufferResizeEvent final : public Event {
	public:
		/*
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