#pragma once

#include <functional>

namespace Uranium::Input::Events {

	class Event {
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
		* Event callback function template
		*/
		using EventCallbackFn = std::function<void(Event&)>;

	public:
		/*
		* Create an event that holds a bit mask
		* to filter the type of event that *this* instance of event is
		*/
		explicit Event(EventType eventType) noexcept:
			eventType(eventType),
			handled(false)
		{

		}

		/*
		* Returns the type of the event that *this* type instance is.
		*/
		EventType getEventType() const {
			return eventType;
		}

		void eventHandled(bool handled) {
			this->handled = handled;
		}

		bool wasHandled() const {
			return handled;
		}

	private:
		EventType eventType;
		bool handled;
	};
}