#pragma once

#include "core/URAPI.h"
#include <functional>

namespace uranium::io::events {
	
	URANIUM_API class Event {
	public:
		enum class EventType {
			NO_EVENT = 0,
			WINDOW_CLOSE,
			WINDOW_FOCUS,
			WINDOW_RESIZE,
			WINDOW_REFRESH,
			WINDOW_MINIMIZE,
			WINDOW_MAXIMIZE,
			WINDOW_POSITION,
			WINDOW_BUFFER_RESIZE,

			MONITOR_CONNECTION,

			KEYBOARD_KEY_HOLD,
			KEYBOARD_KEY_PRESSED,
			KEYBOARD_KEY_RELEASED,

			MOUSE_SCROLL,
			MOUSE_CLICKED,
			MOUSE_PRESSED,
			MOUSE_RELEASED,

			CURSOR_MOVED,
			CURSOR_DROPPED,
			CURSOR_ENTERED,
		};

	public:
		/*
		* @brief
		* Event callback function template
		*/
		using EventCallbackFn = std::function<void(Event&)>;

	public:
		/*
		* @brief
		* Create an event that holds a bit mask
		* to filter the type of event that *this* instance of event is
		*/
		explicit Event(EventType eventType) noexcept;

		/*
		* @return true if event was handled
		*/
		inline bool wasHandled() const;

		/*
		* @brief
		* Validates event handle
		*/
		void eventHandled(bool handled);

		/*
		* @return event type of what this instance is
		*/
		inline EventType getEventType() const;

	private:
		EventType eventType;
		bool handled;
	};
}