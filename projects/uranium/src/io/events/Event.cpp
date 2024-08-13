#include "Event.h"

namespace uranium::io::events {
	Event::Event(EventType eventType) noexcept :
		eventType(eventType),
		handled(false)
	{

	}

	inline Event::EventType Event::getEventType() const {
		return eventType;
	}

	void Event::eventHandled(bool handled) {
		this->handled = handled;
	}

	inline bool Event::wasHandled() const {
		return handled;
	}
}